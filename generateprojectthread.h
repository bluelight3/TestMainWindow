#ifndef GENERATEPROJECTTHREAD_H
#define GENERATEPROJECTTHREAD_H

#include <QObject>
#include <QThread>
#include "global.h"


//该线程要有办法去访问主界面的参数

class GenerateProjectThread : public QThread
{
    Q_OBJECT
public:
    GenerateProjectThread(QObject * parent = 0);
    void stop();
    int generateProgress() const;
    void setGenerateProgress(int generateProgress);


protected:
    void run() override;
private:
    volatile bool m_stopped;
    bool m_generated;
    int m_generateProgress;

signals:
    void generateProject(int i);
    void generated();
};

#endif // GENERATEPROJECTTHREAD_H
