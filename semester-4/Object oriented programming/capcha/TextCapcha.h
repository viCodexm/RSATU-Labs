#ifndef TEXTCAPCHA_H
#define TEXTCAPCHA_H

#include "Capcha.h"
#include <QRandomGenerator>
#include <QTcpSocket>
#include <QHostAddress>

class TextCapcha : public Capcha {
    QString user_text, need_text;
    const int length = 6;

    bool isValid() const override {
        return user_text == need_text;
    }

public:
    explicit TextCapcha(QWidget *parent = nullptr) : Capcha(parent) {
        need_text.resize(length);
    }

    void generate() override {
        need_text = generateString(length);
        emit capchaGenerated(need_text);
    }

    void generateOnServer(QTcpSocket* socket) override {
        socket->write("Хочу текстовую капчу");

        socket->waitForReadyRead();
        QByteArray response = socket->readAll();
        QString receivedResponse = QString::fromLatin1(response.constData());
        qDebug() << "Received response: " << receivedResponse;
        need_text = response;

        emit capchaGenerated(need_text);
    }

    void setUserInput(QString input) {
        user_text = input;
    }
};

#endif // TEXTCAPCHA_H
