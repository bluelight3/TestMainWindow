#include "generateprojectthread.h"
#include "mainwindow.h"
QByteArray MainWindow::generateProjectBit;

GenerateProjectThread::GenerateProjectThread(QObject * parent)
{
    m_generateProgress = 0;
    m_stopped = false;
    m_generated = false;
}

void GenerateProjectThread::stop()
{
    m_stopped = true;
}

void GenerateProjectThread::run()
{
    // 具体的生成Project实现
    // 主界面生成一个静态成员变量供生成线程调用
    QByteArray tmpBit = MainWindow::generateProjectBit;

    while (!m_stopped) {
        // 根据tmpbit进行Project生成工作
        usleep(30*1000);
        m_generateProgress ++;
        //
        qDebug() << QString("in MyThread: %1" ).arg(m_generateProgress);
        emit generateProject(m_generateProgress);
        if (m_generateProgress == 100)
        {
            m_generateProgress = 0;
            emit generated();
            break;
        }
    }
    m_generated = true;
    m_stopped = false;
}

int GenerateProjectThread::generateProgress() const
{
    return m_generateProgress;
}

void GenerateProjectThread::setGenerateProgress(int generateProgress)
{
    m_generateProgress = generateProgress;
}
