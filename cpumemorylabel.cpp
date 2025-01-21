#include "cpumemorylabel.h"
#ifdef Q_OS_WIN
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#endif
#include "windows.h"
#endif

#define MB (1024 * 1024)
#define KB (1024)



CpuMemoryLabel::CpuMemoryLabel(QWidget *parent): QLabel(parent)
{
    m_totalNew = m_idleNew = m_totalOld = m_idleOld = 0;

    m_cpuPercent = 0;
    m_memoryPercent = 0;
    m_memoryAll = 0;
    m_memoryUse = 0;

    //获取CPU占用情况定时器
    m_timerCPU = new QTimer(this);
    connect(m_timerCPU, SIGNAL(timeout()), this, SLOT(getCPU()));

    //获取内存占用情况定时器
    m_timerMemory = new QTimer(this);
    connect(m_timerMemory, SIGNAL(timeout()), this, SLOT(getMemory()));

    //执行命令获取
    m_process = new QProcess(this);
    connect(m_process, SIGNAL(readyRead()), this, SLOT(readData()));

    m_bShowText = true;
}

CpuMemoryLabel::~CpuMemoryLabel()
{
    this->stop();
}

void CpuMemoryLabel::getCPU()
{
#ifdef Q_OS_WIN
#if 0
    static FILETIME lastIdleTime;
    static FILETIME lastKernelTime;
    static FILETIME lastUserTime;

    FILETIME newIdleTime;
    FILETIME newKernelTime;
    FILETIME newUserTime;

    //采用GetSystemTimes获取的CPU占用和任务管理器的不一致
    GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);

    int offset = 31;
    quint64 a, b;
    quint64 idle, kernel, user;

    a = (lastIdleTime.dwHighDateTime << offset) | lastIdleTime.dwLowDateTime;
    b = (newIdleTime.dwHighDateTime << offset) | newIdleTime.dwLowDateTime;
    idle = b - a;

    a = (lastKernelTime.dwHighDateTime << offset) | lastKernelTime.dwLowDateTime;
    b = (newKernelTime.dwHighDateTime << offset) | newKernelTime.dwLowDateTime;
    kernel = b - a;

    a = (lastUserTime.dwHighDateTime << offset) | lastUserTime.dwLowDateTime;
    b = (newUserTime.dwHighDateTime << offset) | newUserTime.dwLowDateTime;
    user = b - a;

    cpuPercent = float(kernel + user - idle) * 100 / float(kernel + user);

    lastIdleTime = newIdleTime;
    lastKernelTime = newKernelTime;
    lastUserTime = newUserTime;
    this->setData();
#else
    //获取系统版本区分win10
    bool win10 = false;
#if (QT_VERSION >= QT_VERSION_CHECK(5,4,0))
    win10 = (QSysInfo::productVersion().mid(0, 2).toInt() >= 10);
#else
    win10 = (QSysInfo::WindowsVersion >= 192);
#endif

    QString cmd = "\\Processor(_Total)\\% Processor Time";
    if (win10) {
        cmd = "\\Processor Information(_Total)\\% Processor Utility";
    }

    if (m_process->state() == QProcess::NotRunning) {
        m_process->start("typeperf", QStringList() << cmd);
    }
#endif

#elif defined(Q_OS_UNIX) && !defined(Q_OS_WASM)
    if (process->state() == QProcess::NotRunning) {
        totalNew = idleNew = 0;
        process->start("cat", QStringList() << "/proc/stat");
    }
#endif
}

void CpuMemoryLabel::getMemory()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    m_memoryPercent = statex.dwMemoryLoad;
    m_memoryAll = statex.ullTotalPhys / MB;
    m_memoryFree = statex.ullAvailPhys / MB;
    m_memoryUse = m_memoryAll - m_memoryFree;
    this->setData();

#elif defined(Q_OS_UNIX) && !defined(Q_OS_WASM)
    if (process->state() == QProcess::NotRunning) {
        process->start("cat", QStringList() << "/proc/meminfo");
    }
#endif
}

void CpuMemoryLabel::readData()
{
#ifdef Q_OS_WIN
    while (!m_process->atEnd()) {
        QString s = QLatin1String(m_process->readLine());
        s = s.split(",").last();
        s.replace("\r", "");
        s.replace("\n", "");
        s.replace("\"", "");
        if (!s.isEmpty() && s.length() < 10) {
            m_cpuPercent = qRound(s.toFloat());
        }
    }
#elif defined(Q_OS_UNIX) && !defined(Q_OS_WASM)
    while (!process->atEnd()) {
        QString s = QLatin1String(process->readLine());
        if (s.startsWith("cpu")) {
            QStringList list = s.split(" ");
            idleNew = list.at(5).toUInt();
            foreach (QString value, list) {
                totalNew += value.toUInt();
            }

            quint64 total = totalNew - totalOld;
            quint64 idle = idleNew - idleOld;
            cpuPercent = 100 * (total - idle) / total;
            totalOld = totalNew;
            idleOld = idleNew;
            break;
        } else if (s.startsWith("MemTotal")) {
            s.replace(" ", "");
            s = s.split(":").at(1);
            memoryAll = s.left(s.length() - 3).toUInt() / KB;
        } else if (s.startsWith("MemFree")) {
            s.replace(" ", "");
            s = s.split(":").at(1);
            memoryFree = s.left(s.length() - 3).toUInt() / KB;
        } else if (s.startsWith("Buffers")) {
            s.replace(" ", "");
            s = s.split(":").at(1);
            memoryFree += s.left(s.length() - 3).toUInt() / KB;
        } else if (s.startsWith("Cached")) {
            s.replace(" ", "");
            s = s.split(":").at(1);
            memoryFree += s.left(s.length() - 3).toUInt() / KB;
            memoryUse = memoryAll - memoryFree;
            memoryPercent = 100 * memoryUse / memoryAll;
            break;
        }
    }
#endif
    this->setData();
}

void CpuMemoryLabel::setData()
{
    //cpuPercent = (cpuPercent < 0 ? 0 : cpuPercent);
    m_cpuPercent = (m_cpuPercent > 100 ? 0 : m_cpuPercent);
    QString msg = QString("CPU %1%  Mem %2% ( 已用 %3 MB / 共 %4 MB )").arg(m_cpuPercent).arg(m_memoryPercent).arg(m_memoryUse).arg(m_memoryAll);
    if (m_bShowText) {
        this->setText(msg);
    }

}

QSize CpuMemoryLabel::sizeHint() const
{
    return QSize(300, 30);
}

QSize CpuMemoryLabel::minimumSizeHint() const
{
    return QSize(30, 10);
}



void CpuMemoryLabel::start(int interval)
{
    getCPU();
    getMemory();

    if (!m_timerCPU->isActive()) {
        m_timerCPU->start(interval);
    }
    if (!m_timerMemory->isActive()) {
        m_timerMemory->start(interval + 1000);
    }
}

void CpuMemoryLabel::stop()
{
    m_process->close();
    if (m_timerCPU->isActive()) {
        m_timerCPU->stop();
    }
    if (m_timerMemory->isActive()) {
        m_timerMemory->stop();
    }
}
