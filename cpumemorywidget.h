#ifndef CPUMEMORYWIDGET_H
#define CPUMEMORYWIDGET_H

#include <QWidget>
#include "global.h"
#include "MyHelper.h"

namespace Ui {
class CpuMemoryWidget;
}

class CpuMemoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CpuMemoryWidget(QWidget *parent = nullptr);
    ~CpuMemoryWidget();

private:
    Ui::CpuMemoryWidget *ui;


private slots:
    void initForm();
    //cpu和内存占用情况数值改变信号

};

#endif // CPUMEMORYWIDGET_H
