#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
//#include <QObject>
#include "global.h"
#include "myitemwidget.h"
#include "arrow.h"

class Arrow;

class MyItem : public QObject,public QGraphicsPolygonItem
{
    Q_OBJECT  // 之后创建的时候记得都加上Q_OBJECT
public:

    MyItem();
    MyItem(MyItem* myItem);
    enum MyType {MyTest1,MyTest2 };

    QRectF boundingRect() const override;       //返回图像外接矩形
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
    bool selectedStatus();
    void addArrow(Arrow *arrow);


    void setLength(int length);
    void setRect(const QRect &rect);

    QString toggle() const;
    void setToggle(const QString &toggle);

private:
    QColor brushColor;                  // 该Item绘制颜色
    MyType myDiagramType;               // 该Item的类型
    QString m_name;                     // 该Item的名称
    QPointF m_point;                    // 该Item相对scene的位置  实际暂不使用，可以用->pos()代替
    QString m_toggle;                   // 关于这个Item的注释，描述信息
    QVector<Arrow*> m_linkedArrow;      // 该Item所有相连的箭头
    QRect m_rect;                       // 图元外接矩形;
    int m_length;                       // 图元边长(如果使用的话)


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override; // 这个是传递式的，不会阻止事件传递。
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    void acceptSetName(QString myName);
    void acceptSetToggle(const QString &toggle);


signals:
    void insertDrops(MyItem* myItem);
    void selectItem();
    void insertTextItem(QString myString);
};

#endif // MYITEM_H
