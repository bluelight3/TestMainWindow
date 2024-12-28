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

private:
    Mode m_myMode;
    MyItemWidget* myItemWidget;
signals:
    void setMyDragMode(); // 向View发送模式
};

#endif // CONTROL_H
