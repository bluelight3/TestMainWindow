#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMimeData>
#include <QDrag>
#include "MyHelper.h"
#include "global.h"


const int InsertTextButton = 10;
extern Control control;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化
    setAcceptDrops(true);
    control.createMyItemWidget();
    qvec_MyItemOnView = new QVector<QGraphicsItem*>;

    m_selectedItem = NULL;
    //

    //设置一个单独接收拖动标签
    m_label = new QLabel(this);
    QPixmap pix(":/images/new.png");
    m_label->setPixmap(pix);
    m_label->resize(pix.size());
    m_label->move(100,100);
    m_label->setAttribute(Qt::WA_DeleteOnClose);
    m_label->installEventFilter(this);

    m_label2 = new QLabel(this);
    QPixmap pix2(":/images/copy.png");
    m_label2->setPixmap(pix2);
    m_label2->resize(pix2.size());
    m_label2->move(100,100);
    m_label2->setAttribute(Qt::WA_DeleteOnClose);
    m_label2->installEventFilter(this);

    m_labelText = new QLabel(this);
    QPixmap pix3(":/images/textpointer.png");
    m_labelText->setPixmap(pix3);
    m_labelText->resize(pix3.size());
//    m_labelText->move(100,100);
    m_labelText->setAttribute(Qt::WA_DeleteOnClose);
    m_labelText->installEventFilter(this);


    m_labelText2 = new QLabel(this);
    QPixmap pix4(":/images/textpointer.png");
    m_labelText2->setPixmap(pix3);
    m_labelText2->resize(pix3.size());
//    m_labelText->move(100,100);
    m_labelText2->setAttribute(Qt::WA_DeleteOnClose);
    m_labelText2->installEventFilter(this);

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

    myDiagramTextItem = new DiagramTextItem;
//    myDiagramTextItem->setFont(myFont);
    myDiagramTextItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    myDiagramTextItem->setZValue(1000.0);

    myTextItem = new MyTextItem;
    myTextItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    myTextItem->setZValue(1000.0);

//    connect(myDiagramTextItem, &DiagramTextItem::selectedChange,
//            m_scene, &MainWindow::itemSelected);

//    myDiagramTextItem->setDefaultTextColor(myTextColor);
//    myDiagramTextItem->setPos(mouseEvent->scenePos());
//    connect(myDiagramTextItem, &DiagramTextItem::lostFocus,
//            this, &DiagramScene::editorLostFocus);
//    connect(myDiagramTextItem, &DiagramTextItem::selectedChange,
//            this, &DiagramScene::itemSelected);
//    addItem(myDiagramTextItem);


    m_myItem1_count = 1;
    m_myItem2_count = 1;
    //
    createToolBox();

    QGraphicsScene scene;
    // 将图形项添加到场景中

    m_view =new MyView();
    m_scene = new QGraphicsScene();

    m_view->setScene(m_scene);
    m_scene->setSceneRect(QRectF(0,0,640,480));
//    scene->addPixmap(QPixmap("C://Users//5510760lbw//Pictures//IP.png"));
    m_scene->setForegroundBrush(QColor(255,255,255,0));

    initQMap();

    // 这边设置信号，当指定图元项被拖动到界面时执行界面函数
    connect(m_view,SIGNAL(insertItem()),this, SLOT(acceptInsertItem())); // 当拖动到view上时调用view的insertItem信号，触发acceptInsertItem
    connect(m_view,SIGNAL(removeItem(QGraphicsItem*)),this, SLOT(acceptRemoveItem(QGraphicsItem*)));
    connect(m_view,SIGNAL(insertClipBordItem(QPointF)),this,SLOT(acceptClipBoardInsertItem(QPointF))); // 暂时复用粘贴栏
    connect(m_view,SIGNAL(insertClipBordItem(QGraphicsItem*)),this,SLOT(acceptClipBoardInsertItem(QGraphicsItem*))); // 暂时复用粘贴栏
    connect(m_view,SIGNAL(clear()),this,SLOT(acceptClear())); // 暂时复用粘贴栏
    connect(m_view,SIGNAL(selectItem(QGraphicsItem*)),this,SLOT(acceptSelectItem(QGraphicsItem*)));
    connect(m_view,SIGNAL(addArrow(Arrow*)),this,SLOT(acceptAddArrow(Arrow*)));



    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(testNew()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(testOpen()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(testSave()));
    connect(ui->actionDelete,SIGNAL(triggered()),this,SLOT(testDelete()));

    connect(ui->actionCut,SIGNAL(triggered()),this,SLOT(testCut()));
    connect(ui->actionCopy,SIGNAL(triggered()),this,SLOT(testCopy()));
    connect(ui->actionPaste,SIGNAL(triggered()),this,SLOT(testPaste()));

    connect(ui->actionStatus,SIGNAL(triggered()),this, SLOT(showStatus()));
    connect(ui->actionGenerateProject,SIGNAL(triggered()),this,SLOT(testGenerateProject()));

    connect(ui->actionConnectLine,SIGNAL(triggered()),this,SLOT(testConnectLine()));
//    connect(this,SIGNAL(setMyDragMode(Mode)),m_view,SLOT(acceptSetMyDragMode(Mode)));
    connect(&control,SIGNAL(setMyDragMode()),m_view,SLOT(acceptSetMyDragMode()));
    connect(ui->actionBrush,SIGNAL(triggered()),this,SLOT(testBrush()));

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

    // 模糊效果

    ui->actionDelete->setEnabled(true);


}

MainWindow::~MainWindow()
{
    delete myItem1;
    delete myItem2;


    for (auto qvec_myItemOnView : m_scene->items()){
        delete qvec_myItemOnView;
    }

    delete myDiagramTextItem;
    delete myTextItem;

    delete qvec_MyItemOnView;
    delete m_view;
    delete m_scene;
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

    layout->addWidget(m_labelText,3,0);
    layout->addWidget(m_labelText2,3,1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

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
    qmap_myItem[m_labelText] = myDiagramTextItem;
    qmap_myItem[m_labelText2] = myTextItem;
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
    if (m_view->geometry().contains(this->mapFromGlobal(QCursor::pos()))){
        // 将所有Item设置成未被选中状态
        unselectAllshowedItem();

        MyItem * selectedItem = static_cast<MyItem*>(m_view->itemAt(event->pos()));
        if (selectedItem){
//            m_selectedItem = selectedItem;
            setFocus();
            setCursor(Qt::ClosedHandCursor);
            qDebug() <<"select Item";
            ui->actionDelete->setEnabled(true);
        }
        else{
//            ui->actionDelete->setEnabled(false);
        }
    }
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
    m_selectedItem = qmap_myItem[child];


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
    else if (obj == this->m_labelText){
        if (event->type() == QEvent::HoverEnter)
        {
            setToolTip("labelText");
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
    else if (obj->inherits("MyItem")){
        if (event->type() == QMouseEvent::MouseButtonPress)
        {
            qDebug()<<"pressed";
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

void MainWindow::acceptInsertItem()
{
    MyItem* tmpItem;
    DiagramTextItem* myTmpDiagramTextItem;
    MyTextItem* myTmpTextItem;

//    if (!selectItem)
//        return;
    // 基于已有Item生成一个新的Item，并显示在界面上

//    QGraphicsItem* tmpItem = m_selectedItem;

    // 现在选择的Item 必须转换成具体的子类Item。
    //尝试强转成 MyItem
    tmpItem =  dynamic_cast<MyItem*>(m_selectedItem);
    myTmpDiagramTextItem = dynamic_cast<DiagramTextItem*>(m_selectedItem);
    myTmpTextItem = dynamic_cast<MyTextItem*>(m_selectedItem);

    // 连线状态不接受放入图元
    if (control.getMyMode() == Mode::InsertLine)
        return;

    if (tmpItem)
    {
        control.setMyMode(Mode::InsertItem);
        MyItem* tmpInsertedItem = new MyItem(tmpItem);

//        connect(tmpInsertedItem, &MyItem::selectItem,
//                this, &MainWindow::myItemSelected);

        if (tmpItem->diagramType() == MyItem::MyTest1){
            tmpItem->setName(tmpItem->name() + QString::number(m_myItem1_count++));
        }
        else if (tmpItem->diagramType() == MyItem::MyTest2) {
            tmpItem->setName(tmpItem->name() + QString::number(m_myItem2_count++));
        }

        tmpInsertedItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
//        connect(tmpInsertedItem,SIGNAL(MyItem::insertTextItem(QString)),this,SLOT(MainWindow::acceptInsertTextItem()));

        m_scene->addItem(tmpInsertedItem);
//        qvec_MyItemOnView->push_back(tmpInsertedItem);
        //
    }
    else if (myTmpDiagramTextItem){
        // 设置自己的Item名称

        // 添加新的Item
        control.setMyMode(Mode::InsertItem);
        DiagramTextItem* tmpInsertedItem = new DiagramTextItem(myTmpDiagramTextItem);
        //未来整体重构，因为之前代码写成了Label放置 对应一个已申请的Item被拖动进的方式，因此
        connect(tmpInsertedItem, &DiagramTextItem::lostFocus,
                this, &MainWindow::editorLostFocus);
        connect(tmpInsertedItem, SIGNAL(DiagramTextItem::selectedChange(QGraphicsItem*)),
                this, SLOT(MainWindow::itemSelected(QGraphicsItem*)));


        tmpInsertedItem->setSelected(true);
        tmpInsertedItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        tmpInsertedItem->setDefaultTextColor(Qt::red);
        qDebug()<<"newpos:"<<m_view->mapFromGlobal(QCursor::pos());
        tmpInsertedItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
        m_scene->addItem(tmpInsertedItem);
        qvec_MyItemOnView->push_back(tmpInsertedItem);

    }
    else if (myTmpTextItem) {
        MyTextItem* tmpInsertedItem = new MyTextItem(myTextItem);

        tmpInsertedItem->setSelected(true);
        tmpInsertedItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        tmpInsertedItem->setDefaultTextColor(Qt::blue);
        qDebug()<<"newpos:"<<m_view->mapFromGlobal(QCursor::pos());
        tmpInsertedItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
        m_scene->addItem(tmpInsertedItem);
        qvec_MyItemOnView->push_back(tmpInsertedItem);
    }

    qDebug()<<m_view->mapFromParent(this->mapFromGlobal(QCursor::pos()));
    m_scene->update();


//    tmpItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
//    m_scene->addItem(tmpItem);

    //    qvec_MyItemOnView->push_back(tmpItem);
}

void MainWindow::acceptInsertTextItem()
{
    MyTextItem* myTmpTextItem;

    myTmpTextItem = dynamic_cast<MyTextItem*>(m_selectedItem);
    if (myTmpTextItem) {
        MyTextItem* tmpInsertedItem = new MyTextItem(myTextItem);

        tmpInsertedItem->setSelected(true);
        tmpInsertedItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        tmpInsertedItem->setDefaultTextColor(Qt::blue);
        qDebug()<<"newpos:"<<m_view->mapFromGlobal(QCursor::pos());
        tmpInsertedItem->setPos(m_selectedItem->pos()+QPointF(0,10));
        m_scene->addItem(tmpInsertedItem);
        qvec_MyItemOnView->push_back(tmpInsertedItem);
    }


//    qDebug()<<m_view->mapFromParent(this->mapFromGlobal(QCursor::pos()));
    m_scene->update();
}

void MainWindow::acceptClipBoardInsertItem(QPointF point)
{
    MyItem* tmpItem;
    DiagramTextItem* myTmpDigramTextItem;




    // 暂时复用selectItem作为粘贴Item，并显示在界面上
    if (!m_selectedItem)
        return;
//    QGraphicsItem* tmpItem = m_selectedItem; // C++多态，父类指针指向子类对象，根据子类的类别执行不同的成员函数

    tmpItem =  dynamic_cast<MyItem*>(m_selectedItem);
    myTmpDigramTextItem = dynamic_cast<DiagramTextItem*>(m_selectedItem);


    if (tmpItem)
    {
        if (tmpItem->diagramType() == MyItem::MyTest1)
           tmpItem->setName(tmpItem->name() + QString::number(m_myItem1_count++));
        else if (tmpItem->diagramType() == MyItem::MyTest2) {
            tmpItem->setName(tmpItem->name() + QString::number(m_myItem2_count++));
        }

        MyItem* tmpInsertedItem = new MyItem(tmpItem);
        tmpInsertedItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
        m_scene->addItem(tmpInsertedItem);
        qvec_MyItemOnView->push_back(tmpInsertedItem);
    }
    else if (myTmpDigramTextItem){
        // 设置自己的名字?
    }



//    MyItem* tmpItem = new MyItem(m_selectedItem); // C++多态，父类指针指向子类对象，根据子类的类别执行不同的成员函数
//    if (m_selectedItem->diagramType() == MyItem::MyTest1)
//       tmpItem->setName(m_selectedItem->name() + QString::number(m_myItem1_count++));
//    else if (m_selectedItem->diagramType() == MyItem::MyTest2) {
//        tmpItem->setName(m_selectedItem->name() + QString::number(m_myItem2_count++));
//    }

    tmpItem->setPos(point);
    m_scene->addItem(tmpItem);
}

void MainWindow::acceptClipBoardInsertItem(QGraphicsItem* myItem)
{
    MyItem* tmpItem;
    DiagramTextItem* myTmpDigramTextItem;

    // 连线状态不接受放入图元
    if (control.getMyMode() == Mode::InsertLine)
        return;

    tmpItem =  dynamic_cast<MyItem*>(myItem);
    myTmpDigramTextItem = dynamic_cast<DiagramTextItem*>(myItem);

    if (tmpItem)
    {
        control.setMyMode(Mode::InsertItem);
        if (tmpItem->diagramType() == MyItem::MyTest1){
            tmpItem->setName(tmpItem->name() + "_copy" + QString::number(m_myItem1_count++));
            tmpItem->setColor(Qt::blue);
        }
        else if (tmpItem->diagramType() == MyItem::MyTest2) {
            tmpItem->setName(tmpItem->name() + "_copy" + QString::number(m_myItem2_count++));
            tmpItem->setColor(Qt::green);
        }

        MyItem* tmpInsertedItem = new MyItem(tmpItem);
        tmpInsertedItem->setPos(m_view->mapFromGlobal(QCursor::pos()));
        m_scene->addItem(tmpInsertedItem);
        qvec_MyItemOnView->push_back(tmpInsertedItem);
    }
    else if (myTmpDigramTextItem){
        // 设置自己的名字?
    }

//    m_scene->addItem(tmpItem);
//    qvec_MyItemOnView->push_back(tmpItem);


//    MyItem* tmpItem = new MyItem(myItem);
//    if (m_selectedItem->diagramType() == MyItem::MyTest1)
//    {
//        tmpItem->setName(m_selectedItem->name() + "_copy" + QString::number(m_myItem1_count++));
//        tmpItem->setColor(Qt::blue);
//    }
//    else if (m_selectedItem->diagramType() == MyItem::MyTest2) {
//        tmpItem->setName(m_selectedItem->name() + "_copy" + QString::number(m_myItem2_count++));
//        tmpItem->setColor(Qt::green);
//    }

//    m_scene->addItem(tmpItem);
//    qvec_MyItemOnView->push_back(tmpItem);
}

void MainWindow::acceptClear()
{

    m_scene->clear();
    for (auto& qvec_myItemOnView : m_scene->selectedItems()){
        delete qvec_myItemOnView;
    }
    qvec_MyItemOnView->clear();
}

void MainWindow::acceptRemoveItem(QGraphicsItem* myItem)
{
    // 删除
    m_scene->removeItem(myItem);
    qvec_MyItemOnView->removeOne(myItem);
}

void MainWindow::acceptSelectItem(QGraphicsItem* myItem)
{
//    m_selectedItem = myItem;
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

void MainWindow::unselectAllshowedItem()
{

    for (auto& qvec_myItemOnView : m_scene->selectedItems()) {
        qvec_myItemOnView->setSelected(false);
    }
}

void MainWindow::generateProject()
{

}

void MainWindow::showStatus()
{
    for (auto& qvec_myItemOnView : m_scene->items()) {
        qDebug() << qvec_myItemOnView->isSelected() << qvec_myItemOnView->pos();
    }
}

void MainWindow::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        m_scene->removeItem(item);
        item->deleteLater();
    }
}

void MainWindow::acceptAddArrow(Arrow *myItem)
{
    Arrow * tmpArrow;
    tmpArrow   = dynamic_cast<Arrow*>(myItem);

    if (tmpArrow)
    {
        control.setMyMode(Mode::InsertLine);
//        Arrow* tmpInsertedItem = new Arrow(tmpArrow);

//        tmpArrow->setPos((tmpArrow->endItem()->pos()));
        m_scene->addItem(tmpArrow);
        qvec_MyItemOnView->push_back(tmpArrow);
        //
    }
}

void MainWindow::setItemToggle(QString toggle)
{
    // 创建一个新的MyTextItem 并设置Text为toggle，位置在MyItem最上方
    MyTextItem* myTextItem = new MyTextItem();
    myTextItem->setPlainText(toggle);
    MyItem* myItem = dynamic_cast<MyItem*>( m_scene->selectedItems().first());
    myTextItem->setPos(myItem->pos()+QPointF(0,10));
    m_scene->addItem(myTextItem);

    // 将MyTextItem和Item组合
}

void MainWindow::testNew()
{

}

void MainWindow::testOpen()
{

}

void MainWindow::testSave()
{

}

void MainWindow::testCut()
{
    qDebug()<<"选中"<<m_scene->selectedItems().size()<<"个Items";
    QGraphicsItem* tmpGraphicsItem = m_scene->selectedItems().first();
    MyItem* tmpItem = dynamic_cast<MyItem*>(tmpGraphicsItem);
    m_scene->removeItem(tmpItem);
    QByteArray itemData;
    QDataStream dataStream(&itemData,QIODevice::WriteOnly); //创建数据流

    if (!tmpItem)
        return;

    // 将Item的相关参数放入到字节数组中
    dataStream <<tmpItem->color()<<tmpItem->name()<<tmpItem->diagramType()<<tmpItem->point();
    // 将数据放入QMimeData中
    QMimeData* mimeData = new QMimeData;
    // 第四步 将字节数组放入QMimeData中，此处Mime类型由自己定义
    mimeData->setData("application/myItem",itemData);
    QClipboard* clipBoard = QApplication::clipboard(); // 自定义剪切板，只在view中实现做参考因此定义在这
    clipBoard->setMimeData(mimeData);


}

void MainWindow::testCopy()
{
    // 这里的Copy不需要通过鼠标获取当前位置的Item，可以直接从类中获取

    MyItem* tmpItem;
    DiagramTextItem* myTmpDigramTextItem;
    QByteArray itemData;
    QDataStream dataStream(&itemData,QIODevice::WriteOnly); //创建数据流

    // 现在需要先创建一个新的Item
    for (auto item : m_scene->selectedItems())
    {
        tmpItem =  dynamic_cast<MyItem*>(item);
        myTmpDigramTextItem = dynamic_cast<DiagramTextItem*>(m_scene->selectedItems().first());
        // 创建一个新的Text

        // 目前只能复制MyItem* 类
        if (!tmpItem)
            return;
        // 将Item的相关参数放入到字节数组中
        dataStream <<tmpItem->color()<<tmpItem->name()<<tmpItem->diagramType()<<tmpItem->point();
    }
    // 将数据放入QMimeData中
    QMimeData* mimeData = new QMimeData;
    // 第四步 将字节数组放入QMimeData中，此处Mime类型由自己定义
    mimeData->setData("application/myItem",itemData);
    QClipboard* clipBoard = QApplication::clipboard(); // 自定义剪切板，只在view中实现做参考因此定义在这
    clipBoard->setMimeData(mimeData);

}

void MainWindow::testPaste()
{
    // 这里实现粘贴操作
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
    MyItem tmpItem;

    while (!dataStream.atEnd()){
        dataStream >> color >>name >> myType >> myPoint;

        tmpItem.setColor(color);
        tmpItem.setName(name);
        tmpItem.setType(myType);
        tmpItem.setPoint(myPoint);

        // 同样的，主界面中直接执行槽函数而不需要发射信号
        acceptClipBoardInsertItem(&tmpItem);
    }



}

void MainWindow::testDelete()
{
    // 只选中一个的情况
    if (m_scene->selectedItems().size()>0)
        acceptRemoveItem(m_scene->selectedItems().first());

    // 删除多个的情况
    // 目前逻辑为删除所有界面上被选中的item

    for (auto& qvec_myItemOnView : m_scene->selectedItems())
    if (qvec_myItemOnView->isSelected()){
        m_scene->removeItem(qvec_myItemOnView);
        qvec_MyItemOnView->removeOne(qvec_myItemOnView);
    }

}

void MainWindow::testConnectLine()
{
    if (ui->actionConnectLine->isChecked())
        control.setMyMode(Mode::InsertLine);
    else
        control.setMyMode(Mode::nullItem);
    //    emit setMyDragMode(m_myMode);
}

void MainWindow::testBrush()
{
    m_scene->update();
    m_view->repaint();
}

void MainWindow::testGenerateProject()
{
    // 更新界面进度条
    if (!control.getMyGenerateProjectForm())
        control.createMyGenerateProjectForm();
    if (!control.getMyGenerateProjectThread())
        control.createMyGenerateProjectThread();
    GenerateProjectForm* form = control.getMyGenerateProjectForm();
    GenerateProjectThread* thread = control.getMyGenerateProjectThread();
    control.runMyGenerateProjectThread();
    form->show();
//    QTimer* timer = new QTimer(this);
//    connect(timer,&QTimer::timeout,thread,GenerateProjectThread::);
    // 生成Project具体实现
//    m_updateProgressValue++;
//    thread->setGenerateProgress(m_updateProgressValue);
    // 生成项目在generateProject中实现
}

void MainWindow::itemSelected(QGraphicsItem *item)
{
    // Item被选中时使能部分action
    ui->actionDelete->setEnabled(true);

    DiagramTextItem *textItem =
    qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();

    //  字体栏引入后再打开注释


//    fontCombo->setCurrentFont(font);
//    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
//    boldAction->setChecked(font.weight() == QFont::Bold);
//    italicAction->setChecked(font.italic());
    //    underlineAction->setChecked(font.underline());
}

void MainWindow::myItemSelected()
{
    ui->actionDelete->setEnabled(true);
}


