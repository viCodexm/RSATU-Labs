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

QString getProjectPath() {
    QString fullPath = QDir::currentPath();
    QDir dir(fullPath);
    while (!dir.isRoot() && !dir.path().endsWith("capcha"))
        dir.cdUp();
    return dir.path();
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
    QString path = getRandomImagePath(getProjectPath() + "/imgs/");
    ui->label->setStyleSheet("background-image: url(" + path + "); color: rgba(255, 0, 0, 1);");
}


gui::~gui()
{
    delete ui;
    delete capchaWidget;
}

void gui::on_pushButton_2_clicked()
{
    capchaWidget->generate();
    image_capcha->generate();
    ui->lineEdit->clear();
}


void gui::on_lineEdit_returnPressed()
{
    capchaWidget->callPopup(ui->lineEdit->text());
    capchaWidget->generate();
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

