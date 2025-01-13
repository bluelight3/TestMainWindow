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
    ~Control();

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



    QVector<MyItem *> *getMyItems() const;

private:
    Mode m_myMode;
    MyItemWidget* m_myItemWidget;
    GenerateProjectForm* m_myGenerateProjectForm;
    GenerateProjectThread* m_myGenerateProjectThread;
    QVector<MyItem *> *m_myItems;       //目前所创建的所有Items 现在交由controls管理

signals:
    void setMyDragMode(); // 向View发送模式


public slots:
    void closeMyGenerateProjectForm();
};

#endif // CONTROL_H
