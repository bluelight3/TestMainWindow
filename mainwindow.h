#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myitem.h"
#include "myview.h"
#include <QComboBox>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QFontComboBox>
#include <QToolBox>
#include <QButtonGroup>
#include <QToolButton>
#include <QLabel>
#include <QHoverEvent>
#include "diagramitem.h"
#include "diagramtextitem.h"
#include "mytextitem.h"
#include "control.h"
#include "generateprojectform.h"

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
    QLabel *m_labelText;
    QLabel *m_labelText2;


    void createToolBox();
    void buttonGroupClicked(int id);
    void initQMap();    // 初始化每个Label 和Item的对应 (目前想到的设计是图元栏里放Label用于拖动(Widget自定义拖动函数得重新设计一个Widget) )
    QWidget* createCellWidget(const QString &text, DiagramItem::DiagramType type);
    QWidget* createCellWidget_v2(const QString &text, MyItem::MyType type);   // 通过自定义item类来设计widget
    QWidget* createBackgroundCellWidget(const QString &text, const QString &image);

    void backgroundButtonGroupClicked(QAbstractButton *button);
    void unselectAllshowedItem();
    void generateProject();

protected:
    void mousePressEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent* event);


public:
    bool eventFilter(QObject* obj,QEvent * event);
    static QByteArray generateProjectBit;       // 假设也会生成一段比特流

private:
    Ui::MainWindow *ui;


    // 自定义图元
    MyItem * myItem1;
    MyItem * myItem2;
    DiagramTextItem *myDiagramTextItem;
    MyTextItem* myTextItem;

    int m_myItem1_count;
    int m_myItem2_count;
    QGraphicsItem * m_selectedItem;
    QGraphicsScene* m_scene;
    QMap<QLabel*,QGraphicsItem*> qmap_myItem;
    QVector<QGraphicsItem*>* qvec_MyItemOnView;  // 在界面上显示的Item
    int m_updateProgressValue = 0;


signals:
    void setMyDragMode(Mode m_myMode);
//    void itemSelected(QGraphicsItem *item); // 我们没有自定义scene这里不需要进行转发

public:
    void removeItems(QList<QGraphicsItem>* myItems);

public slots:
    void acceptInsertItem();
    void acceptInsertTextItem();    // 添加文本Item 注释更新用
    void acceptClipBoardInsertItem(QPointF point);
    void acceptClipBoardInsertItem(QGraphicsItem* myItem);
    void acceptClear();
    void acceptRemoveItem(QGraphicsItem* myItem);
    void acceptSelectItem(QGraphicsItem* myItem);
    void showStatus();  //显示当前状态 (仅调试用)
    void editorLostFocus(DiagramTextItem *item);
    void acceptAddArrow(Arrow* myItem);
    void setItemToggle(QString toggle);

private slots:
    void testNew();
    void testOpen();
    void testSave();
    void testCut();
    void testCopy();
    void testPaste();
    void testDelete();
    void testConnectLine();
    void testBrush();
    void testGenerateProject();

    void itemSelected(QGraphicsItem *item);
    void myItemSelected();          // 仅表示有Item被选中

};
#endif // MAINWINDOW_H
