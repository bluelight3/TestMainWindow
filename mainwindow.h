#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myitem.h"
#include "myview.h"
#include "global.h"
#include <QComboBox>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QFontComboBox>
#include <QToolBox>
#include <QButtonGroup>
#include <QToolButton>
#include <QLabel>
#include "diagramitem.h"
#include <QHoverEvent>
#include "mytextitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    MyView *m_view;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fontColorToolButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;
    QMenu *itemMenu;
    QLabel *m_label;
    QLabel *m_label2;
    QLabel *m_myTextLabel;


    // 自定义图元
    MyItem * myItem1;
    MyItem * myItem2;
    MyTextItem *myTextItem;

    int m_myItem1_count;
    int m_myItem2_count;


    QGraphicsItem * m_selectItem;
    QGraphicsScene* m_scene;
    QMap<QLabel*,QGraphicsItem*> qmap_myItem;
    QVector<QGraphicsItem*>* qvec_MyItemOnView = new QVector<QGraphicsItem*>;  // 在界面上显示的Item


    // 文件项目相关 (打开，保存)
    QString m_projectName;
    QString m_projectSaveName;


    void createToolBox();
    void createToolbars();
    void buttonGroupClicked(int id);
    void initQMap();    // 初始化每个Label 和Item的对应 (目前想到的设计是图元栏里放Label用于拖动(Widget自定义拖动函数得重新设计一个Widget) )
    QWidget* createCellWidget(const QString &text, DiagramItem::DiagramType type);
    QWidget* createCellWidget_v2(const QString &text, MyItem::MyType type);   // 通过自定义item类来设计widget
    QWidget* createBackgroundCellWidget(const QString &text, const QString &image);


    void backgroundButtonGroupClicked(QAbstractButton *button);

protected:
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent* event);


public:
    bool eventFilter(QObject* obj,QEvent * event);
    void copyItem(QGraphicsItem* item);        //自定义函数 统一所有的复制最后调用的函数
    void pasteItem();

    void openProject();
    void saveProject(); //
    void saveAsProject();


private:
    Ui::MainWindow *ui;

signals:
//    void insertItem();

public slots:
    void acceptInsertItem();
    void acceptClipBoardInsertItem(QPointF point);
    void acceptClipBoardInsertItem(MyItem* myItem);
    void acceptClipBoardInsertTextItem(MyTextItem* myTextItem);
    void acceptClear();
    void testNew();
    void testOpen();
    void testSave();
    void testSaveAs();
    void testCut();
    void testCopy();
    void testPaste();

    void testShowStatus();
    void sceneScaleChanged(const QString &scale);


};
#endif // MAINWINDOW_H
