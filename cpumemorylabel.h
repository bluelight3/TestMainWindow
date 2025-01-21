#ifndef CPUMEMORYLABEL_H
#define CPUMEMORYLABEL_H

#include <QObject>
#include "global.h"
#include <QLabel>

class CpuMemoryLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CpuMemoryLabel(QWidget *parent = 0);
    ~CpuMemoryLabel();

private:
    quint64 m_totalNew;
    quint64 m_idleNew;
    quint64 m_totalOld;
    quint64 m_idleOld;

    quint64 m_cpuPercent;     //CPU百分比
    quint64 m_memoryPercent;  //内存百分比
    quint64 m_memoryAll;      //所有内存
    quint64 m_memoryUse;      //已用内存
    quint64 m_memoryFree;     //空闲内存

    QTimer *m_timerCPU;       //定时器获取CPU信息
    QTimer *m_timerMemory;    //定时器获取内存信息
    QProcess *m_process;      //执行命令行

    bool m_bShowText;          //自己显示值

private slots:
    void getCPU();          //获取cpu
    void getMemory();       //获取内存
    void readData();        //读取数据
    void setData();         //设置数据

public:
    //默认尺寸和最小尺寸
    QSize sizeHint() const;
    QSize minimumSizeHint() const;



public slots:
    //开始启动服务
    void start(int interval);
    //停止服务
    void stop();

};

#endif // CPUMEMORYLABEL_H
