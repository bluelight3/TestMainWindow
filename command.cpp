#include "command.h"



AddCommand::AddCommand(MyItem *myItem, QGraphicsScene *graphicsScene, QUndoCommand *parent)
{

}

void AddCommand::undo()
{

}

void AddCommand::redo()
{

}

bool AddCommand::mergeWith(const QUndoCommand *other)
{

}

Movecommand::Movecommand(MyItem *myItem, const QPointF &oldPos, QUndoCommand *parent)
{

}

void Movecommand::undo()
{

}

void Movecommand::redo()
{

}

bool Movecommand::mergeWith(const QUndoCommand *other)
{

}
