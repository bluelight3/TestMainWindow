#include "myview.h"
#include <QKeyEvent>
//#include "config.h"
#include <QCursor>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>

MyView::MyView(QWidget * parent) :QGraphicsView(parent)
{
    setAcceptDrops(true);
    setDragMode(QGraphicsView::RubberBandDrag);


    m_bAcceptContextMenu = true;
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


void MyView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event){
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

void MyView::contextMenuEvent(QContextMenuEvent *event)
{

    //    if (m_bAcceptContextMenu){
    //        m_bAcceptContextMenu = false;
    //        if (m_)
    //    }
    MyItem * selectedItem = static_cast<MyItem*>(itemAt(event->pos()));


    if (!selectedItem){
        QMenu menu;
        QAction *cutAction = menu.addAction("cut");
        QAction *copyAction = menu.addAction("copy");
        QAction *pasteAction = menu.addAction("paste");
        QAction *brushAction = menu.addAction("brush");
        QAction *clearAction = menu.addAction("clear");
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

            dataStream >> name >> myType >> myPoint;
            MyItem tmpItem;
            tmpItem.setName(name);
            tmpItem.setType(myType);
            tmpItem.setPoint(myPoint);
            emit insertClipBordItem(&tmpItem);

        }
        else if (selectedAction == brushAction){
            // 这里实现刷新操作
            //        scene()->brush;
        }

        else if (selectedAction == clearAction) {
            // 这里实现清除操作
            emit clear();
        }
        else{
            qDebug() << "undefined Action";
        }
    }
    else if ( selectedItem->diagramType()== MyItem::MyTest1 || selectedItem->diagramType()== MyItem::MyTest2){
        QMenu menu;
        QAction *moveAction = menu.addAction("move back");
        QAction *brushAction = menu.addAction("brush");
        QAction *cutAction = menu.addAction("cut");
        QAction *copyAction = menu.addAction("copy");
        QAction *pasteAction = menu.addAction("paste");
        QAction *deleteAction = menu.addAction("delete");


        QAction *selectedAction = menu.exec(event->globalPos());
        if (selectedAction == moveAction){
            selectedItem->setPos(0,0);
        }
        else if (selectedAction == brushAction){
            // 这里实现刷新操作
    //        scene()->brush;
        }
        else if (selectedAction == cutAction){
            // 这里实现剪切操作

        }
        else if (selectedAction == copyAction) {
            // 这里实现复制操作
            QByteArray itemData;
            QDataStream dataStream(&itemData,QIODevice::WriteOnly); //创建数据流
            // 将Item的相关参数放入到字节数组中
            dataStream <<selectedItem->name()<<selectedItem->diagramType()<<selectedItem->point();
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

            dataStream >> name >> myType >> myPoint;
            MyItem tmpItem;
            tmpItem.setName(name);
            tmpItem.setType(myType);
            tmpItem.setPoint(myPoint);
            emit insertClipBordItem(&tmpItem);

//            delete tmpItem;
        }

        else if (selectedAction == deleteAction) {
            // 这里实现删除操作
        }
        else{
            qDebug() << "undefined Action";
        }
    }

    else{
        QGraphicsView::contextMenuEvent(event);
    }
}





