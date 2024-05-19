#ifndef IMAGECAPCHA_H
#define IMAGECAPCHA_H

#include "Capcha.h"
#include <QDirIterator>
#include <QIcon>
#include <QPushButton>
#include <QGridLayout>
#include <QRandomGenerator>

class ImageCapcha : public Capcha {
    Q_OBJECT

    QGridLayout* gridLayout;
    QVector<QString> imagesPool;
    const int max_images = 12, max_column = 4;
    int need_presses = 0;
    int current_presses = 0;

    void setButtonStyle(QPushButton* button, bool selected) {
        button->setStyleSheet(
            (selected) ? "background-color: blue;" : "background-color: transparent");
    }

    void getImagesPool(const QString& directoryPath) {
        QDirIterator iterator(directoryPath, QStringList() << "*.png" << "*.jpg", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        while (iterator.hasNext()) {
            imagesPool.append(iterator.next());
        }
    }

    QVector<QString> getRandomImagesPaths() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(imagesPool.begin(), imagesPool.end(), g);

        return QVector(imagesPool.begin(), imagesPool.begin() + max_images);
    }

    QPushButton* formButton(QString& imagePath, int row, int column) {
        need_presses |= imagePath.contains("panda") * 1 << (row * max_column + column);
        QIcon icon(imagePath);
        QPushButton* button = new QPushButton(icon, "", this);
        button->setFixedSize(QSize(90, 90));
        button->setIconSize(QSize(85, 85));
        button->setCheckable(true);
        connect(button, &QPushButton::toggled, this,
                [button, row, column, this] { updatePressState(button, row, column); });
        return button;
    }

    void populateGridWithImages() {
        QVector<QString> imagesPaths = getRandomImagesPaths();

        int row = 0, column = 0;
        foreach (QString imagePath, imagesPaths) {
            if (column >= max_column) { column = 0; row++; }

            QPushButton* button = formButton(imagePath, row, column);
            gridLayout->addWidget(button, row, column);
            column++;
        }
    }
    bool isValid(const QString& input) const override {
        return need_presses == current_presses;
    }

    ~ImageCapcha() {
        delete gridLayout;
    }

    QString getProjectPath() {
        QString fullPath = QDir::currentPath();
        QDir dir(fullPath);
        while (!dir.isRoot() && !dir.path().endsWith("capcha"))
            dir.cdUp();
        return dir.path();
    }
public:
    explicit ImageCapcha(QWidget *parent = nullptr) : Capcha(parent), gridLayout(new QGridLayout(this)) {
        getImagesPool(getProjectPath() + "/imgs/");
        gridLayout->setSpacing(15);

        // connect(gridLayout, &QGridLayout::itemAtPosition, this, &ImageCapcha::onItemMoved);
        // for (int i = 0; i < 10; ++i) {
        //     QObject::connect(gridLayout->itemAtPosition(row, column + i), &QPushButton::clicked, this, [this, i]() { onButtonClick(i); });
        // }
    }

    void generate() override {
        need_presses = current_presses = 0;
        populateGridWithImages();
    }
public slots:
    void updatePressState(QPushButton* button, int row, int column) {
        int current_bit = 1 << (row * max_column + column);
        current_presses ^= current_bit;
        // button->hide();
        setButtonStyle(button, current_presses & current_bit);
    }
};

#endif // IMAGECAPCHA_H
