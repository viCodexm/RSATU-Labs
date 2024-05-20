#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "TextCapcha.h"
#include "ImageCapcha.h"
#include "ErrorHandler.h"
#include "ProjectSpecific.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class gui;
}
QT_END_NAMESPACE

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui(QWidget *parent = nullptr);
    ~gui();
    void updateCapchaDisplay(QString capchaText);

private slots:
    void on_pushButton_2_clicked();
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::gui *ui;
    TextCapcha *capchaWidget;
    ImageCapcha *image_capcha;
    ErrorHandler error_handler;
};
#endif // GUI_H
