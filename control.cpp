#include "control.h"

Control::Control()
{
    m_myMode = nullItem;

    m_bUpdateFlag = false;


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
    return m_myItemWidget;
}

void Control::setMyItemWidget(MyItemWidget *value)
{
    m_myItemWidget = value;
}

void Control::createMyItemWidget()
{
    m_myItemWidget = new MyItemWidget();
}

void Control::destroyMyItemWidget()
{
    delete m_myItemWidget;
}

void Control::showMyItemWidget()
{
    m_myItemWidget->show();
}

void Control::showProperty(MyItem *myItem)
{
    if(!m_myItemWidget)
        createMyItemWidget();
    MyItemWidget* m_myItemWidget = getMyItemWidget();

    m_myItemWidget->setItemName(myItem->name());
    m_myItemWidget->setItemType(myItem->diagramType());
    m_myItemWidget->setItemToggle(myItem->toggle());
    m_myItemWidget->setItemPixMap(myItem->image());
    m_myItemWidget->setTitleName(myItem->name());

    QObject::connect(m_myItemWidget,SIGNAL(setToggle(QString)),this,SLOT(acceptSetToggle(QString)));
    QObject::connect(m_myItemWidget,SIGNAL(setName(QString)),this,SLOT(acceptSetName(QString)));

    showMyItemWidget();
}
