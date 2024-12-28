#include "myitem.h"
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QDebug>
#include "control.h"

extern Control control;
MyItem::MyItem()
{
    brushColor = Qt::red;
    m_name = "defaultName";
    myDiagramType = MyType::MyTest1;
    m_point = QPointF(0,0);
    m_rect = QRect(-40,-40,40,40);

    setFlag(QGraphicsItem::ItemIsFocusable  ); // 如果要用键盘控制图形项，就必须使图形项可以获得焦点，即设置该标志
    setFlag(QGraphicsItem::ItemIsMovable);     // 如果要想用鼠标控制图形项，那么必须先设置该标志
    setFlag(QGraphicsItem::ItemIsSelectable);
                                               // 其实也可以在创建图形项进行设置
    setAcceptHoverEvents(true);                // 使图形项支持鼠标悬停事件

}

MyItem::MyItem(MyItem *myItem)
{
    brushColor = myItem->brushColor;
    m_name = myItem->m_name;
    myDiagramType = myItem->myDiagramType;
    m_point = myItem->m_point;
    m_rect = myItem->m_rect;


    setFlag(QGraphicsItem::ItemIsFocusable  ); // 如果要用键盘控制图形项，就必须使图形项可以获得焦点，即设置该标志
    setFlag(QGraphicsItem::ItemIsMovable);     // 如果要想用鼠标控制图形项，那么必须先设置该标志
    setFlag(QGraphicsItem::ItemIsSelectable);   // 其实也可以在创建图形项进行设置


    setAcceptHoverEvents(true);                // 使图形项支持鼠标悬停事件
}

QRectF MyItem::boundingRect() const
{
    qreal adjust = 0.5;
    qreal penWidth =1;
//    if (this->type() == MyTest1){
//        return QRectF(-40 - adjust ,-40- adjust,40+adjust,40+adjust);
//    }

    return QRectF(-40 - adjust ,-40- adjust,40+adjust,40+adjust);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (isSelected() || !collidingItems().isEmpty())      // 焦点-> 选中
        painter->setPen(QPen(QColor(255,255,255,200)) );
    else
        painter->setPen(QPen(QColor(100,100,100,100)));
    painter->setBrush(brushColor);
    painter->drawRect(-40,-40,40,40);


//    painter->setBrush(Qt::red);
    //    painter->drawRect(0,0,20,20);
}

void MyItem::setType(MyItem::MyType myType)
{
    myDiagramType = myType;
}

void MyItem::setName(QString myName)
{
    m_name = myName;
}

void MyItem::setPoint(QPointF myPoint)
{
    m_point = myPoint;
}

QPainterPath MyItem::shape() const
{
    QPainterPath path;
    path.addRect(-40,-40,40,40);
    return path;
}

QColor MyItem::color() const
{
    return brushColor;
}

QPixmap MyItem::image() const
{
    QPixmap pixmap(":/images/default.png");
    if (diagramType() == MyTest1)
        return QPixmap(":/images/test1.png");
    if (diagramType() == MyTest2)
        return QPixmap(":/images/test2.png");

    return pixmap;
}

QString MyItem::name() const
{
    return m_name;
}

QPointF MyItem::point() const
{
    return m_point+this->pos();
}

bool MyItem::selectedStatus()
{
    return isSelected();
}

void MyItem::addArrow(Arrow *arrow)
{
    m_linkedArrow.append(arrow);
}

void MyItem::setLength(int length)
{
    m_length = length;
}

void MyItem::setRect(const QRect &rect)
{
    m_rect = rect;
}

QString MyItem::toggle() const
{
    return m_toggle;
}

void MyItem::setToggle(const QString &toggle)
{
    m_toggle = toggle;
}

void MyItem::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Down)
        moveBy(0,10);
    if (event->key() == Qt::Key_Up)
        moveBy(0,-10);
    if (event->key() == Qt::Key_Left)
        moveBy(-10,0);
    if (event->key() == Qt::Key_Right)
        moveBy(10,0);
}


//
void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setFocus();
    if (control.getMyMode() == Mode::InsertLine)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ClosedHandCursor);
    }
//    emit selectItem();
}

//void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    if (event->modifiers() == Qt::ControlModifier)
//    {
//        // 按住Ctrl时松开可能的操作
//    }
//    else
//        setSelected(false);

//}

void MyItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

    if (control.getMyMode() == Mode::InsertLine)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::OpenHandCursor);
        setToolTip(QString("I am item %1").arg(this->name()));
    }

}

void MyItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
//    QGraphicsItem * selectedItem = itemAt(event->scenePos());

//    QMenu menu;
//    QAction *moveAction = menu.addAction("move back");
//    QAction *brushAction = menu.addAction("brush");
//    QAction *cutAction = menu.addAction("cut");
//    QAction *copyAction = menu.addAction("copy");
////    QAction *pasteAction = menu.addAction("paste");
//    QAction *deleteAction = menu.addAction("delete");


//    QAction *selectedAction = menu.exec(event->screenPos());
//    if (selectedAction == moveAction){
//        setPos(0,0);
//    }
//    else if (selectedAction == brushAction){
//        // 这里实现刷新操作
////        scene()->brush;
//    }
//    else if (selectedAction == cutAction){
//        // 这里实现剪切操作

//    }
//    else if (selectedAction == copyAction) {
//        // 这里实现复制操作
//    }
//    else if (selectedAction == deleteAction) {
//        // 这里实现粘贴操作
//    }
//    else{
//        qDebug() << "未定义Action";
    //    }
}

void MyItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    control.createMyItemWidget();
    MyItemWidget* myItemWidget = control.getMyItemWidget();
    myItemWidget->setItemName(this->name());
    myItemWidget->setItemType(this->diagramType());
    myItemWidget->setItemToggle("default toggle");
    myItemWidget->setItemPixMap(this->image());
    myItemWidget->setTitleName(this->name());

    QObject::connect(myItemWidget,SIGNAL(setToggle(QString)),this,SLOT(acceptSetToggle(QString)));
    QObject::connect(myItemWidget,SIGNAL(setName(QString)),this,SLOT(acceptSetName(QString)));

    myItemWidget->show();
}

void MyItem::acceptSetName(QString myName)
{
    setName(myName);
}

void MyItem::acceptSetToggle(const QString &toggle)
{
    setToggle(toggle);
    // 在Item下方绘制一个graphicTextView
    emit insertTextItem(toggle);
}


