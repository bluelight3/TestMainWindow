#ifndef CONTROL_H
#define CONTROL_H
#include "global.h"
#include "myitemwidget.h"
#include "generateprojectform.h"
#include "generateprojectthread.h"
#include "searchwidget.h"
#include "cpumemorywidget.h"

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

    QVector<MyItem *> *getMyItems() const;
    bool m_bUpdateFlag;   // 表示界面是否更新过
    bool m_bNewProjectFlag;   // 表示是否是一个新的项目
    void showProperty(MyItem *myItem);
    void showMyItemWidget();


    void setSearchWidget(SearchWidget *mySearchWidget);
    SearchWidget *getSearchWidget() const;
    void createSearchWidget();
    void destroySearchWidget();




    CpuMemoryWidget *getCpuMemoryWidget() const;
    void setCpuMemoryWidget(CpuMemoryWidget *cpuMemoryWidget);
    void createCpuMemoryWidget();
    void destroyCpuMemoryWidget();

private:
    Mode m_myMode;
    MyItemWidget* m_myItemWidget;
    GenerateProjectForm* m_generateProjectForm;
    GenerateProjectThread* m_generateProjectThread;
    SearchWidget* m_searchWidget;
    CpuMemoryWidget* m_cpuMemoryWidget;

    QVector<MyItem *> *m_myItems;       //目前所创建的所有Items 现在交由controls管理

public slots:
    void closeMyGenerateProjectForm();

signals:
    void setMyDragMode(); // 向View发送模式
    void updateWindow();


};


#endif // CONTROL_H
