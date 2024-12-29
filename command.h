#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QUndoCommand>

#include "myitem.h"
#include "arrow.h"
class Arrow;
class Movecommand : public QUndoCommand
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
    MyItem *myItem;
    QPointF myOldPos;
    QPointF newPos;
};


class AddCommand : public QUndoCommand
{
    Q_OBJECT
public:

    AddCommand(MyItem * myItem,QGraphicsScene* graphicsScene,QUndoCommand *parent=0);


    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand *other) override;

private:
    MyItem *myItem;
    QPointF myOldPos;
    QPointF newPos;
};




#endif // COMMAND_H
