#ifndef MYITEMIDGET_H
#define MYITEMIDGET_H

#include <QWidget>
#include "global.h"
#include <qdrawutil.h>

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
    void setTitleName(QString titleName);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

    void on_btn_close_clicked();

private:
    Ui::MyItemidget *ui;

    QPoint windowPositionBeforeMoving; // 移动窗口前窗口左上角的坐标
    QPoint mousePressedPosition;       // 按下鼠标时鼠标的全局坐标
};

#endif // MYITEMIDGET_H
