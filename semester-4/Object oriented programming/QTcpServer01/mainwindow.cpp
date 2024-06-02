#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QPushButton>
#include <QJsonArray>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tcpServer(new QTcpServer(this)),
    image_capcha(new ImageCapcha())
{
    ui->setupUi(this);
    on_starting_clicked();
    image_capcha->generate();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpServer;
}

void MainWindow::on_starting_clicked()
{
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!tcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
        ui->textinfo->append(tcpServer->errorString());
    } else {
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
        ui->textinfo->append(QString::fromUtf8("Сервер запущен!"));
        qDebug() << QString::fromUtf8("Сервер запущен!");
    }
}

void MainWindow::on_stoping_clicked()
{
    foreach(int i,SClients.keys()){
        QTextStream os(SClients[i]);
        os.setAutoDetectUnicode(true);
        os << QDateTime::currentDateTime().toString() << "\n";
        SClients[i]->close();
        SClients.remove(i);
    }
    tcpServer->close();
    ui->textinfo->append(QString::fromUtf8("Сервер остановлен!"));
    qDebug() << QString::fromUtf8("Сервер остановлен!");
}


void MainWindow::newuser()
{
    qDebug() << QString::fromUtf8("У нас новое соединение!");
    ui->textinfo->append(QString::fromUtf8("У нас новое соединение!"));
    QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
    int idusersocs=clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(slotReadClient()));
}

QString MainWindow::generateString(int size) {
    QString allowed_symbols = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_!@~$^&*";
    QString string(size, '.');
    for (QChar& capcha_symbol : string)
        capcha_symbol = (allowed_symbols.at(QRandomGenerator::global()->bounded(allowed_symbols.size())));

    return string;
}


void MainWindow::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);

    QString text = clientSocket->readAll();
    ui->textinfo->append("От клиента: " + text + "\n");

    if (text == "Хочу текстовую капчу") {
        QString tmp = generateString(6);
        qDebug() << tmp;
        clientSocket->write(tmp.toLatin1());
    }
    else if (text == "Хочу капчу с картинками") {
        image_capcha->generate();
        image_capcha->serialize(clientSocket);
    }
    // else if (text == "Хочу проверить капчу с картинками") {
    //     qDebug() << image_capcha->need_presses;
    //     clientSocket->write(std::to_string(image_capcha->need_presses).c_str());
    // }
    clientSocket->flush();
}
