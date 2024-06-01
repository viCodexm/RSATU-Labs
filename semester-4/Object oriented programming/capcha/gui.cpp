#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress::Any, 33333);

    text_capcha = new TextCapcha(this);
    connect(text_capcha, &TextCapcha::capchaGenerated, this, &gui::updateCapchaDisplay);

    // text_capcha->generate();
    text_capcha->generateOnServer(socket);
    ui->verticalLayout->addWidget(text_capcha);

    image_capcha = new ImageCapcha(this);
    image_capcha->generateOnServer(socket);
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

void gui::on_pushButton_2_clicked()
{
    if (ui->tabWidget->currentWidget() == ui->tab)
        text_capcha->generateOnServer(socket);
    else image_capcha->generateOnServer(socket);
    ui->lineEdit->clear();
}


void gui::on_lineEdit_returnPressed()
{
    text_capcha->setUserInput(ui->lineEdit->text());
    text_capcha->callPopup();
    try {
        text_capcha->generateOnServer(socket);
    } catch (const std::string error_msg) {
        error_handler.callPopup(error_msg);
    }
    ui->lineEdit->clear();
}


void gui::on_pushButton_clicked()
{    
    if (ui->tabWidget->currentWidget() == ui->tab) {
        text_capcha->callPopup();
        text_capcha->generateOnServer(socket);
    }
    else {
        image_capcha->callPopup();
        image_capcha->generateOnServer(socket);
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

