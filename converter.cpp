#include "converter.h"
#include <libheif/heif.h>
#include <QImage>
#include <QColorSpace>
#include <QFile>
#include <QDebug>

bool HeicConverter::convertFile(const QString &inputFile, const QString &outputFile, int quality)
{
    qDebug() << "Starting conversion for:" << inputFile;

    // --- Проверка заголовка файла ---
    QFile f(inputFile);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file:" << inputFile;
        return false;
    }

    QByteArray header = f.peek(32);
    f.close();

    // ------------------------------------------------------------------
    // JPEG (магическое число: FF D8 FF)
    // ------------------------------------------------------------------
    if (header.startsWith("\xFF\xD8\xFF")) {
        qDebug() << "File is actually JPEG, fallback to QImage:" << inputFile;

        QImage img;
        if (!img.load(inputFile)) {
            qWarning() << "Failed to load JPEG with QImage:" << inputFile;
            return false;
        }
        img.setColorSpace(QColorSpace::SRgb);
        return img.save(outputFile, "JPEG", quality);
    }

    // ------------------------------------------------------------------
    // WEBP (RIFF....WEBP)
    // ------------------------------------------------------------------
    if (header.startsWith("RIFF") && header.size() >= 12 && header.mid(8, 4) == "WEBP") {
        qDebug() << "File is WEBP, converting via QImage:" << inputFile;

        QImage img;
        if (!img.load(inputFile)) {
            qWarning() << "Failed to load WEBP with QImage:" << inputFile;
            return false;
        }
        img.setColorSpace(QColorSpace::SRgb);
        return img.save(outputFile, "JPEG", quality);
    }

    // ------------------------------------------------------------------
    // PNG
    // ------------------------------------------------------------------
    if (header.startsWith("\x89PNG\r\n\x1a\n")) {
        qDebug() << "File is PNG, converting via QImage:" << inputFile;

        QImage img;
        if (!img.load(inputFile)) {
            qWarning() << "Failed to load PNG with QImage:" << inputFile;
            return false;
        }
        img.setColorSpace(QColorSpace::SRgb);
        return img.save(outputFile, "JPEG", quality);
    }

    // ------------------------------------------------------------------
    // HEIC / HEIF / AVIF (через libheif)
    // ------------------------------------------------------------------
    if ((header.startsWith("ftyp") || (header.size() >= 12 && header.mid(4, 4) == "ftyp"))) {
        const QByteArray ftyp = header.mid(4, 8).toLower();
        if (ftyp.contains("heic") || ftyp.contains("heix") || ftyp.contains("heim") ||
            ftyp.contains("heis") || ftyp.contains("hevs") || ftyp.contains("hevm") ||
            ftyp.contains("mif1") || ftyp.contains("avis") || ftyp.contains("avif")) {
            qDebug() << "File is HEIC/HEIF/AVIF, converting via libheif:" << inputFile;
        }
    }

    heif_context* ctx = heif_context_alloc();
    if (!ctx) {
        qWarning() << "Failed to allocate heif_context.";
        return false;
    }

    heif_error err = heif_context_read_from_file(
        ctx,
        inputFile.toStdString().c_str(),
        nullptr
        );

    if (err.code != heif_error_code::heif_error_Ok) {
        qWarning() << "Cannot read HEIC file:" << inputFile << ", error:" << err.message;
        heif_context_free(ctx);
        return false;
    }

    qDebug() << "HEIC file read successfully.";

    heif_image_handle* handle = nullptr;
    err = heif_context_get_primary_image_handle(ctx, &handle);
    if (err.code != heif_error_code::heif_error_Ok || !handle) {
        qWarning() << "Cannot get primary image handle:" << inputFile << ", error:" << err.message;
        heif_context_free(ctx);
        return false;
    }

    heif_image* img = nullptr;
    err = heif_decode_image(
        handle,
        &img,
        heif_colorspace_RGB,
        heif_chroma_interleaved_RGBA,
        nullptr
        );

    if (err.code != heif_error_code::heif_error_Ok || !img) {
        qWarning() << "Cannot decode HEIC image to RGBA:" << inputFile << ", error:" << err.message;
        heif_image_handle_release(handle);
        heif_context_free(ctx);
        return false;
    }

    int w = heif_image_get_width(img, heif_channel_interleaved);
    int h = heif_image_get_height(img, heif_channel_interleaved);

    int stride = 0;
    const uint8_t* data = heif_image_get_plane_readonly(
        img,
        heif_channel_interleaved,
        &stride
        );

    if (!data) {
        qWarning() << "Failed to get interleaved plane for:" << inputFile;
        heif_image_release(img);
        heif_image_handle_release(handle);
        heif_context_free(ctx);
        return false;
    }

    QImage qimg(w, h, QImage::Format_RGBA8888);
    for (int y = 0; y < h; ++y) {
        memcpy(qimg.scanLine(y), data + y * stride, w * 4);
    }

    bool saved = qimg.save(outputFile, "JPEG", quality);
    if (!saved) {
        qWarning() << "Failed to save JPEG:" << outputFile;
    } else {
        qDebug() << "Saved JPEG successfully:" << outputFile;
    }

    heif_image_release(img);
    heif_image_handle_release(handle);
    heif_context_free(ctx);

    return saved;
}
