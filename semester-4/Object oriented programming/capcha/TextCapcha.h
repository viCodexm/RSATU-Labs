#ifndef TEXTCAPCHA_H
#define TEXTCAPCHA_H

#include "Capcha.h"
#include <QRandomGenerator>
#include <QTcpSocket>
#include <QHostAddress>

class TextCapcha : public Capcha {
    QString user_text, need_text;
    const int length = 6;

    bool isValid() const override;

public:
    explicit TextCapcha(QWidget *parent = nullptr);

    void generate() override;

    void generateOnServer(QTcpSocket* socket, QDataStream& in) override;

    void setUserInput(QString input);
};

#endif // TEXTCAPCHA_H
