#pragma once

#include <QMainWindow>
#include <QThread>
#include <QElapsedTimer>
#include <QVector>

#include "converter.h"
#include "clickablelabel.h"
#include <QFileInfo>

#include <QObject>
#include <QStringList>
#include <QImage>
#include <QColorSpace>
#include <QFileInfo>
#include <QDir>
#include <QImageReader>
#include <QImageWriter>

#include <libheif/heif.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(const QStringList &files,
           const QString &sourceDir,
           const QString &destDir,
           int quality,
           bool *stopRequested,
           QObject *parent = nullptr)
        : QObject(parent),
        m_files(files),
        m_sourceDir(sourceDir),
        m_destDir(destDir),
        m_quality(quality),
        m_stopRequested(stopRequested)
    {}

public slots:
    void process() {
        for (const QString &file : m_files) {
            if (m_stopRequested && *m_stopRequested)
                break;

            QString fullPath;
            QFileInfo fi(file);

            if (fi.isAbsolute())
                fullPath = file;
            else if (!m_sourceDir.isEmpty())
                fullPath = QDir(m_sourceDir).absoluteFilePath(file);
            else
                fullPath = file;

            bool ok = convertToJpeg(fullPath);
            emit fileProcessed(fullPath, ok);
        }

        emit finished();
    }

signals:
    void fileProcessed(const QString &file, bool ok);
    void finished();

private:
    static QByteArray readFileHeader(const QString &filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
            return {};

        const QByteArray header = file.read(32);
        file.close();
        return header;
    }

    static QString detectImageFormat(const QString &filePath) {
        const QByteArray header = readFileHeader(filePath);
        if (header.isEmpty())
            return {};

        if (header.startsWith("\xFF\xD8\xFF"))
            return "jpeg";

        if (header.startsWith("RIFF") && header.size() >= 12 && header.mid(8, 4) == "WEBP")
            return "webp";

        if (header.startsWith("\x89PNG\r\n\x1a\n"))
            return "png";

        if (header.startsWith("GIF8"))
            return "gif";

        if (header.startsWith("II*\x00") || header.startsWith("MM\x00*"))
            return "tiff";

        if ((header.startsWith("ftyp") || (header.size() >= 12 && header.mid(4, 4) == "ftyp"))) {
            const QByteArray ftyp = header.mid(4, 8).toLower();
            if (ftyp.contains("heic") || ftyp.contains("heix") || ftyp.contains("heim") ||
                ftyp.contains("heis") || ftyp.contains("hevs") || ftyp.contains("hevm") ||
                ftyp.contains("mif1") || ftyp.contains("avis") || ftyp.contains("avif")) {
                return "heic";
            }
        }

        QImageReader probe(filePath);
        const QString format = probe.format();
        return format.isEmpty() ? QString() : format.toLower();
    }

    bool convertToJpeg(const QString &filePath) {
        QFileInfo fi(filePath);
        if (!fi.exists())
            return false;

        const QString detectedFormat = detectImageFormat(filePath);
        const QString ext = fi.suffix().toLower();

        if (detectedFormat == "heic" || detectedFormat == "heif" || detectedFormat == "avif") {
            return convertWithLibheif(filePath, fi);
        }

        if (!detectedFormat.isEmpty() && detectedFormat != "jpeg") {
            QImageReader reader(filePath);
            reader.setAutoTransform(true);
            QImage image = reader.read();
            if (!image.isNull()) {
                return saveJpeg(image, fi);
            }
        }

        // 🔹 fallback for standard Qt-supported image types
        if (ext != "avif") {
            QImageReader reader(filePath);
            reader.setAutoTransform(true);
            QImage image = reader.read();
            if (!image.isNull()) {
                return saveJpeg(image, fi);
            }
        }

        // 🔹 fallback through libheif (HEIC / HEIF / AVIF)
        if (ext == "heic" || ext == "heif" || ext == "avif") {
            return convertWithLibheif(filePath, fi);
        }

        return false;
    }

    bool convertWithLibheif(const QString &filePath, const QFileInfo &fi) {
        heif_context* ctx = heif_context_alloc();
        if (!ctx)
            return false;

        heif_error err = heif_context_read_from_file(
            ctx, filePath.toUtf8().constData(), nullptr);

        if (err.code != heif_error_Ok) {
            heif_context_free(ctx);
            return false;
        }

        heif_image_handle* handle = nullptr;
        err = heif_context_get_primary_image_handle(ctx, &handle);
        if (err.code != heif_error_Ok) {
            heif_context_free(ctx);
            return false;
        }

        heif_image* img = nullptr;
        err = heif_decode_image(
            handle,
            &img,
            heif_colorspace_RGB,
            heif_chroma_interleaved_RGB,
            nullptr
            );

        if (err.code != heif_error_Ok || !img) {
            heif_image_handle_release(handle);
            heif_context_free(ctx);
            return false;
        }

        int width  = heif_image_get_width(img, heif_channel_interleaved);
        int height = heif_image_get_height(img, heif_channel_interleaved);
        int stride = 0;

        const uint8_t* src =
            heif_image_get_plane_readonly(img, heif_channel_interleaved, &stride);

        if (!src) {
            heif_image_release(img);
            heif_image_handle_release(handle);
            heif_context_free(ctx);
            return false;
        }

        // ✅ ГЛУБОКАЯ КОПИЯ (обязательно)
        QImage image(width, height, QImage::Format_RGB888);
        for (int y = 0; y < height; ++y) {
            memcpy(image.scanLine(y), src + y * stride, width * 3);
        }
        image.setColorSpace(QColorSpace::SRgb);

        bool ok = saveJpeg(image, fi);

        heif_image_release(img);
        heif_image_handle_release(handle);
        heif_context_free(ctx);

        return ok;
    }

    bool saveJpeg(const QImage &image, const QFileInfo &fi) {
        QString outFile =
            QDir(m_destDir).absoluteFilePath(fi.completeBaseName() + ".jpg");

        QImage imageForSave = image;
        if (imageForSave.colorSpace().isValid()) {
            imageForSave.setColorSpace(QColorSpace(QColorSpace::SRgb));
        } else {
            imageForSave.setColorSpace(QColorSpace::SRgb);
        }

        QImageWriter writer(outFile, "JPG");
        writer.setQuality(m_quality);
        return writer.write(imageForSave);
    }

private:
    QStringList m_files;
    QString m_sourceDir;
    QString m_destDir;
    int m_quality;
    bool *m_stopRequested;
};
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int finishedThreads = 0;

private slots:
    void on_browseSourceButton_clicked();
    void on_browseDestButton_clicked();
    void on_startButton_clicked();
    void stopConversion();
    void openSettingsDialog();

    void handleFileProcessed(const QString &file, bool ok);
    void handleWorkerFinished();
    void showAboutDialog();

private:
    Ui::MainWindow *ui;

    bool stopRequested = false;
    int totalFiles = 0;
    int processedFiles = 0;
    int successCount = 0;
    int errorCount = 0;
    int threadCount;

    QElapsedTimer timer;
    QVector<QThread*> threads;
};
