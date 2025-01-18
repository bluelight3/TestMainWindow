#include "command.h"



/**********************************************
* @projectName   TestMainWindow
* @brief         移动命令
* @func          Movecommand
* @param         void
* @return        void
* @author        gl
* @date          2024-12-29
**********************************************/
MoveCommand::MoveCommand(MyItem *myItem, const QPointF &oldPos, QUndoCommand *parent)
{
    m_myItem = myItem;
    m_newPos = myItem->pos();
    m_myOldPos = oldPos;
}

/**********************************************
* @projectName   TestMainWindow
* @brief         撤销移动命令
* @func          undo
* @param         void
* @return        void
* @author        gl
* @date          2024-12-29
**********************************************/
void MoveCommand::undo()
{
    m_myItem->setPos(m_myOldPos);
    m_myItem->scene()->update();
}

/**********************************************
* @projectName   TestMainWindow
* @brief         恢复移动命令
* @func          redo
* @param         void
* @return        void
* @author        gl
* @date          2024-12-29
**********************************************/
void MoveCommand::redo()
{
    m_myItem->setPos(m_newPos);
    m_myItem->scene()->update();
}

/**********************************************
* @projectName   TestMainWindow
* @brief         合并2次以上的移动命令
* @func          MoveCommand::mergeWith
* @param         void
* @return        void
* @author        gl
* @date          2024-12-29
**********************************************/
bool MoveCommand::mergeWith(const QUndoCommand *command)
{
    const MoveCommand *moveCommand = static_cast<const MoveCommand *>(command);
    MyItem *item = moveCommand->m_myItem;

    if (m_myItem != item)
    return false;

//    newPos = item->pos();
//    setText(QObject::tr("Move %1").arg(createCommandString(myDiagramItem, newPos)));

    return false;
}


/**********************************************
* @projectName   TestMainWindow
* @brief         添加图元命令
* @func          AddCommand
* @param         void
* @return        void
* @author        gl
* @date          2024-12-29
**********************************************/
AddCommand::AddCommand(MyItem *myItem, QGraphicsScene *scene, QUndoCommand *parent)
{
    m_myGraphicsScene = scene;
    m_myDiagramItem = myItem;

    scene->update();
//    setText(QObject::tr("Add %1").arg(createCommandString(myDiagramItem, myDiagramItem->scenePos())));
}




/**********************************************
* @projectName   TestMainWindow
* @brief         撤回添加命令
* @func          undo
* @param         void
* @return        void
* @author        gl
* @date          2024-12-29
**********************************************/
void AddCommand::undo()
{
    m_myGraphicsScene->removeItem(m_myDiagramItem);
    m_myGraphicsScene->update();
}

/**********************************************
* @projectName   TestMainWindow
* @brief         恢复添加命令
* @func          undo
* @param         void
* @return        void
* @author        gl
* @date          2024-12-29
**********************************************/
void AddCommand::redo()
{
    m_myGraphicsScene->addItem(m_myDiagramItem);
    m_myGraphicsScene->clearSelection();
    m_myGraphicsScene->update();
}


DeleteCommand::DeleteCommand(QGraphicsScene *graphicsScene, QUndoCommand *parent)
{

}

void DeleteCommand::undo()
{

}

void DeleteCommand::redo()
{

}
