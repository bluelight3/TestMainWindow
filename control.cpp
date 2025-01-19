#include "control.h"

Control::Control()
{

    m_myItems = new QVector<MyItem *>;
    m_myMode = nullItem;

    m_bUpdateFlag = false;
    m_bNewProjectFlag = true;

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
//    connect(myItemWidget,&MyItemWidget::setToggle,&w,&MainWindow::setItemToggle);
}

void Control::destroyMyItemWidget()
{
    delete m_myItemWidget;
}

void Control::createMyGenerateProjectForm()
{
    m_myGenerateProjectForm = new GenerateProjectForm();
}

void Control::destroyMyGenerateProjectForm()
{
    delete m_myGenerateProjectForm;
}

void Control::closeMyGenerateProjectForm()
{
    m_myGenerateProjectForm->close();
}

GenerateProjectForm *Control::getMyGenerateProjectForm() const
{
    return m_myGenerateProjectForm;
}

void Control::setMyGenerateProjectForm(GenerateProjectForm *value)
{
    m_myGenerateProjectForm = value;
}

void Control::createMyGenerateProjectThread()
{
    m_myGenerateProjectThread = new GenerateProjectThread();

    connect(m_myGenerateProjectThread,SIGNAL(generateProject(int)),
            m_myGenerateProjectForm,SLOT(updateProgress(int)));
    connect(m_myGenerateProjectThread,SIGNAL(generated()),
            this,SLOT(closeMyGenerateProjectForm()));
}

void Control::destroyMyGenerateProjectThread()
{
    delete m_myGenerateProjectThread;
}

GenerateProjectThread *Control::getMyGenerateProjectThread() const
{
    return m_myGenerateProjectThread;
}

void Control::setMyGenerateProjectThread(GenerateProjectThread *value)
{
    m_myGenerateProjectThread = value;
}

void Control::runMyGenerateProjectThread()
{
    m_myGenerateProjectThread->start();
}

QVector<MyItem *> *Control::getMyItems() const
{
    return m_myItems;
}



void Control::showMyItemWidget()
{
    m_myItemWidget->show();
}

void Control::setMySearchWidget(SearchWidget *mySearchWidget)
{
    m_mySearchWidget = mySearchWidget;
}

void Control::createMySearchWidget()
{
    m_mySearchWidget = new SearchWidget;
}

void Control::destroyMySearchWidget()
{
    delete m_mySearchWidget;
}

SearchWidget *Control::getMySearchWidget() const
{
    return m_mySearchWidget;
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
