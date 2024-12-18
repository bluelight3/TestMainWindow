#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>
#include <QContextMenuEvent>
#include "myitem.h"
#include "mytextitem.h"
#include "global.h"

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget * parent = 0);
protected:
    void keyPressEvent(QKeyEvent *event) override;

//    void mousePressEvent(QMouseEvent *event) override;
//    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;


signals:
    void insertItem();
    void insertClipBordItem(QPointF);
    void insertClipBordItem(MyItem*);
    void insertClipBoardTextItem(MyTextItem*);
    void clear();


private:
    QPointF m_mousePos;
    bool m_bAcceptContextMenu;
    QGraphicsItem * m_pRightButtonPressItem = nullptr;
    bool m_bRightButtonPressed = false;
    MyItem* m_selectedItem;

};

#endif // MYVIEW_H
