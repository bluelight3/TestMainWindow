#ifndef MYITEMIDGET_H
#define MYITEMIDGET_H

#include <QWidget>

namespace Ui {
class MyItemidget;
}

class MyItemidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyItemidget(QWidget *parent = nullptr);
    ~MyItemidget();

    void setItemName(QString itemName);
    void setItemToggle(QString itemToggle);
    void setItemMyType(int i);
    void setItemPixmap(QPixmap pixmap);

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::MyItemidget *ui;
};

#endif // MYITEMIDGET_H
