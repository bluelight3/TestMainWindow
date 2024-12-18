#ifndef MYITEMWIDGET_H
#define MYITEMWIDGET_H

#include <QWidget>

namespace Ui {
class MyItemWidget;
}

class MyItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyItemWidget(QWidget *parent = nullptr);
    ~MyItemWidget();

private:
    Ui::MyItemWidget *ui;
};

#endif // MYITEMWIDGET_H
