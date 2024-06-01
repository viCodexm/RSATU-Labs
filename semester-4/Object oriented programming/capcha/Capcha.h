#ifndef CAPCHA_H
#define CAPCHA_H

#include <QWidget>
#include <QTcpSocket>

class Capcha : public QWidget
{
    Q_OBJECT
    virtual bool isValid() const = 0;
public:
    explicit Capcha(QWidget *parent = nullptr);
    virtual void generate() = 0;
    virtual void generateOnServer(QTcpSocket* socket) = 0;

    void callPopup() const;
    QString generateString(int size);
    QImage addNoise(QImage image);
    QImage addBlur(QImage image);
    QImage addWatermark(QImage image);

signals:
    void capchaGenerated(QString capcha_text);
};

#endif // CAPCHA_H
