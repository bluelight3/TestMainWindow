#ifndef MYITEMWIDGET_H
#define MYITEMWIDGET_H

#include <QWidget>
#include "myitem.h"

namespace Ui {
class MyItemWidget;
}

class MyItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyItemWidget(QWidget *parent = nullptr);
    ~MyItemWidget();
    void setItemName(QString myItemName);
    void setItemToggle(QString myToggle);
    void setItemType(int myType);
    void setItemPixMap(QPixmap myPixmap);
    void setTitleName(QString myTitleName);

protected:
    // 拖拽实现窗口移动
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:

    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

    void closeWindow();

private:
    Ui::MyItemWidget *ui;

    QPoint windowPositionBeforeMoving;
    QPoint mousePressedPosition;

signals:
    void setToggle(QString toggle); // 将设置好的注释返回设置到Item上
    void setName(QString name);     // 将设置好的名称返回设置到Item上

};

#endif // MYITEMWIDGET_H
