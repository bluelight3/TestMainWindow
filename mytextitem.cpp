#include "mytextitem.h"


MyTextItem::MyTextItem(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void MyTextItem::focusInEvent(QFocusEvent *event){
    if (event->reason() !=Qt::PopupFocusReason){ //右键菜单再次进入焦点时不保存原始文本
        m_store_str = toPlainText();    //保存原始文本
    }
    QGraphicsTextItem::focusInEvent(event);
}


void MyTextItem::focusOutEvent(QFocusEvent *event){
    if (event->reason() == Qt::MouseFocusReason &&QApplication::mouseButtons() == Qt::RightButton){
        setPlainText(m_store_str);
        setTextInteractionFlags(Qt::NoTextInteraction);
    }
    else if (event->reason() == Qt::PopupFocusReason){ //右键弹出菜单时不做处理，

    }
    else{//其他情况，包括下面点击回车的情况，编辑成功，发送信号给父对象
        setTextInteractionFlags(Qt::NoTextInteraction);
        emit mySignal(toPlainText());
    }
    QGraphicsItem::focusOutEvent(event);
}

void MyTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if (event->buttons() == Qt::LeftButton){
        setTextInteractionFlags(Qt::TextEditorInteraction);
        setFocus();
        QGraphicsTextItem::mouseDoubleClickEvent(event);
    }
}

void MyTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // 左键点击如果可编辑状态的话响应事件
    if (event->button() == Qt::LeftButton){
        if (textInteractionFlags() != Qt::NoTextInteraction){
            QGraphicsTextItem::mousePressEvent(event);
        }   // 是不可编辑状态的话，未双击进入编辑状态时不响应，一遍产生双击事件
        else{
            QGraphicsTextItem::mousePressEvent(event);
        }
    }
}

void MyTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}
void MyTextItem::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Down)
        moveBy(0,10);
    if (event->key() == Qt::Key_Up)
        moveBy(0,-10);
    if (event->key() == Qt::Key_Left)
        moveBy(-10,0);
    if (event->key() == Qt::Key_Right)
        moveBy(10,0);

    return QGraphicsTextItem::keyPressEvent(event);
}

