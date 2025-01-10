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

    void mousePressEvent(QMouseEvent *event) override;
//    void dragEnterEvent(QDragEnterEvent *event);
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;


signals:
    void insertItem();
    void removeItem(QGraphicsItem*);
    void addArrow(Arrow*);

    void insertClipBordItem(QPointF);
    void insertClipBordItem(QGraphicsItem*);
    void clear();
    void selectItem(QGraphicsItem*);

private:
    QPointF m_mousePos;
    bool m_bAcceptContextMenu;
    QGraphicsItem * m_pRightButtonPressItem = nullptr;
    bool m_bRightButtonPressed = false;
    MyItem* m_selectedItem;

//    Mode m_myMode;
    QGraphicsLineItem* m_line;

private slots:
    void acceptSetMyDragMode();

};

#endif // MYVIEW_H
