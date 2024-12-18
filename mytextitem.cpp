#include "mytextitem.h"


MyTextItem::MyTextItem(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    m_store_str = "Text";
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);


    setSelected(true);
}

MyTextItem::MyTextItem(MyTextItem *myTextItem)
{
    m_store_str=myTextItem->m_store_str;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setSelected(true);
    setFocus();
}

void MyTextItem::focusInEvent(QFocusEvent *event)
{
    if(event->reason() != Qt::PopupFocusReason){//注意右键菜单再次进入焦点时不保存原始文本
        m_store_str = toPlainText();//保存原始文本
    }
    QGraphicsTextItem::focusInEvent(event);
}

void MyTextItem::focusOutEvent(QFocusEvent *event)
{
    if (event->reason() == Qt::MouseFocusReason && QApplication::mouseButtons()==Qt::RightButton){
        //右键点击其他地方失去焦点，定义为取消操作，恢复原始文本
        setPlainText(m_store_str);
        setTextInteractionFlags(Qt::NoTextInteraction);//恢复不能编辑状态
    }
    else if(event->reason() == Qt::PopupFocusReason){//右键弹出菜单时不做处理
    }else{//其他情况，包括下面点击回车的情况，编辑成功，发送信号给父对象
        setTextInteractionFlags(Qt::NoTextInteraction);
        setPlainText(toPlainText());
//        emit mySignal(toPlainText());
    }
    QGraphicsTextItem::focusOutEvent(event);
}

void MyTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){//左键双击进入可编辑状态并打开焦点
        setTextInteractionFlags(Qt::TextEditorInteraction);
        setFocus();
        QGraphicsTextItem::mouseDoubleClickEvent(event);
    }
}


void MyTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        //左键点击是可编辑状态的话响应单击事件
        if(textInteractionFlags() != Qt::NoTextInteraction){
            QGraphicsTextItem::mousePressEvent(event);
        }//是不可编辑状态的话，也就是未双击进入编辑状态时不响应，一遍产生双击事件
    }else{//其他按键正常流程
        QGraphicsTextItem::mousePressEvent(event);
    }
}

void MyTextItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return||event->key() == Qt::Key_Enter)
    {
    //点击回车失去焦点，编辑完成，后续给FocusOutEvent处理
        clearFocus();
    }else{
        QGraphicsTextItem::keyPressEvent(event);
    }
}
