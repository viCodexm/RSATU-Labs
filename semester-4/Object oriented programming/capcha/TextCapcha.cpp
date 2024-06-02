#ifndef TEXTCAPCHA_CPP
#define TEXTCAPCHA_CPP

#endif // TEXTCAPCHA_CPP

#include "TextCapcha.h"

bool TextCapcha::isValid() const
{
    return user_text == need_text;
}

TextCapcha::TextCapcha(QWidget *parent)
    : Capcha(parent)
{
    need_text.resize(length);
}

void TextCapcha::generate()
{
    need_text = generateString(length);
    emit capchaGenerated(need_text);
}

void TextCapcha::generateOnServer(QTcpSocket* socket, QDataStream& in)
{
    in.startTransaction();

    need_text = socket->readAll();
    qDebug() << "Received response: " << need_text;

    if (need_text.isEmpty())
        return;

    emit capchaGenerated(need_text);
}

void TextCapcha::setUserInput(QString input)
{
    user_text = input;
}
