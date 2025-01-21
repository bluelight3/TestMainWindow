#include "myitem.h"
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QDebug>
#include "control.h"
#include "mytextitem.h"


extern Control control;
MyItem::MyItem()
{
    brushColor = Qt::red;
    m_name = "defaultName";
    myDiagramType = MyType::MyTest1;
    m_toggle = "defaultToggle";
    m_point = QPointF(0,0);
    m_rect = QRect(-60,-60,120,120);
    m_image = type2Image(myDiagramType);

    point_left = QPoint(-60, 0 );
    point_right = QPoint(60, 0 );

//    QPixmap pixmap(":/images/default.png");
//    m_image = pixmap;



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
    m_toggle = myItem->toggle();
    m_point = myItem->m_point;
    m_rect = myItem->m_rect;
    m_image = type2Image(myItem->myDiagramType);

    point_left = myItem->point_left;
    point_right = myItem->point_right;


    setFlag(QGraphicsItem::ItemIsFocusable  ); // 如果要用键盘控制图形项，就必须使图形项可以获得焦点，即设置该标志
    setFlag(QGraphicsItem::ItemIsMovable);     // 如果要想用鼠标控制图形项，那么必须先设置该标志
    setFlag(QGraphicsItem::ItemIsSelectable);   // 其实也可以在创建图形项进行设置


    setAcceptHoverEvents(true);                // 使图形项支持鼠标悬停事件
}

QRectF MyItem::boundingRect() const
{
    qreal adjust = 0.5;
    qreal penWidth =1;
    return QRectF(-60 - adjust ,-60- adjust,120+adjust,120+adjust);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (isSelected() /*|| !collidingItems().isEmpty()*/)      // 焦点-> 选中
        painter->setPen(QPen(QColor(100,100,100,100)));
    else
        painter->setPen(QPen(QColor(255,255,255,200)) );

//    painter->setBrush(brushColor);

    QPixmap pixmap = type2Image(myDiagramType);
    painter->drawPixmap(m_rect,pixmap);
    painter->drawRect(m_rect);


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
    path.addRect(-60,-60,120,120);
    return path;
}

QColor MyItem::color() const
{
    return brushColor;
}

QPixmap MyItem::image() const
{
    return m_image;
}

QString MyItem::name() const
{
    return m_name;
}

QPointF MyItem::point() const
{
    return m_point+this->pos();
}

void MyItem::setLinePoint(QPointF p)
{
//    if( myDiagramType==GND ){
//        isLeft_Right = true;
//        return;
//    }


    p = mapFromParent(p);

    auto len_left = (p.x()-point_left.x())*(p.x()-point_left.x())+(p.y()-point_left.y())*(p.y()-point_left.y());
    auto len_right = (p.x()-point_right.x())*(p.x()-point_right.x())+(p.y()-point_right.y())*(p.y()-point_right.y());
    isLeft_Right = len_left < len_right;
}

bool MyItem::selectedStatus()
{
    return isSelected();
}

void MyItem::addArrow(Arrow *arrow)
{
    m_linkedArrow.append(arrow);
}

QPixmap MyItem::type2Image(MyItem::MyType myType)
{
    if (myType == MyTest1)
        return QPixmap(":/images/circuit/capacitor.png");
    if (myType == MyTest2)
        return QPixmap(":/images/circuit/inductor.png");
    if (myType == MyTest3)
        return QPixmap(":/images/circuit/resistor.png");
    if (myType == MyTest4)
        return QPixmap(":/images/circuit/power.png");
    if (myType == MyTest5)
        return QPixmap(":/images/circuit/ground.png");
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

QRect MyItem::rect() const
{
    return m_rect;
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
        QGraphicsItem::mousePressEvent(event);
    }

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
    MyItemWidget* myItemWidget = control.getMyItemWidget();
    myItemWidget->setItemName(this->name());
    myItemWidget->setItemType(this->diagramType());
    myItemWidget->setItemToggle(this->toggle());
    myItemWidget->setItemPixMap(this->type2Image(this->diagramType()));
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
    MyTextItem* myTextItem = new MyTextItem();

    // 找到所有的Item项

    myTextItem->setPlainText(toggle);
    if (this->childItems().size()>0)
    {
        for (auto item : this->childItems())
            scene()->removeItem(item);
    }
    myTextItem->setParentItem(this);
    myTextItem->setPos(QPointF(-60,-80));
    myTextItem->setZValue(this->zValue()+1);

    MyItemWidget* myItemWidget = control.getMyItemWidget();
    QObject::disconnect(myItemWidget,SIGNAL(setToggle(QString)),this,SLOT(acceptSetToggle(QString)));
    myItemWidget = nullptr;
    // 在Item下方绘制一个graphicTextView
//    emit insertTextItem(toggle);
}


