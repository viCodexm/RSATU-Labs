#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class server;
}
QT_END_NAMESPACE

class server : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_starting_clicked();
    void on_stoping_clicked();
    void newuser();
    void slotReadClient();

private:
    Ui::server *ui;
    QTcpServer *tcpServer;
    int server_status;
    QMap<int,QTcpSocket *> SClients;

public:
    explicit server(QWidget *parent = nullptr);
    ~server();
};
#endif // SERVER_H
