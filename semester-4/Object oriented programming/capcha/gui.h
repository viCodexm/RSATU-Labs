#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QTcpSocket>
#include "TextCapcha.h"
#include "ImageCapcha.h"
#include "ErrorHandler.h"

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
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();

    void requestNewFortune();
    void whatToRead();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    Ui::gui *ui;
    TextCapcha *text_capcha;
    ImageCapcha *image_capcha;
    ErrorHandler error_handler;
    QTcpSocket* socket;
    QDataStream in;

signals:
    void readTextCapcha();
    void readImageCapcha();
};
#endif // GUI_H
