#ifndef CONTROL_H
#define CONTROL_H
#include "global.h"
#include "myitemwidget.h"
#include "generateprojectform.h"
#include "generateprojectthread.h"


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
    void createMyGenerateProjectForm();
    void destroyMyGenerateProjectForm();

    GenerateProjectForm *getMyGenerateProjectForm() const;
    void setMyGenerateProjectForm(GenerateProjectForm *value);

    void createMyGenerateProjectThread();
    void destroyMyGenerateProjectThread();
    GenerateProjectThread *getMyGenerateProjectThread() const;
    void setMyGenerateProjectThread(GenerateProjectThread *value);
    void runMyGenerateProjectThread();

private:
    Mode m_myMode;
    MyItemWidget* m_myItemWidget;
    GenerateProjectForm* m_myGenerateProjectForm;
    GenerateProjectThread* m_myGenerateProjectThread;
signals:
    void setMyDragMode(); // 向View发送模式


public slots:
    void closeMyGenerateProjectForm();
};

#endif // CONTROL_H
