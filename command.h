#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QUndoCommand>

#include "myitem.h"
#include "arrow.h"
class Arrow;
class MoveCommand : public QObject,public QUndoCommand
{
    Q_OBJECT
public:

    enum {Id = 1234};
    MoveCommand(MyItem * myItem,const QPointF &oldPos,QUndoCommand *parent=0);


    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand *other) override;
    int id() const override {return Id;}

private:
    MyItem *m_myItem;
    QPointF m_myOldPos;
    QPointF m_newPos;
};

class DeleteCommand : public QUndoCommand
{
public:
    explicit DeleteCommand(QGraphicsScene *graphicsScene, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

private:
    QList<QGraphicsItem *> list_item;
    QMap<QGraphicsItem *, QList<Arrow *> > map_item_arrow;
    QGraphicsScene *myGraphicsScene;
};


class AddCommand : public QObject,public QUndoCommand
{
    Q_OBJECT
public:

    AddCommand(QGraphicsItem * myItem,QGraphicsScene* graphicsScene,QUndoCommand *parent=0);


    void undo() override;
    void redo() override;

private:
    QGraphicsItem *m_myItem;
    QGraphicsScene *m_myGraphicsScene;
    QPointF m_initialPosition;
    bool m_bFirstAdded;     //表示第一次Added，置为true 不知道为什么加入图元时会先调用一次redo，此标志位配置第一次加入时不调用redo的实际功能

};




#endif // COMMAND_H
