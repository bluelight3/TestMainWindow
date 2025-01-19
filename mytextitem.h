#ifndef MYTEXTITEM_H
#define MYTEXTITEM_H

#include <QObject>
#include <QGraphicsTextItem>
#include "global.h"

class MyTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    enum { Type = UserType + MYTEXTITEM_TYPE_OFFSET };

    MyTextItem(QGraphicsItem *parent = nullptr);
private:
    QString m_store_str;
protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


signals:
    void mySignal(QString);



};

#endif // MYTEXTITEM_H
