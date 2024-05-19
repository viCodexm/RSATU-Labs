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
    explicit TextCapcha(QWidget *parent = nullptr) : Capcha(parent) {}

    void generate() override {
        capcha_text.clear();
        capcha_text.reserve(length);
        for (int i = 0; i < length; ++i)
            capcha_text.append(allowed_symbols.at(QRandomGenerator::global()->bounded(allowed_symbols.size())));
        emit capchaGenerated(capcha_text);
    }
};

#endif // TEXTCAPCHA_H
