#ifndef TEXTCAPCHA_H
#define TEXTCAPCHA_H

#include "Capcha.h"
#include <QRandomGenerator>

class TextCapcha : public Capcha {
    QString capcha_text;
    QString allowed_symbols = "abcdefghijklmnopqrstuvwxyz0123456789";
    int length = 6;

    bool isValid(const QString& input) const override {
        return input == capcha_text;
    }
public:
    explicit TextCapcha(QWidget *parent = nullptr) : Capcha(parent) {
        capcha_text.resize(length);
    }

    void generate() override {
        for (QChar& capcha_symbol : capcha_text)
            capcha_symbol = (allowed_symbols.at(QRandomGenerator::global()->bounded(allowed_symbols.size())));

        emit capchaGenerated(capcha_text);
    }
};

#endif // TEXTCAPCHA_H
