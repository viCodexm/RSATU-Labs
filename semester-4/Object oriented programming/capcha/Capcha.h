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
    virtual void generateOnServer(QTcpSocket* socket, QDataStream& in) = 0;

    void callPopup() const;
    void callPopup(QString message) const;
    QString generateString(int size) const;
    QImage addNoise(QImage image) const;
    QImage addBlur(QImage image) const;
    QImage addWatermark(QImage image) const;

signals:
    void capchaGenerated(QString capcha_text);
};

#endif // CAPCHA_H
