#include "Capcha.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QPainter>

Capcha::Capcha(QWidget *parent)
    : QWidget{parent}
{}

void Capcha::callPopup() const {
    if (this->isValid()) {
        QMessageBox successBox(QMessageBox::Information, "Успех", "Капча успешно пройдена");
        successBox.exec();
    }
    else {
        QMessageBox failBox(QMessageBox::Warning, "Ошибка", "Капча не пройдена");
        failBox.exec();
    }
}


QString Capcha::generateString(int size) {
    QString allowed_symbols = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_!@~$^&*";
    QString string(size, '.');
    for (QChar& capcha_symbol : string)
        capcha_symbol = (allowed_symbols.at(QRandomGenerator::global()->bounded(allowed_symbols.size())));

    return string;
}


QImage Capcha::addNoise(QImage image) {
    const int size = image.width() * image.height();
    int min_noise_amount = size / 10;
    int max_noise_amount = size / 3;
    int noise_amount = QRandomGenerator::global()->bounded(min_noise_amount, max_noise_amount);
    for (; noise_amount > 0; --noise_amount) {
        int x = QRandomGenerator::global()->bounded(image.width());
        int y = QRandomGenerator::global()->bounded(image.height());
        image.setPixelColor(x, y, QColor(0, 0, 0, 250));
    }
    return image;
}


QImage Capcha::addBlur(QImage image) {
    QT_BEGIN_NAMESPACE
    extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
    QT_END_NAMESPACE

    QPixmap dest(image.size());
    dest.fill(Qt::transparent);
    {
        int blur_radius = 5;
        QPainter painter(&dest);
        qt_blurImage(&painter, image, blur_radius, true, false);
    }
    return dest.toImage();
}

QImage Capcha::addWatermark(QImage image) {
    QPainter painter(&image);
    const int color_min     = 100,  color_max     = 255;
    const int font_min_size = 16,   font_max_size = 24;
    const int alpha_min     = 180,  alpha_max     = 240;
    const int r = QRandomGenerator::global()->bounded(color_min, color_max);
    const int g = QRandomGenerator::global()->bounded(color_min, color_max);
    const int b = QRandomGenerator::global()->bounded(color_min, color_max);
    const int alpha = QRandomGenerator::global()->bounded(alpha_min, alpha_max);

    painter.setPen(QPen(QColor(r, g, b, alpha)));
    const int font_size = QRandomGenerator::global()->bounded(font_min_size, font_max_size);
    painter.setFont(QFont("Times", font_size, QFont::Bold));
    painter.setCompositionMode(QPainter::CompositionMode_Source);

    const int length_min = 8, length_max = 12;
    QString watermark = generateString(QRandomGenerator::global()->bounded(length_min, length_max));

    const int rect_size = 100;
    QRectF rect(0, 0, rect_size, rect_size);
    painter.translate(rect.center());
    painter.rotate(QRandomGenerator::global()->bounded(0, 360));
    painter.translate(-rect.center());
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, watermark);
    return image;
}
