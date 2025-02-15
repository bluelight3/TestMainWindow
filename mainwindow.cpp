#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMimeData>
#include <QDrag>
#include "MyHelper.h"
#include "global.h"

const int InsertTextButton = 10;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);






    // 初始化
    setAcceptDrops(true);



    m_selectItem = NULL;
    //

    //设置一个单独接收拖动标签
    m_label = new QLabel(this);
    QPixmap pix("D://codes//Qt_projects//TestMainWindow//images//new.png");
    m_label->setPixmap(pix);
    m_label->resize(pix.size());
    m_label->move(100,100);
    m_label->setAttribute(Qt::WA_DeleteOnClose);
    m_label->installEventFilter(this);

    m_label2 = new QLabel(this);
    QPixmap pix2("D://codes//Qt_projects//TestMainWindow//images//copy.png");
    m_label2->setPixmap(pix2);
    m_label2->resize(pix2.size());
    m_label2->move(100,100);
    m_label2->setAttribute(Qt::WA_DeleteOnClose);
    m_label2->installEventFilter(this);

    m_myTextLabel = new QLabel(this);

    QPixmap pix3=QPixmap("D://codes//Qt_projects//TestMainWindow//images//textpointer.png");
    m_myTextLabel->setPixmap(pix3);
    m_myTextLabel->resize(pix3.size());
    m_myTextLabel->move(100,100);
    m_myTextLabel->setAttribute(Qt::WA_DeleteOnClose);
    m_myTextLabel->installEventFilter(this);



    myItem1 = new MyItem;
    myItem1->setColor(Qt::blue);
    myItem1->setType(MyItem::MyTest1);
    myItem1->setName("test1_name");
    myItem1->setPoint(QPointF(0.0,0.0));
    myItem2 = new MyItem;
    myItem2->setColor(Qt::green);
    myItem2->setType(MyItem::MyTest2);
    myItem2->setName("test2_name");
    myItem2->setPoint(QPointF(0.0,0.0));

    myTextItem = new MyTextItem;
    //    myTextItem->setFont(  QFont("Times", 24 ) );
    myTextItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    myTextItem->setZValue(1000.0);
    myTextItem->setSelected(true);
    myTextItem->setFont(QFont("Times"));
    myTextItem->setDefaultTextColor(Qt::red);

    m_myItem1_count = 1;
    m_myItem2_count = 1;
    //
    createToolBox();

    QGraphicsScene scene;
    // 将图形项添加到场景中

    m_view =new MyView();
    m_scene = new QGraphicsScene();



    m_view->setScene(m_scene);
    m_scene->setSceneRect(QRectF(0,0,1920,1080));
    //    scene->addPixmap(QPixmap("C://Users//5510760lbw//Pictures//IP.png"));
    m_scene->setForegroundBrush(QColor(255,255,0,100));

    createToolbars();


    initQMap();

    // 这边设置信号，当指定图元项被拖动到界面时执行界面函数
    connect(m_view,SIGNAL(insertItem()),this, SLOT(acceptInsertItem())); // 当拖动到view上时调用view的insertItem信号，触发acceptInsertItem
    connect(m_view,SIGNAL(insertClipBordItem(QPointF)),this,SLOT(acceptClipBoardInsertItem(QPointF))); // 暂时复用粘贴栏
    connect(m_view,SIGNAL(insertClipBordItem(MyItem*)),this,SLOT(acceptClipBoardInsertItem(MyItem*))); // 暂时复用粘贴栏
    connect(m_view,SIGNAL(insertClipBoardTextItem(MyTextItem*)),this,SLOT(acceptClipBoardInsertTextItem(MyTextItem*)));
    connect(m_view,SIGNAL(clear()),this,SLOT(acceptClear())); // 暂时复用粘贴栏


    // 链接所有Action信号
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(testNew()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(testOpen()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(testSave()));
    connect(ui->actionSaveAs,SIGNAL(triggered()),this,SLOT(testSaveAs()));
    connect(ui->actionCut,SIGNAL(triggered()),this,SLOT(testCut()));
    connect(ui->actionCopy,SIGNAL(triggered()),this,SLOT(testCopy()));
    connect(ui->actionPaste,SIGNAL(triggered()),this,SLOT(testPaste()));
    connect(ui->actionDelete,SIGNAL(triggered()),this,SLOT(testDelete()));
    connect(ui->actionleftRotate,SIGNAL(triggered()),this,SLOT(testLeftRotate()));
    connect(ui->actionrightRotate,SIGNAL(triggered()),this,SLOT(testRightRotate()));
    connect(ui->actionToFront,SIGNAL(triggered()),this,SLOT(testToFront()));
    connect(ui->actionToBack,SIGNAL(triggered()),this,SLOT(testToBack()));
    connect(ui->actionBold,SIGNAL(triggered()),this,SLOT(testBold()));
    connect(ui->actionItalic,SIGNAL(triggered()),this,SLOT(testItalic()));
    connect(ui->actionUnderLine,SIGNAL(triggered()),this,SLOT(testUnderLine()));

    connect(ui->actionShowStatus,SIGNAL(triggered()),this,SLOT(testShowStatus()));


    //    m_view = ui->graphicsView;

    // 手动实现将几个图形项放入group
    //    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    //    group->addToGroup(item1);
    //    group->addToGroup(item2);
    //    group->setFlag(QGraphicsItem::ItemIsMovable);
    QHBoxLayout *layOut = new QHBoxLayout();
    layOut->addWidget(toolBox);
    layOut->addWidget(m_view);
    //    ui->graphicsView->setScene(&scene);
    //    ui->graphicsView->show();
    QWidget *widget = new QWidget;
    widget->setLayout(layOut);
    setCentralWidget(widget);
    //    widget->show();

}

MainWindow::~MainWindow()
{
    delete myItem1;
    delete myItem2;


    delete m_scene;
    delete m_view;
    delete qvec_MyItemOnView;

    delete ui;

}


void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::buttonGroupClicked);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_label,0,0);
    layout->addWidget(m_label2,0,1);
    layout->addWidget(createCellWidget(tr("Conditional"), DiagramItem::Conditional), 1, 0);
    layout->addWidget(createCellWidget(tr("Process"), DiagramItem::Step),1, 1);
    layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::Io), 2, 0);
    // added
    //    layout->addWidget(createCellWidget(tr("myitem1"),DiagramItem::MyTest1),3,0);
    //    layout->addWidget(createCellWidget(tr("myitem2"),DiagramItem::MyTest2),3,1);

    //    layout->addWidget(createCellWidget_v2(tr("myitem1"),MyItem::MyTest1),3,0);
    //    layout->addWidget(createCellWidget_v2(tr("myitem2"),MyItem::MyTest2),3,1);
    //    layout->addWidget(m_label,0,0);


    //! [21]

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 2, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);
    layout->addWidget(m_myTextLabel,3,0);


    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    backgroundButtonGroup = new QButtonGroup(this); //在createBackgroundCellWidget函数中添加对应button
    connect(backgroundButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::backgroundButtonGroupClicked);

    QGridLayout *backgroundLayout = new QGridLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
                                                           ":/images/background1.png"), 0, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                                                           ":/images/background2.png"), 0, 1);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                                                           ":/images/background3.png"), 1, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
                                                           ":/images/background4.png"), 1, 1);

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);


    //! [22]
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));


}


void MainWindow::createToolbars(){

    auto pointerToolbar = ui->toolBar;
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);


    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),this, SLOT(sceneScaleChanged(QString)));



    pointerToolbar->addWidget(sceneScaleCombo);
}
void MainWindow::buttonGroupClicked(int id)
{
    const QList<QAbstractButton *> buttons = buttonGroup->buttons();
    for (QAbstractButton *button : buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }
    //    if (id == InsertTextButton) {
    //        scene->setMode(DiagramScene::InsertText);
    //    } else {
    //        scene->setItemType(DiagramItem::DiagramType(id));
    //        scene->setMode(DiagramScene::InsertItem);
    //    }
}

void MainWindow::initQMap()
{
    qmap_myItem[m_label] = myItem1;
    qmap_myItem[m_label2] = myItem2;
    qmap_myItem[m_myTextLabel] = myTextItem;
}


QWidget *MainWindow::createCellWidget(const QString &text, DiagramItem::DiagramType type)
{

    DiagramItem item(type, itemMenu);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    //    item.image().save(text+".png");
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QWidget *MainWindow::createCellWidget_v2(const QString &text, MyItem::MyType type)
{
    MyItem item;
    QIcon icon(item.image());
    QToolButton *button = new QToolButton;

    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);

    buttonGroup->addButton(button, int(type));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);


    return widget;
}

QWidget *MainWindow::createBackgroundCellWidget(const QString &text, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 第一步：获取图片
    // 鼠标指针位置部件转换成QLabel
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    //    QLabel *child2 = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;
    if (!child->pixmap()) return;
    if (!child->inherits(("QLabel"))) return;
    QPixmap pixmap = *child->pixmap();
    // 自定义MIME类型
    QByteArray itemData;
    QDataStream dataStream(&itemData,QIODevice::WriteOnly); //创建数据流
    // 将图片信息，位置信息输入到字节数组中
    dataStream <<pixmap <<QPoint(event->pos() - child->pos());
    // 第三步：将数据放入QMimeData中
    QMimeData* mimeData = new QMimeData;
    // 第四步 将字节数组放入QMimeData中，此处Mime类型由自己定义
    mimeData->setData("myimage/png",itemData);
    QDrag * drag = new QDrag(this);  //创建QDrag 它用来移动数据
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    //    drag->setHotSpot(event->pos() - child->pos());
    // 第五步 给原图片添加阴影
    QPixmap tmpPixmap = pixmap;
    QPainter painter;            //创建QPainter，用来绘制QPixmap
    painter.begin(&tmpPixmap);
    painter.fillRect(pixmap.rect(),QColor(127,127,127,127));
    painter.end();
    child->setPixmap(tmpPixmap);
    // 添加，选定selectItem 变为选择Label对应的Item
    m_selectItem = qmap_myItem[child];
    // 第六步 具体的拖放操作，用exec函数不会影响主事件循环，因此界面不会被冻结 这里设置支持复制和移动，并设置默认动作是复制；
    // 图片被放下后，exec()函数返回操作类型，这个返回值由dropEvent()函数设置决定
    if (drag->exec(Qt::CopyAction | Qt::MoveAction,Qt::CopyAction) == Qt::MoveAction)
        child->close();
    else{
        child->show();
        child->setPixmap(pixmap);
    }

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("myimage/png")){
        event->setDropAction(Qt::CopyAction);       // 如果想要设置复制这里和下面函数设置成Qt::CopyAction即可
        event->accept();
    }
    else{
        event->ignore();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("myimage/png")){
        event->setDropAction(Qt::CopyAction);   // 如果想要设置复制这里和下面函数设置成Qt::CopyAction即可
        event->accept();
    }
    else{
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if (!m_view->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    {
        if (event->mimeData()->hasFormat("myimage/png")){
            QByteArray itemData = event->mimeData()->data("myimage/png");
            QDataStream dataStream(&itemData,QIODevice::ReadOnly);
            QPixmap pixmap;
            QPoint offset;
            dataStream >> pixmap >>offset;
            // 让图片移动到放下的位置，不设置的话，图片会默认显示在（0,0）点即窗口左上角。
            event->setDropAction(Qt::CopyAction);

            event->accept();
        }
    }
    else{
        event->ignore();
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this->m_label){
        if (event->type() == QEvent::HoverEnter)
        {
            setToolTip("label1");
        }
        else if (event->type() == QEvent::KeyPress){
            QKeyEvent * keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Up){
                QPoint currPoint = m_label->pos();
                this->m_label->move(currPoint + QPoint(0,-20));
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (obj == this->m_label2){
        if (event->type() == QEvent::HoverEnter)
        {
            setToolTip("label2");
        }
        else if (event->type() == QEvent::KeyPress){
            QKeyEvent * keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Up){
                QPoint currPoint = m_label->pos();
                this->m_label->move(currPoint + QPoint(0,-20));
                return true;
            }
            else{
                return false;
            }
        }
    }

    else
        return QWidget::eventFilter(obj,event);
}

void MainWindow::copyItem(QGraphicsItem *item)
{

    MyItem* myItem = dynamic_cast<MyItem*>( item);

    QByteArray itemData;
    QDataStream dataStream(&itemData,QIODevice::WriteOnly); //创建数据流
    // 将Item的相关参数放入到字节数组中
    dataStream << myItem->color()<<myItem->name()<<myItem->diagramType()<<myItem->point();
    // 将数据放入QMimeData中
    QMimeData* mimeData = new QMimeData;
    // 第四步 将字节数组放入QMimeData中，此处Mime类型由自己定义
    mimeData->setData("application/myItem",itemData);
    QClipboard* clipBoard = QApplication::clipboard(); // 自定义剪切板，只在view中实现做参考因此定义在这
    clipBoard->setMimeData(mimeData);
}

void MainWindow::pasteItem()
{
    QClipboard* clipBoard = QApplication::clipboard(); // 自定义剪切板，只在view中实现做参考因此定义在这
    const QMimeData* mimeData = clipBoard->mimeData();
    // 判断是否存在我们要的数据
    if (!mimeData->hasFormat("application/myItem")){
        return;
    }
    // 取出数据
    QByteArray itemData = mimeData->data("application/myItem");

    QDataStream dataStream(&itemData,QIODevice::ReadOnly);
    QColor color;
    QString name;
    MyItem::MyType myType;
    QPointF myPoint;

    dataStream >> color >>name >> myType >> myPoint;
    MyItem tmpItem;
    tmpItem.setColor(color);
    tmpItem.setName(name);
    tmpItem.setType(myType);
    tmpItem.setPoint(myPoint);

    acceptClipBoardInsertItem(&tmpItem);

}

/**********************************************
* @projectName   TestMainWindow
* @brief         摘要
* @func          defaultFunc
* @param         void
* @return        void
* @author        gl
* @date          2024-12-16
**********************************************/
void MainWindow::openProject()
{

}


/**********************************************
* @projectName   TestMainWindow
* @brief         摘要
* @func          defaultFunc
* @param         void
* @return        void
* @author        gl
* @date          2024-12-16
**********************************************/
void MainWindow::saveProject()
{

}


/**********************************************
* @projectName   TestMainWindow
* @brief         摘要
* @func          defaultFunc
* @param         void
* @return        void
* @author        gl
* @date          2024-12-16
**********************************************/
void MainWindow::saveAsProject()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,tr("Open File"),"D://codes//Qt_projects//testGraphics//saved",tr("Text File(*.txt)"));
    if(fileName == "")
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return;
    }
    else
    {
        // TODO:这里将界面的相关参数写入我们给的文件

        //        QTextStream textStream(&file);

        /////////

        QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
        file.close();
    }
}

void MainWindow::acceptInsertItem()
{

    //    if (!selectItem)
    //        return;
    // 基于已有Item生成一个新的Item，并显示在界面上

    MyItem* tmpItem = dynamic_cast<MyItem*>(m_selectItem);
    MyTextItem* tmpTextItem = dynamic_cast<MyTextItem*>(m_selectItem);

    if (tmpItem)
    {
        MyItem* newItem = new MyItem(tmpItem);
        if (newItem->diagramType() == MyItem::MyTest1)
            newItem->setName(newItem->name() + QString::number(m_myItem1_count++));
        else if (newItem->diagramType() == MyItem::MyTest2) {
            newItem->setName(newItem->name() + QString::number(m_myItem2_count++));
        }

        newItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
        m_scene->addItem(newItem);

    }
    if (tmpTextItem){
        MyTextItem* newInsertItem = new MyTextItem(tmpTextItem);
        newInsertItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
        newInsertItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        newInsertItem->setZValue(1000.0);
        newInsertItem->setFont(QFont("Times",24));
        newInsertItem->setDefaultTextColor(Qt::red);
        newInsertItem->setSelected(true);

        m_scene->addItem(newInsertItem);

    }


    qDebug()<<m_view->mapFromParent(this->mapFromGlobal(QCursor::pos()));


}

void MainWindow::acceptClipBoardInsertItem(QPointF point)
{
    return;
}

void MainWindow::acceptClipBoardInsertItem(MyItem *myItem)
{
    MyItem* tmpItem = new MyItem(myItem);

    if (tmpItem->diagramType() == MyItem::MyTest1)
    {
        tmpItem->setName(tmpItem->name() + QString::number(m_myItem1_count++));
        tmpItem->setColor(Qt::blue);
    }
    else if (tmpItem->diagramType() == MyItem::MyTest2) {
        tmpItem->setName(tmpItem->name() + QString::number(m_myItem2_count++));
        tmpItem->setColor(Qt::green);
    }

    tmpItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
    m_scene->addItem(tmpItem);
    m_scene->update();
    qvec_MyItemOnView->push_back(tmpItem);
}

void MainWindow::acceptClipBoardInsertTextItem(MyTextItem *myTextItem)
{
    MyTextItem* tmpTextItem = new MyTextItem(myTextItem);

//    if (tmpItem->diagramType() == MyItem::MyTest1)
//    {
//        tmpItem->setName(tmpItem->name() + QString::number(m_myItem1_count++));
//        tmpItem->setColor(Qt::blue);
//    }
//    else if (tmpItem->diagramType() == MyItem::MyTest2) {
//        tmpItem->setName(tmpItem->name() + QString::number(m_myItem2_count++));
//        tmpItem->setColor(Qt::green);
//    }

    tmpTextItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
    m_scene->addItem(tmpTextItem);
    qvec_MyItemOnView->push_back(tmpTextItem);
}

void MainWindow::acceptClear()
{
    m_scene->clear();
}

void MainWindow::testNew()
{

}

void MainWindow::testOpen()
{
    m_projectName = FileHelper::GetFileName("*.ini(配置文件)");

    // 实现在界面中打开该文件名，读取相关参数，并对整个程序进行相关配置
    openProject();
}

void MainWindow::testSave()
{
    saveProject();
}

void MainWindow::testSaveAs()
{
    saveAsProject();
}

void MainWindow::testCut()
{

}

void MainWindow::testCopy()
{
    QGraphicsItem* selectItem = m_scene->selectedItems().first();
    copyItem(selectItem);
}

void MainWindow::testPaste()
{
    pasteItem();
}

void MainWindow::testDelete()
{
    QGraphicsItem* selectedItem = m_scene->selectedItems().first();
    m_scene->removeItem(selectedItem);
}





/**********************************************
* @projectName   TestMainWindow
* @brief         左旋（逆时针）旋转90°
* @func          testLeftRotate()
* @param         void
* @return        void
* @author        gl
* @date          2024-12-20
**********************************************/
void MainWindow::testLeftRotate()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = m_scene->selectedItems().first();
    if( selectedItem->type()==QGraphicsItemGroup::Type ) return;
    selectedItem->setRotation(-90+selectedItem->rotation());
    m_scene->update();
}

/**********************************************
* @projectName   TestMainWindow
* @brief         摘要
* @func          testRightRotate
* @param         void
* @return        void
* @author        gl
* @date          2024-12-20
**********************************************/
void MainWindow::testRightRotate()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = m_scene->selectedItems().first();
    if( selectedItem->type()==QGraphicsItemGroup::Type ) return;
    selectedItem->setRotation(90+selectedItem->rotation());
    m_scene->update();
}


/**********************************************
* @projectName   TestMainWindow
* @brief         实现图元前置
* @func          testToFront
* @param         void
* @return        void
* @author        gl
* @date          2024-12-20
**********************************************/
void MainWindow::testToFront()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = m_scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue && item->type() == MyItem::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}


/**********************************************
* @projectName   TestMainWindow
* @brief         实现图元后置
* @func          testToBack
* @param         void
* @return        void
* @author        gl
* @date          2024-12-20
**********************************************/
void MainWindow::testToBack()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = m_scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue && item->type() == MyItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::testToGroup()
{

}

void MainWindow::testGroupBreak()
{

}

void MainWindow::testBold()
{
    //    QFont font = fontCombo->currentFont();
    //    font.setPointSize(fontSizeCombo->currentText().toInt());
    //    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    //    font.setItalic(italicAction->isChecked());
    //    font.setUnderline(underlineAction->isChecked());

    //    scene->setFont(font);
    MyTextItem * selectedTextItem = qgraphicsitem_cast<MyTextItem*>(m_scene->selectedItems().first());

    if (selectedTextItem){
        // 未来按钮改成Checked形式
        QFont font = selectedTextItem->font();
        font.setWeight(QFont::Bold);

        selectedTextItem->setFont(font);
        m_scene->update();
    }
}

void MainWindow::testItalic()
{
    MyTextItem * selectedTextItem = qgraphicsitem_cast<MyTextItem*>(m_scene->selectedItems().first());

    if (selectedTextItem){
        QFont font = selectedTextItem->font();
        font.setItalic(true);
        selectedTextItem->setFont(font);
        m_scene->update();
    }
}

void MainWindow::testUnderLine()
{
    MyTextItem * selectedTextItem = qgraphicsitem_cast<MyTextItem*>(m_scene->selectedItems().first());

    if (selectedTextItem){
        QFont font = selectedTextItem->font();
        font.setUnderline(true);
        selectedTextItem->setFont(font);
        m_scene->update();
    }
}

void MainWindow::testUndo()
{

}

void MainWindow::testRedo()
{

}

void MainWindow::testShowStatus()
{
    for (auto& qvec_myItemOnView: m_scene->items() ){
        qDebug() << qvec_myItemOnView->isSelected() << qvec_myItemOnView->pos();
    }
}

void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
        m_scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
    else if (text == tr("White Grid"))
        m_scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
    else if (text == tr("Gray Grid"))
        m_scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
    else
        m_scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

    m_scene->update();
    m_view->update();
}


/**
 * @brief MainWindow::sceneScaleChanged
 * 响应视图缩放功能
 * @param scale
 */
void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = this->m_view->matrix();

    this->m_view->resetMatrix();
    this->m_view->translate(oldMatrix.dx(), oldMatrix.dy());
    this->m_view->scale(newScale, newScale);
    m_view->update();
}

void MainWindow::do_timer_timeout()
{
    m_loadWidget->close();
}
