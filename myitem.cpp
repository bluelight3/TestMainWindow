#include "myitem.h"
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QDebug>

MyItem::MyItem()
{
    brushColor = Qt::red;
    m_name = "defaultName";
    myDiagramType = MyType::MyTest1;
    m_point = QPointF(0,0);
    m_point_left = QPointF(-120,0);
    m_point_right = QPointF(120,0);

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



    setFlag(QGraphicsItem::ItemIsFocusable  ); // 如果要用键盘控制图形项，就必须使图形项可以获得焦点，即设置该标志
    setFlag(QGraphicsItem::ItemIsMovable);     // 如果要想用鼠标控制图形项，那么必须先设置该标志
    setFlag(QGraphicsItem::ItemIsSelectable);
                                               // 其实也可以在创建图形项进行设置


    setAcceptHoverEvents(true);                // 使图形项支持鼠标悬停事件
}

QRectF MyItem::boundingRect() const
{
    qreal adjust = 0.5;
    qreal penWidth =1;
    return QRectF(-40 - adjust ,-40- adjust,40+adjust,40+adjust);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (isSelected() || !collidingItems().isEmpty())
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
    return m_point;
}



/**********************************************
* @projectName   TestMainWindow
* @brief         移除关联的连线
* @func          removeArrow
* @param         Arrow *arrow
* @return        void
* @author        gl
* @date          2024-12-23
**********************************************/
void MyItem::removeArrow(Arrow *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

/**********************************************
* @projectName   TestMainWindow
* @brief         移除所有连线
* @func          removeArrows
* @param         void
* @return        void
* @author        gl
* @date          2024-12-23
**********************************************/
QList<Arrow *> MyItem::removeArrows()
{
    foreach (Arrow *arrow, arrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);

        QGraphicsItem* tmpArrow = dynamic_cast<QGraphicsItem*>(arrow);
        if (tmpArrow)
            scene()->removeItem(tmpArrow);
//        emit removeItem(arrow);
        delete arrow;
    }
    return arrows;
}

/**********************************************
* @projectName   TestMainWindow
* @brief         添加连线
* @func          addArrow
* @param         void
* @return        void
* @author        gl
* @date          2024-12-23
**********************************************/
void MyItem::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

/**********************************************
* @projectName   TestMainWindow
* @brief         获取连接点位置
* @func          getLinePoint
* @param         void
* @return        void
* @author        gl
* @date          2024-12-23
**********************************************/
QPointF MyItem::getLinePoint(){
    return m_isLeft_Right ? m_point_left : m_point_right;
}

/**********************************************
* @projectName   TestMainWindow
* @brief         设置确定连接点位置
* @func          setLinePoint
* @param         QPointF p
* @return        void
* @author        gl
* @date          2024-12-23
**********************************************/
void MyItem::setLinePoint(QPointF p)
{
//    if( myDiagramType==GND ){
//        isLeft_Right = true;
//        return;
//    }

    p = mapFromScene(p);

    auto len_left = (p.x()-m_point_left.x())*(p.x()-m_point_left.x())+(p.y()-m_point_left.y())*(p.y()-m_point_left.y());
    auto len_right = (p.x()-m_point_right.x())*(p.x()-m_point_right.x())+(p.y()-m_point_right.y())*(p.y()-m_point_right.y());
    m_isLeft_Right = len_left < len_right;
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

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setFocus();
    setCursor(Qt::ClosedHandCursor);
}

void MyItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    setToolTip(QString("I am item %1").arg(this->name()));
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
    MyItemidget* myItemWidget = new MyItemidget();
    myItemWidget->setItemName(this->name());
    myItemWidget->setItemMyType(this->diagramType());
    myItemWidget->setItemToggle("default toggle");
    myItemWidget->setItemPixmap(this->image());

    myItemWidget->setTitleName(this->name());

    myItemWidget->show();
}

/**********************************************
* @projectName   TestMainWindow
* @brief         关联图元变化,更新连线位置
* @func          itemChange
* @param         QGraphicsItem::GraphicsItemChange change,const QVariant &value
* @return        void
* @author        gl
* @date          2024-12-23
**********************************************/
QVariant MyItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{

}


