#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    ui->listWidget->addItem(text);
}

void MainWindow::on_pushButton_2_clicked()
{
    QList<QListWidgetItem*> reversedItems;

    QListWidgetItem* item;
    for (int i = ui->listWidget->count() - 1; i >= 0; --i) {
        item = ui->listWidget->takeItem(i);
        reversedItems.append(item);
    }

    ui->listWidget->clear();

    for (QListWidgetItem* item : reversedItems) {
        ui->listWidget->addItem(item);
    }
}


void MainWindow::on_textEdit_textChanged() {}


void MainWindow::on_listWidget_currentRowChanged(int currentRow) {}


void MainWindow::on_pushButton_3_clicked()
{
    double sum = 0.0;
        QString concatenation;

        for (int i = 0; i < ui->listWidget->count(); ++i) {
            QListWidgetItem* item = ui->listWidget->item(i);
            bool ok;
            double value = item->text().toDouble(&ok);
            if (ok) {
                sum += value;
            }
            else concatenation += item->text() + " ";
        }

        ui->textBrowser->clear();
        ui->textBrowser->append("Сумма чисел: " + QString::number(sum));
        ui->textBrowser->append("Конкатенация строк: " + concatenation);
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int index = ui->listWidget->row(item);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удаление элемента", "Вы уверены, что хотите удалить выбранный элемент?",
                                 QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QListWidgetItem *it = ui->listWidget->takeItem(index);
        delete it;
    }
}


