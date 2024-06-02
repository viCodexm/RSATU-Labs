#include "gui.h"
#include "ui_gui.h"
#include "ProjectSpecific.h"
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
    , socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    in.setDevice(socket);
    connect(ui->getFortuneButton, &QAbstractButton::clicked, this, &gui::requestNewFortune);
    connect(socket, &QIODevice::readyRead, this, &gui::whatToRead);
    // connect(socket, &QAbstractSocket::errorOccurred, this, &gui::displayError);

    ui->label->hide();
    ui->tabWidget->setCurrentIndex(0);
    text_capcha = new TextCapcha(this);
    connect(text_capcha, &TextCapcha::capchaGenerated, this, &gui::updateCapchaDisplay);

    try {
        requestNewFortune();
    } catch (const std::exception& error) {
        error_handler.callErrorPopup(error.what());
    }

    text_capcha->generateOnServer(socket, in);
    ui->verticalLayout->addWidget(text_capcha);

    image_capcha = new ImageCapcha(this);
    try {
        requestNewFortune();
    } catch (const std::exception& error) {
        error_handler.callErrorPopup(error.what());
    }

    image_capcha->show();
    ui->verticalLayout->addWidget(image_capcha);
}

QString getRandomImagePath(QString path) {
    QVector<QString> imagesPool;
    QDirIterator iterator(path, QStringList() << "*.png" << "*.jpg", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (iterator.hasNext())
        imagesPool.append(iterator.next());

    return *(imagesPool.begin() + QRandomGenerator::global()->bounded(imagesPool.size()));
}

void gui::updateCapchaDisplay(QString capchaText) {
    ui->label->setText(capchaText);
    QString path = getRandomImagePath(project::getProjectPath() + "/imgs/");
    ui->label->setStyleSheet("background-image: url(" + path + "); color: rgba(255, 0, 0, 1);");
}


gui::~gui()
{
    delete ui;
    delete text_capcha;
}

void gui::requestNewFortune()
{
    socket->abort();
    socket->connectToHost(QHostAddress::Any, 33333);
    qDebug() << socket->state();
    // if ((socket->state() != QAbstractSocket::ConnectedState))
    //     throw std::runtime_error("Не удается подключится к серверу");

    std::string msg = "";
    if (ui->tabWidget->currentWidget() == ui->tab)
        msg = "Хочу текстовую капчу";
    else msg = "Хочу капчу с картинками";

    socket->write(msg.c_str());
    qDebug() << msg.c_str();
}

void gui::whatToRead()
{
    if (ui->tabWidget->currentWidget() == ui->tab) {
        text_capcha->generateOnServer(socket, in);
        ui->label->show();
    }
    else {
        image_capcha->generateOnServer(socket, in);
    }
}

void gui::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Клиент"),
                                 tr("Хост не найден. Пожалуйста, проверьте "
                                    "имя хоста и настройки портов."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Клиент"),
                                 tr("Соединение отклонено. "
                                    "Убедитесь, что сервер запущен, "
                                    "проверьте имя хоста и настройки "
                                    "портов."));
        break;
    default:
        QMessageBox::information(this, tr("Клиент"),
                                 tr("Встретилась следующая ошибка: %1.")
                                     .arg(socket->errorString()));
    }
}


void gui::on_lineEdit_returnPressed()
{
    text_capcha->setUserInput(ui->lineEdit->text());
    text_capcha->callPopup();
    try {
        text_capcha->generateOnServer(socket, in);
    } catch (const std::string error_msg) {
        error_handler.callErrorPopup(error_msg);
    }
    ui->lineEdit->clear();
}


void gui::on_pushButton_clicked()
{
    requestNewFortune();
    if (ui->tabWidget->currentWidget() == ui->tab) {
        text_capcha->callPopup();
        text_capcha->generateOnServer(socket, in);
    }
    else {
        image_capcha->callPopup();
        image_capcha->generateOnServer(socket, in);
    }
    ui->lineEdit->clear();
}


// about program
void gui::on_action_2_triggered()
{
    QMessageBox popup(QMessageBox::Information, "О программе",
                        "Автор: Скворцов Дмитрий\n"
                        "Графический интерфейс: qt\n"
                        "Язык: C++");
    popup.exec();
}

// exit
void gui::on_action_3_triggered()
{
    QCoreApplication::quit();
}


void gui::on_action_4_triggered()
{
    QMessageBox popup(QMessageBox::Information, "Помощь",
                      "Программа предназначена для прохождения капчи\n\n"
                      "Предусмотрено два варианта:\n"
                      "- текстовая и капча с картинками\n\n"
                      "При возникновении ошибок или пожеланий пишите на почту разработчика: uin@yandex.ru");
    popup.exec();
}

