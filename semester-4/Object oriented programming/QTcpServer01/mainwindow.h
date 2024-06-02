#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include "../capcha/ImageCapcha.h"

namespace Ui {
    class MainWindow;
}

class QTcpServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_starting_clicked();
    void on_stoping_clicked();
    void newuser();
    void slotReadClient();

    QString generateString(int size);
private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QMap<int, QTcpSocket *> SClients;
    ImageCapcha* image_capcha;
};

#endif // MAINWINDOW_H
