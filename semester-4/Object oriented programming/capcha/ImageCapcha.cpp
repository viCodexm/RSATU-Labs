#ifndef IMAGECAPCHA_CPP
#define IMAGECAPCHA_CPP

#endif // IMAGECAPCHA_CPP
#include "ImageCapcha.h"
#include "ProjectSpecific.h"

void ImageCapcha::setButtonStyle(QPushButton* button, bool selected)
{
    button->setStyleSheet(
        (selected) ? "background-color: blue;" : "background-color: transparent");
    // button->hide();
}

void ImageCapcha::getImagesPool(const QString& directoryPath)
{
    QDirIterator iterator(directoryPath, QStringList() << "*.png" << "*.jpg", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (iterator.hasNext())
        imagesPool.append(iterator.next());
}

QPushButton* ImageCapcha::formButton(QString& imagePath, int row, int column)
{
    need_presses |= imagePath.contains("panda") * 1 << (row * max_column + column);

    QImage image(imagePath);
    QIcon icon(QPixmap::fromImage(addWatermark(addBlur(addNoise(image)))));

    QPushButton* button = new QPushButton(icon, "", this);
    button->setFixedSize(QSize(90, 90));
    button->setIconSize(QSize(85, 85));
    button->setCheckable(true);
    connect(button, &QPushButton::toggled, this,
            [button, row, column, this] { updatePressState(button, row, column); });
    return button;
}

void ImageCapcha::clearGrid() {
    while (gridLayout->count() > 0) {
        QWidget* widgetToRemove = gridLayout->takeAt(0)->widget();
        if (widgetToRemove!= nullptr)
            delete widgetToRemove;
    }
}

void ImageCapcha::populateGridWithImages() {
    clearGrid();
    QVector<QString> imagesPaths = getRandomImagesPaths();
    int row = 0, column = 0;
    foreach (QString imagePath, imagesPaths) {
        if (column >= max_column) { column = 0; row++; }
        QPushButton* button = formButton(imagePath, row, column);
        gridLayout->addWidget(button, row, column);
        column++;
    }
    qDebug() << gridLayout;
}

bool ImageCapcha::isValid() const {
    return need_presses == current_presses;
}

void ImageCapcha::getKeyFromServer(QTcpSocket* socket, QDataStream& in) {
    in.startTransaction();

    need_presses = socket->readAll().toInt();
    qDebug() << "Received response: " << need_presses;
}

ImageCapcha::~ImageCapcha() {
    delete gridLayout;
}

QVector<QString> ImageCapcha::getRandomImagesPaths()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(imagesPool.begin(), imagesPool.end(), g);
    return QVector(imagesPool.begin(), imagesPool.begin() + max_images);
}



ImageCapcha::ImageCapcha(QWidget *parent)
    : Capcha(parent)
    , gridLayout(new QGridLayout(this))
{
    getImagesPool(project::getProjectPath() + "/imgs/");
    gridLayout->setSpacing(15);
}

void ImageCapcha::generate()
{
    need_presses = current_presses = 0;
    populateGridWithImages();
}

void ImageCapcha::generateOnServer(QTcpSocket* socket, QDataStream& in)
{
    in.startTransaction();

    accumulative_data.append(socket->readAll());
    qDebug() << accumulative_data.size();

    if (accumulative_data.size() > 200000) {
        qDebug() << "hello";
    } else return;

    clearGrid();

    QDataStream stream(&accumulative_data, QIODevice::ReadOnly);

    for (int column = 0; column < max_column; ++column) {
        for (int row = 0; row < max_images / max_column; ++row) {

            QIcon icon; stream >> icon;

            qDebug() << column << row << "  " << icon;

            QPushButton* button = new QPushButton(icon, "", this);
            button->setFixedSize(QSize(90, 90));
            button->setIconSize(QSize(85, 85));
            button->setCheckable(true);
            connect(button, &QPushButton::toggled, this,
                    [button, row, column, this] { updatePressState(button, row, column); });

            gridLayout->addWidget(button, row, column);
        }
    }
    qDebug() << "Done!   need_presses: " << need_presses;
    in.abortTransaction();
    accumulative_data.clear();
}

void ImageCapcha::serialize(QTcpSocket* socket)
{
    QByteArray data = NULL;
    QDataStream stream(&data, QIODevice::WriteOnly);

    for (int column = 0; column < gridLayout->columnCount(); ++column) {
        for (int row = 0; row < gridLayout->rowCount(); ++row) {
            QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row, column)->widget());
            stream << button->icon();
            qDebug() << column << row << "  " << button->icon();
        }
    }
    qDebug() << data.size() << "need_presses: " << need_presses;

    qint64 bytesWritten = 0;
    qint64 bytesToWrite = data.size();
    while (bytesWritten < bytesToWrite) {
        qint64 chunkSize = qMin(qint64(65536), bytesToWrite - bytesWritten);
        qDebug() << chunkSize;
        socket->write(data.mid(bytesWritten, chunkSize));
        bytesWritten += chunkSize;
    }
}

void ImageCapcha::updatePressState(QPushButton* button, int row, int column)
{
    int current_bit = 1 << (row * max_column + column);
    current_presses ^= current_bit;
    setButtonStyle(button, current_presses & current_bit);
}
