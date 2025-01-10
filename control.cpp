#include "control.h"
#include "mainwindow.h"

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
