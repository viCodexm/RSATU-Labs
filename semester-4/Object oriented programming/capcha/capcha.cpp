#include "Capcha.h"
#include <QMessageBox>

Capcha::Capcha(QWidget *parent)
    : QWidget{parent}
{}

void Capcha::callPopup(const QString& input) const {
    if (this->isValid(input)) {
        QMessageBox successBox(QMessageBox::Information, "Успех", "Капча успешно пройдена");
        successBox.exec();
    }
    else {
        QMessageBox failBox(QMessageBox::Warning, "Ошибка", "Капча не пройдена");
        failBox.exec();
    }
}
