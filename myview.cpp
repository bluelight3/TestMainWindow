#include "myview.h"
#include <QKeyEvent>
//#include "config.h"
#include <QCursor>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>
#include "control.h"

extern Control control;

MyView::MyView(QWidget * parent) :QGraphicsView(parent)
{
    setAcceptDrops(true);
    setDragMode(QGraphicsView::RubberBandDrag);
    m_bAcceptContextMenu = true;
    m_line = nullptr;
}

void MyView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        scale(1.2,1.2);
        break;
    }
    QGraphicsView::keyPressEvent(event);
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    if (control.getMyMode() == Mode::InsertItem)
    {
        MyItem * selectedItem = dynamic_cast<MyItem*>(itemAt(event->pos()));
        if (!selectedItem){
            QGraphicsView::mousePressEvent(event);
        }
        else{
            emit selectItem(selectedItem);
        }
    }
    else if (control.getMyMode() == InsertLine){
        MyItem* firstSelectItem = dynamic_cast<MyItem*>(itemAt(event->pos()));
        m_line = new QGraphicsLineItem(QLineF(event->pos(),
                                              event->pos()));
        m_line->setPen(QPen(Qt::black, 2));

    }
    return QGraphicsView::mousePressEvent(event);
}

void MyView::mouseMoveEvent(QMouseEvent *event)
{
    if (control.getMyMode() == Mode::InsertLine && m_line != nullptr) {
        QLineF newLine(m_line->line().p1(), event->pos());
        m_line->setLine(newLine);
    } else if (control.getMyMode() == Mode::MoveItem) {
        return QGraphicsView::mouseMoveEvent(event);
    }
    else{
        return QGraphicsView::mouseMoveEvent(event);
    }
}

void MyView::mouseReleaseEvent(QMouseEvent *event)
{

    if (m_line != nullptr && control.getMyMode() == Mode::InsertLine) {
        QList<QGraphicsItem *> startItems = items(m_line->line().p1().x(),m_line->line().p1().y());
        if (startItems.count() && startItems.first() == m_line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(m_line->line().p2().x(),m_line->line().p2().y());
        if (endItems.count() && endItems.first() == m_line)
            endItems.removeFirst();

//        emit removeItem(m_line);
        delete m_line;
        //! [11] //! [12]

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == MyItem::Type &&
                endItems.first()->type() == MyItem::Type &&
                startItems.first() != endItems.first()) {
            MyItem *startItem = qgraphicsitem_cast<MyItem  *>(startItems.first());
            MyItem *endItem = qgraphicsitem_cast<MyItem  *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            arrow->setColor(Qt::black);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            emit addArrow(arrow);
            arrow->updatePosition();
        }



    }
    //! [12] //! [13]
    m_line = nullptr;
    return QGraphicsView::mouseReleaseEvent(event);
}

void MyView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("myimage/png")){
        event->setDropAction(Qt::CopyAction);   // 如果想要设置复制这里和下面函数设置成Qt::CopyAction即可
        event->accept();
    }
    else{
        event->ignore();
    }

}

void MyView::dropEvent(QDropEvent *event)
{

    if (event){
        event->setDropAction(Qt::CopyAction);   // 如果想要设置复制这里和下面函数设置成Qt::CopyAction即可
        event->accept();
        emit insertItem();
    }
    else{
        event->ignore();
    }
}

//void MyView::mousePressEvent(QMouseEvent *event)
//{
////    setFocus();
////    if (event->button() == Qt::RightButton){
////        QPoint currPoint = event->pos();
////        m_mousePos = currPoint;
////        event->accept();
////    }
////    else{
////        event->ignore();
////    }
//    m_bAcceptContextMenu = false;
//    m_pRightButtonPressItem = nullptr;
//    if (event->button() == Qt::RightButton){
//        event->accept();
//        m_bRightButtonPressed = true;
//        QPoint currPoint = event->pos();
//        m_mousePos = currPoint;
//    }

//}


void MyView::contextMenuEvent(QContextMenuEvent *event)
{

    //    if (m_bAcceptContextMenu){
    //        m_bAcceptContextMenu = false;
    //        if (m_)
    //    }


    MyItem * selectedItem = static_cast<MyItem*>(itemAt(event->pos()));


    if (!selectedItem){
        QMenu menu;
        QAction *cutAction = menu.addAction("剪切");
        QAction *copyAction = menu.addAction("复制");
        QAction *pasteAction = menu.addAction("粘贴");
        QAction *brushAction = menu.addAction("刷新");
        QAction *clearAction = menu.addAction("清空");
        QAction *selectedAction = menu.exec(event->globalPos());


        if (selectedAction == cutAction){
            // 这里实现剪切操作
        }
        else if (selectedAction == copyAction) {
            // 这里实现复制操作
        }
        else if (selectedAction == pasteAction) {
            // 这里实现粘贴操作
            //            qDebug()<<m_mousePos;
            //            emit insertClipBordItem(m_mousePos);

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
            QString name;
            MyItem::MyType myType;
            QPointF myPoint;
            QColor color;

            dataStream >> color >> name >> myType >> myPoint;
            MyItem tmpItem;
            tmpItem.setColor(color);
            tmpItem.setName(name);
            tmpItem.setType(myType);
            tmpItem.setPoint(myPoint);
            emit insertClipBordItem(&tmpItem);

        }
        else if (selectedAction == brushAction){
            // 这里实现刷新操作
            scene()->update();
            repaint();
        }

        else if (selectedAction == clearAction) {
            // 这里实现清除操作
            emit clear();
        }
        else{
            qDebug() << "not defined Action";
        }
    }
    else if ( selectedItem->diagramType()== MyItem::MyTest1 || selectedItem->diagramType()== MyItem::MyTest2){
        QMenu menu;
        QAction *moveAction = menu.addAction("移回");
        QAction *brushAction = menu.addAction("刷新");
        QAction *cutAction = menu.addAction("剪切");
        QAction *copyAction = menu.addAction("复制");
        QAction *pasteAction = menu.addAction("粘贴");
        QAction *deleteAction = menu.addAction("删除");


        QAction *selectedAction = menu.exec(event->globalPos());
        if (selectedAction == moveAction){
            qDebug() <<"move back!";
            selectedItem->setPos(0,0);
        }
        else if (selectedAction == brushAction){
            // 这里实现刷新操作
            scene()->update();
        }
        else if (selectedAction == cutAction){
            // 这里实现剪切操作

        }
        else if (selectedAction == copyAction) {
            // 这里实现复制操作 后续改成根据复制的Item是MyItem还是TextItem执行不同的操作
            QByteArray itemData;

            QDataStream dataStream(&itemData,QIODevice::WriteOnly); //创建数据流
            // 将Item的相关参数放入到字节数组中
            dataStream <<selectedItem->color()<<selectedItem->name()<<selectedItem->diagramType()<<selectedItem->point();
            // 多个复制需要将多个Item一起放到 dataStrem中 一个解决方案就是先指定有多少个Item，然后一个一个把Item放进去 ()
            // 将数据放入QMimeData中
            QMimeData* mimeData = new QMimeData;
            // 第四步 将字节数组放入QMimeData中，此处Mime类型由自己定义
            mimeData->setData("application/myItem",itemData);
            QClipboard* clipBoard = QApplication::clipboard(); // 自定义剪切板，只在view中实现做参考因此定义在这
            clipBoard->setMimeData(mimeData);



        }
        else if (selectedAction == pasteAction) {
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
            QString name;
            MyItem::MyType myType;
            QPointF myPoint;
            QColor color;

            dataStream >> color >> name >> myType >> myPoint;
            MyItem tmpItem;
            tmpItem.setColor(color);
            tmpItem.setName(name);
            tmpItem.setType(myType);
            tmpItem.setPoint(myPoint);
            emit insertClipBordItem(&tmpItem);

            //            delete tmpItem;
        }

        else if (selectedAction == deleteAction) {
            emit removeItem(selectedItem);  // 删除选中Item
            // 这里实现删除操作
        }
        else{
            qDebug() << "not defined Action";
        }
    }

    else{
        QGraphicsView::contextMenuEvent(event);
    }
}

void MyView::acceptSetMyDragMode()
{
//    m_myMode = myMode;
    if (control.getMyMode() == InsertLine){
        setDragMode(QGraphicsView::NoDrag);
    }
    else{
        setDragMode(QGraphicsView::RubberBandDrag);
    }
}






