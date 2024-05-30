#ifndef TEXTCAPCHA_H
#define TEXTCAPCHA_H

#include "Capcha.h"
#include <QRandomGenerator>

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

    void setUserInput(QString input) {
        user_text = input;
    }
};

#endif // TEXTCAPCHA_H
