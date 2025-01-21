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
    m_generateProjectForm = new GenerateProjectForm();
}

void Control::destroyMyGenerateProjectForm()
{
    delete m_generateProjectForm;
}

void Control::closeMyGenerateProjectForm()
{
    m_generateProjectForm->close();
}

GenerateProjectForm *Control::getMyGenerateProjectForm() const
{
    return m_generateProjectForm;
}

void Control::setMyGenerateProjectForm(GenerateProjectForm *value)
{
    m_generateProjectForm = value;
}

void Control::createMyGenerateProjectThread()
{
    m_generateProjectThread = new GenerateProjectThread();

    connect(m_generateProjectThread,SIGNAL(generateProject(int)),
            m_generateProjectForm,SLOT(updateProgress(int)));
    connect(m_generateProjectThread,SIGNAL(generated()),
            this,SLOT(closeMyGenerateProjectForm()));
}

void Control::destroyMyGenerateProjectThread()
{
    delete m_generateProjectThread;
}

GenerateProjectThread *Control::getMyGenerateProjectThread() const
{
    return m_generateProjectThread;
}

void Control::setMyGenerateProjectThread(GenerateProjectThread *value)
{
    m_generateProjectThread = value;
}

void Control::runMyGenerateProjectThread()
{
    m_generateProjectThread->start();
}

QVector<MyItem *> *Control::getMyItems() const
{
    return m_myItems;
}



void Control::showMyItemWidget()
{
    m_myItemWidget->show();
}

void Control::setSearchWidget(SearchWidget *mySearchWidget)
{
    m_searchWidget = mySearchWidget;
}

void Control::createSearchWidget()
{
    m_searchWidget = new SearchWidget;
}

void Control::destroySearchWidget()
{
    delete m_searchWidget;
}

CpuMemoryWidget *Control::getCpuMemoryWidget() const
{
    return m_cpuMemoryWidget;
}

void Control::setCpuMemoryWidget(CpuMemoryWidget *cpuMemoryWidget)
{
    m_cpuMemoryWidget = cpuMemoryWidget;
}

void Control::createCpuMemoryWidget()
{
    m_cpuMemoryWidget = new CpuMemoryWidget;
}

void Control::destroyCpuMemoryWidget()
{
    delete m_cpuMemoryWidget;
}

SearchWidget *Control::getSearchWidget() const
{
    return m_searchWidget;
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

    QObject::connect(m_myItemWidget,SIGNAL(setToggle(QString)),myItem,SLOT(acceptSetToggle(QString)));
    QObject::connect(m_myItemWidget,SIGNAL(setName(QString)),myItem,SLOT(acceptSetName(QString)));

    showMyItemWidget();
}
