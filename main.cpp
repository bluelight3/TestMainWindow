#include "mainwindow.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(diagramscene);
    Q_INIT_RESOURCE(myimages);

    QApplication a(argc, argv);



    // 载入画面

    LoadWidget* m_loadWidget= new LoadWidget();
    MainWindow w;
#ifdef SHOW_LOADWIDGET
    QTimer::singleShot(10000,Qt::PreciseTimer,&w,&MainWindow::show);
    QTimer::singleShot(10000,Qt::PreciseTimer,m_loadWidget,&LoadWidget::closeWindow);


    m_loadWidget->setWindowModality(Qt::ApplicationModal); //设置阻塞类型
    m_loadWidget->setAttribute(Qt::WA_ShowModal, true);    //属性设置 true:模态 false:非模态
    m_loadWidget->show();
#else
    w.show();
#endif





    return a.exec();
}
