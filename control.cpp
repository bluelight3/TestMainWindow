#include "control.h"

Control::Control()
{
    m_myMode = nullItem;
}

Mode Control::getMyMode() const
{
    return m_myMode;
}

void Control::setMyMode(const Mode &value)
{
    m_myMode = value;
    emit setMyDragMode();
}

MyItemWidget *Control::getMyItemWidget() const
{
    return myItemWidget;
}

void Control::setMyItemWidget(MyItemWidget *value)
{
    myItemWidget = value;
}

void Control::createMyItemWidget()
{
    myItemWidget = new MyItemWidget();
}

void Control::destroyMyItemWidget()
{
    delete myItemWidget;
}
