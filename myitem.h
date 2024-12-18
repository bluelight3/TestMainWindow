#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "myitemidget.h"


class MyItem : public QGraphicsItem
{
public:
    MyItem();
    MyItem(MyItem* myItem);
    enum MyType {MyTest1,MyTest2 };

    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget * widget) override;
    void setColor(const QColor & color) { brushColor = color; }
    void setType(MyType myType);
    void setName(QString myName);
    void setPoint(QPointF myPoint);

    QPainterPath shape() const override;
    QColor color() const;
    QPixmap image() const;
    QString name() const;
    QPointF point() const;
    MyType diagramType() const { return myDiagramType; }


private:
    QColor brushColor;
    MyType myDiagramType;
    QString m_name;
    QPointF m_point;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void insertDrops(MyItem* myItem);

};

#endif // MYITEM_H
