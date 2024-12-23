#ifndef MYTEXTITEM_H
#define MYTEXTITEM_H

#include <QObject>
#include <QGraphicsTextItem>
#include "global.h"

class MyTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 4 };
    MyTextItem(QGraphicsItem *parent = 0);
    MyTextItem(MyTextItem* myTextItem);
    int type() const override { return Type; }
signals:
    void mySignal(QString);
    void selectedChange(QGraphicsItem *item);

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


private:
    QString m_store_str; //保存字符串
};

#endif // MYTEXTITEM_H
