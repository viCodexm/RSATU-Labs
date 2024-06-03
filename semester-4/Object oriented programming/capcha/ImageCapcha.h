#ifndef IMAGECAPCHA_H
#define IMAGECAPCHA_H


#include "Capcha.h"
#include <QDirIterator>
#include <QIcon>
#include <QPushButton>
#include <QGridLayout>
#include <QRandomGenerator>
#include <QPainter>

class ImageCapcha : public Capcha {
    Q_OBJECT
public:
    QGridLayout* gridLayout;
    int need_presses = 0;
private:
    QVector<QString> imagesPool;
    const int max_images = 12, max_column = 4;
    int current_presses = 0;
    QByteArray accumulative_data = NULL;
    qint32 totalBytesToGet = 0;
    qint32 validationKey = 0;


    void setButtonStyle(QPushButton* button, bool selected);
    void getImagesPool(const QString& directoryPath);
    QVector<QString> getRandomImagesPaths();
    QPushButton* formButton(QString& imagePath, int row, int column);
    void populateGridWithImages();
    bool isValid() const override;
    ~ImageCapcha();

public:
    explicit ImageCapcha(QWidget *parent = nullptr);
    void generate() override;
    void generateOnServer(QTcpSocket* socket, QDataStream& in) override;
    void getKeyFromServer(QTcpSocket* socket, QDataStream& in);
    void serialize(QTcpSocket* socket);
    void clearGrid();


public slots:
    void updatePressState(QPushButton* button, int row, int column);
};

#endif // IMAGECAPCHA_H
