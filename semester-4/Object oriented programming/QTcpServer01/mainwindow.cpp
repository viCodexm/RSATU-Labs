#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QPushButton>
#include <QJsonArray>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image_capcha = new ImageCapcha(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    server_status=0;
}

void MainWindow::on_starting_clicked()
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!tcpServer->listen(QHostAddress::Any, 33333) && server_status==0) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
        ui->textinfo->append(tcpServer->errorString());
    } else {
        server_status=1;
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
        ui->textinfo->append(QString::fromUtf8("Сервер запущен!"));
        qDebug() << QString::fromUtf8("Сервер запущен!");
    }
}

void MainWindow::on_stoping_clicked()
{
    if (server_status != 1)
        return;

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
    server_status=0;
}


void MainWindow::newuser()
{
    if (server_status != 1)
        return;

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
    int idusersocs=clientSocket->socketDescriptor();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);

    QString text = clientSocket->readAll();
    ui->textinfo->append("От клиента: " + text + "\n\r");

    if (text == "Хочу текстовую капчу") {
        clientSocket->write(generateString(6).toLatin1());
    }
    else if (text == "Хочу капчу с картинками") {
        image_capcha->generate();
        QJsonArray jsonArray;
        for (int i = 0; i < image_capcha->gridLayout->count(); ++i) {
            // QPushButton* button = qobject_cast<QPushButton*>(image_capcha->gridLayout->itemAt(i));
            QPushButton* button = new QPushButton();
            QJsonObject json;
            json["text"] = button->text();
            // json["row"] = image_capcha->gridLayout->row(i);
            // json["column"] = image_capcha->gridLayout->column(i);
            jsonArray.append(json);
        }

        //// Now, send the JSON array over the network
        // QByteArray data;
        // QJsonArray::iterator it = jsonArray.begin();
        // while (it != jsonArray.end()) {
        //     QJsonObject jsonObject = it.value().toObject();
        //     // Serialize the object to a QByteArray
        //     QByteArray jsonData;
        //     QDataStream stream(&jsonData, QIODevice::WriteOnly);
        //     stream << jsonObject;
        //     // Send the data over the network using QtTcpServer
        //     clientSocket->write(jsonData);
        //     it++;
        // }
    }

    clientSocket->flush();
}
