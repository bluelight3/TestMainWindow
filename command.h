#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QUndoCommand>

#include "myitem.h"
#include "arrow.h"
class Arrow;
class Movecommand : public QObject,public QUndoCommand
{
    Q_OBJECT
public:

    enum {Id = 1234};
    Movecommand(MyItem * myItem,const QPointF &oldPos,QUndoCommand *parent=0);


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

    AddCommand(MyItem * myItem,QGraphicsScene* graphicsScene,QUndoCommand *parent=0);


    void undo() override;
    void redo() override;

private:
    MyItem *m_myDiagramItem;
    QGraphicsScene *m_myGraphicsScene;
    QPointF m_initialPosition;


};




#endif // COMMAND_H
