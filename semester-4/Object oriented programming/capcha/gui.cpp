#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    ui->setupUi(this);

    capchaWidget = new TextCapcha(this);
    connect(capchaWidget, &TextCapcha::capchaGenerated, this, &gui::updateCapchaDisplay);

    capchaWidget->generate();
    ui->verticalLayout->addWidget(capchaWidget);

    image_capcha = new ImageCapcha(this);
    image_capcha->generate();
    image_capcha->show();
    ui->verticalLayout->addWidget(image_capcha);
}

QString getRandomImagePath(QString path) {
    QVector<QString> imagesPool;
    QDirIterator iterator(path, QStringList() << "*.png" << "*.jpg", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        imagesPool.append(iterator.next());
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(imagesPool.begin(), imagesPool.end(), g);

    return *imagesPool.begin();
}

void gui::updateCapchaDisplay(QString capchaText) {
    ui->label->setText(capchaText);
    QString path = getRandomImagePath(project::getProjectPath() + "/imgs/");
    ui->label->setStyleSheet("background-image: url(" + path + "); color: rgba(255, 0, 0, 1);");
}


gui::~gui()
{
    delete ui;
    delete capchaWidget;
}

void gui::on_pushButton_2_clicked()
{
    if (ui->tabWidget->currentWidget() == ui->tab)
        capchaWidget->generate();
    else image_capcha->generate();
    ui->lineEdit->clear();
}


void gui::on_lineEdit_returnPressed()
{
    capchaWidget->callPopup(ui->lineEdit->text());
    try {
        capchaWidget->generate();
    } catch (const std::string error_msg) {
        error_handler.callPopup(error_msg);
    }
    ui->lineEdit->clear();
}


void gui::on_pushButton_clicked()
{    
    if (ui->tabWidget->currentWidget() == ui->tab) {
        capchaWidget->callPopup(ui->lineEdit->text());
        capchaWidget->generate();
    }
    else {
        image_capcha->callPopup("");
        image_capcha->generate();
    }
    ui->lineEdit->clear();
}


// о программе
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

