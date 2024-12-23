#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "myitemidget.h"
#include "arrow.h"

class MyItem : public QGraphicsItem
{
public:
    MyItem();
    MyItem(MyItem* myItem);
    enum { Type = UserType + 16 };
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
    int type() const override { return Type; }

    void removeArrow(Arrow *arrow);
    QList<Arrow *> removeArrows();
    void addArrow(Arrow *arrow);
    QPointF getLinePoint();
    void setLinePoint(QPointF p);

private:
    // 图元类型
    QColor brushColor;
    MyType myDiagramType;
    QString m_name;
    QPointF m_point;
    QList<Arrow *> arrows;

    QPointF m_point_left;
    QPointF m_point_right;
    bool m_isLeft_Right = false;


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

signals:
    void insertDrops(MyItem* myItem);
    void removeItem(Arrow* arrow);  // 这里没搞清楚Arrow为什么不能自动转换成QGraphicsItem，先用这种方式移除箭头

};

#endif // MYITEM_H
