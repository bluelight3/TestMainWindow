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
    m_paintFlag = false;
    m_selectedItem = nullptr;


}

void MyView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
    {
        scale(1.2,1.2);
        break;
    }
    case Qt::Key_Alt:
    {
        m_paintFlag = true;
        break;
    }
    }
    QGraphicsView::keyPressEvent(event);
}

void MyView::keyReleaseEvent(QKeyEvent *event)
{
    m_paintFlag = false;
}

void MyView::mousePressEvent(QMouseEvent *event)
{

    MyItem * selectedItem;
    MyTextItem * selectedTextItem;
    if (control.getMyMode() == Mode::InsertItem)
    {
        selectedItem = dynamic_cast<MyItem*>(itemAt(event->pos()));
        selectedTextItem = dynamic_cast<MyTextItem*>(itemAt(event->pos()));

        if (selectedItem){
            QPoint mousePos = event->pos();
            selectedItem= dynamic_cast<MyItem*>(itemAt(mousePos));

            if (selectedItem!= 0 && event->button() == Qt::LeftButton) {
                oldPos =selectedItem->pos();
            }
        }
        else if (selectedTextItem){
             setDragMode(QGraphicsView::NoDrag);
        }
        else{
//            emit selectItem(m_selectedItem);
        }
    }
    else if (control.getMyMode() == InsertLine){
        m_selectedItem= dynamic_cast<MyItem*>(itemAt(event->pos()));
        m_line = new QGraphicsLineItem(QLineF(event->pos(),
                                              event->pos()));
        m_line->setPen(QPen(Qt::black, 2));
        m_line2 = new QGraphicsLineItem(QLineF(event->pos(),
                                              event->pos()));
        m_line2 ->setPen(QPen(Qt::black, 2));
        scene()->addItem(m_line);
        scene()->addItem(m_line2);
    }


    return QGraphicsView::mousePressEvent(event);
}

void MyView::mouseMoveEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
    if (control.getMyMode() == Mode::InsertLine && m_line != nullptr) {
        QPointF tmpPoint = QPointF(event->pos().x(),m_line->line().p1().y());
        QLineF newLine(m_line->line().p1(), tmpPoint);
        QLineF newLine2(tmpPoint, event->pos());
        m_line->setLine(newLine);
        m_line2->setLine(newLine2);

    } else if (control.getMyMode() == Mode::MoveItem) {
        QGraphicsView::mouseMoveEvent(event);

    }
    else{
        QGraphicsView::mouseMoveEvent(event);
    }
    update();
}

void MyView::mouseReleaseEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();

    if (m_line != nullptr && control.getMyMode() == Mode::InsertLine) {
        QList<QGraphicsItem *> startItems = items(m_line->line().p1().x(),m_line->line().p1().y());
        if (startItems.count() && startItems.first() == m_line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(m_line2->line().p2().x(),m_line2->line().p2().y());
        if (endItems.count() && endItems.first() == m_line2)
            endItems.removeFirst();
        qDebug() << m_line << m_line2;

        emit removeItem(m_line);
        emit removeItem(m_line2);
        //        delete m_line;
        //! [11] //! [12]

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == MyItem::Type &&
                endItems.first()->type() == MyItem::Type &&
                startItems.first() != endItems.first()) {
            MyItem *startItem = qgraphicsitem_cast<MyItem  *>(startItems.first());
            MyItem *endItem = qgraphicsitem_cast<MyItem  *>(endItems.first());

            auto p1 = m_line->mapToParent(m_line->line().p1() );
            auto p2 = m_line->mapToParent(m_line->line().p2() );
            startItem->setLinePoint( p1 );
            endItem->setLinePoint( p2 );


            Arrow *arrow = new Arrow(startItem, endItem);
            arrow->setColor(Qt::black);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            arrow->updatePosition();
            emit addArrow(arrow);

        }
        m_line = nullptr;
    }
    //! [12] //! [13]
    if (control.getMyMode() != Mode::InsertLine)
    {
//        QPoint mousePos =   event->pos();
//        m_selectedItem = dynamic_cast<MyItem*>(itemAt(mousePos));
        setDragMode(QGraphicsView::RubberBandDrag);
        if (m_selectedItem != 0 && event->button() == Qt::LeftButton) {
            if (oldPos != m_selectedItem->pos() && m_selectedItem->type()==MyItem::Type )
                emit moveItem(m_selectedItem,oldPos);
        }

    }


    for (auto item : scene()->selectedItems() ) {
        auto p = item->pos();
        p.setX( int(p.x()/10)*10 );
        p.setY( int(p.y()/10)*10 );
        item->setPos(p);
    }

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

void MyView::paintEvent(QPaintEvent *event)
{

    QPainter painter(this->viewport());

    if (m_paintFlag){
        QPen pen;
        pen.setWidth(1);
        pen.setColor(Qt::red);
        painter.setPen(pen);

        //绘制横向线
        painter.drawLine(0, m_lastPos.y(), width(), m_lastPos.y());
        //绘制纵向线
        painter.drawLine(m_lastPos.x(), 0, m_lastPos.x(), height());
    }
    return QGraphicsView::paintEvent(event);
}


void MyView::contextMenuEvent(QContextMenuEvent *event)
{

    MyItem * selectedItem = dynamic_cast<MyItem*>(itemAt(event->pos()));
    MyTextItem * selectedTextItem = dynamic_cast<MyTextItem*>(itemAt(event->pos()));
//    qDebug() << selectedItem->type();
//    qDebug() << selectedTextItem->type();

    if (!selectedItem && !selectedTextItem){
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

            QClipboard* clipBoard = QApplication::clipboard(); // 自定义剪切板，只在view中实现做参考因此定义在这
            const QMimeData* mimeData = clipBoard->mimeData();
            // 判断是否存在我们要的数据
            if (mimeData->hasFormat("application/myItem")){
                QByteArray itemData = mimeData->data("application/myItem");
                QDataStream dataStream(&itemData,QIODevice::ReadOnly);
                QString name;
                MyItem::MyType myType;
                QPointF myPoint;
                QColor color;
                QString toggle;

                dataStream >> color >> name >> myType >> myPoint >> toggle;
                MyItem tmpItem;
                tmpItem.setColor(color);
                tmpItem.setName(name);
                tmpItem.setType(myType);
                tmpItem.setPoint(myPoint);
                tmpItem.setToggle(toggle);
                emit insertClipBordItem(&tmpItem);
            }
            else if (mimeData->hasFormat("application/myTextItem")){
                QByteArray itemData = mimeData->data("application/myTextItem");
                QDataStream dataStream(&itemData,QIODevice::ReadOnly);

                QString text;
                dataStream >> text;
                MyTextItem tmpTextItem;
                tmpTextItem.setPlainText(text);
                emit insertClipBordItem(&tmpTextItem);
            }

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


    else if ( selectedItem && selectedItem->Type == QGraphicsItem::UserType + MYITEM_TYPE_OFFSET){
        QMenu menu;
        QAction *moveAction = menu.addAction("移回");
        QAction *brushAction = menu.addAction("刷新");
        QAction *cutAction = menu.addAction("剪切");
        QAction *copyAction = menu.addAction("复制");
        QAction *pasteAction = menu.addAction("粘贴");
        QAction *deleteAction = menu.addAction("删除");
        QAction *propertyAction = menu.addAction("属性");

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
            QString toggle;

            dataStream >> color >> name >> myType >> myPoint >> toggle;
            MyItem tmpItem;
            tmpItem.setColor(color);
            tmpItem.setName(name);
            tmpItem.setType(myType);
            tmpItem.setPoint(myPoint);
            tmpItem.setToggle(toggle);
            emit insertClipBordItem(&tmpItem);

            //            delete tmpItem;
        }

        else if (selectedAction == deleteAction) {
            emit removeItem(selectedItem);  // 删除选中Item
            // 这里实现删除操作
        }
        else if (selectedAction == propertyAction) {
            control.showProperty(selectedItem);
        }
        else{
            qDebug() << "not defined Action";
        }
    }


    else if ( selectedTextItem &&
              selectedTextItem->Type ==
              QGraphicsItem::UserType + MYTEXTITEM_TYPE_OFFSET
              && !selectedTextItem->hasFocus()){
        QMenu menu;
        QAction *moveAction = menu.addAction("移回");
        QAction *cutAction = menu.addAction("剪切");
        QAction *copyAction = menu.addAction("复制");
        QAction *pasteAction = menu.addAction("粘贴");
        QAction *deleteAction = menu.addAction("删除");
        menu.addSeparator();
        QMenu subMenu;
        subMenu.setTitle("添加至图元");
        QList <QAction*> addToItemActions;

        // 获取所有MyItem图元名称
        for (int i = 0; i < control.getMyItems()->size();i++){
            MyItem* tmpItem = control.getMyItems()->at(i);
            QAction* tmpAddToItemAction = subMenu.addAction(tmpItem->name());
            if (tmpItem->childItems().size()>0){
                tmpAddToItemAction->setEnabled(false);
            }
            addToItemActions.append(tmpAddToItemAction);
        }
        menu.addMenu(&subMenu);
        QAction *selectedAction = menu.exec(event->globalPos());
        if (selectedAction == moveAction){
            qDebug() <<"move back!";
            selectedTextItem->setPos(0,0);
        }
        else if (selectedAction == cutAction){
            // 这里实现剪切操作
        }
        else if (selectedAction == copyAction) {
            // 这里实现复制操作 后续改成根据复制的Item是MyItem还是TextItem执行不同的操作
            QByteArray itemData;

            QDataStream dataStream(&itemData,QIODevice::WriteOnly); //创建数据流
            // 将Item的相关参数放入到字节数组中
            dataStream <<selectedTextItem->toPlainText();
            // 多个复制需要将多个Item一起放到 dataStrem中 一个解决方案就是先指定有多少个Item，然后一个一个把Item放进去 ()
            // 将数据放入QMimeData中
            QMimeData* mimeData = new QMimeData;
            // 第四步 将字节数组放入QMimeData中，此处Mime类型由自己定义
            mimeData->setData("application/myTextItem",itemData);
            QClipboard* clipBoard = QApplication::clipboard(); // 自定义剪切板，只在view中实现做参考因此定义在这
            clipBoard->setMimeData(mimeData);

        }
        else if (selectedAction == pasteAction) {
            // 这里实现粘贴操作
            QClipboard* clipBoard = QApplication::clipboard(); // 自定义剪切板，只在view中实现做参考因此定义在这
            const QMimeData* mimeData = clipBoard->mimeData();
            // 判断是否存在我们要的数据
            if (!mimeData->hasFormat("application/myTextItem")){
                return;
            }
            // 取出数据
            QByteArray itemData = mimeData->data("application/myTextItem");

            QDataStream dataStream(&itemData,QIODevice::ReadOnly);
            QString text;
            dataStream >> text;
            MyTextItem tmpTextItem;
            tmpTextItem.setPlainText(text);
            emit insertClipBordItem(&tmpTextItem);

            //            delete tmpItem;
        }
        else if (selectedAction == deleteAction) {
            emit removeItem(selectedTextItem);  // 删除选中Item
            // 这里实现删除操作
        }
        else if (addToItemActions.indexOf(selectedAction) >= 0) {
            int index = addToItemActions.indexOf(selectedAction);
            // 找到所有的Item项
            selectedItem = (*control.getMyItems())[index]; // 复用一下这个变量作为父Item

            selectedTextItem->setParentItem((selectedItem));
            selectedTextItem->setPos(QPointF(-60,-80));
            selectedTextItem->setZValue(selectedItem->zValue()+1);
            qDebug() << "set item "<< index << "as a child of " << (*control.getMyItems())[index]->name();
            //            emit removeItem(selectedTextItem);  //
            // 这里实现将该TextItem设置为其子Item的操作
        }

        else{
            qDebug() << "not defined Action";
        }
    }

    else{
        QGraphicsView::contextMenuEvent(event);
    }
//    QGraphicsView::contextMenuEvent(event);
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






