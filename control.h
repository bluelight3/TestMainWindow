#ifndef CONTROL_H
#define CONTROL_H
#include "global.h"
#include "myitemwidget.h"

enum Mode { InsertItem, InsertLine, InsertText, MoveItem,nullItem};
class Control : public QObject
{
    Q_OBJECT

public:
    Control();

    Mode getMyMode() const;
    void setMyMode(const Mode &value);

    MyItemWidget *getMyItemWidget() const;
    void setMyItemWidget(MyItemWidget *value);
    void createMyItemWidget();
    void destroyMyItemWidget();
    void showMyItemWidget();    //显示属性框
    void showProperty(MyItem* myItem);

    bool m_bUpdateFlag;   // 表示界面是否更新过
private:
    Mode m_myMode;
    MyItemWidget* m_myItemWidget;

signals:
    void setMyDragMode(); // 向View发送模式
    void updateWindow();
};

#endif // CONTROL_H
