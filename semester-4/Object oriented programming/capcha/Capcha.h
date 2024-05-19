#ifndef CAPCHA_H
#define CAPCHA_H

#include <QWidget>

class Capcha : public QWidget
{
    Q_OBJECT
    virtual bool isValid(const QString& input) const = 0;
public:
    explicit Capcha(QWidget *parent = nullptr);
    virtual void generate() = 0;
    void callPopup(const QString& input) const;

signals:
    void capchaGenerated(QString capcha_text);
};

#endif // CAPCHA_H
