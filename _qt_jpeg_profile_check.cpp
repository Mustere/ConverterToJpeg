#include <QImage>
#include <QImageWriter>
#include <QColorSpace>
#include <QDebug>

int main() {
    QImage img(64, 64, QImage::Format_RGB888);
    img.fill(Qt::red);
    img.setColorSpace(QColorSpace(QColorSpace::SRgb));
    QImageWriter writer("/home/dmitriy/Работа/Projects/software/ConverterToJpeg/_qt_jpeg_profile_check.jpg", "JPG");
    writer.setQuality(90);
    if (\!writer.write(img)) {
        qDebug() << "write failed";
        return 1;
    }
    qDebug() << "saved";
    qDebug() << "image colorspace:" << img.colorSpace().isValid() << img.colorSpace().name();
    return 0;
}
