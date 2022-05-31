#include "ContextMenu.h"
#include <QGraphicsItem>
#include "src/Sandbox/Node.h"
#include "src/Sandbox/Edge/BaseEdge.h"
#include "src/Windows/WindowsManager.h"
#include "src/Windows/SandboxWindow/SandboxWindow.h"
#include "src/Windows/PlaygroundWindow/PlaygroundWindow.h"
#include "src/Sandbox/GraphicsView.h"

ContextMenu::ContextMenu(QGraphicsItem* item, QWidget* parent)
    : QMenu(parent), item(item)
{
    if (auto casted = dynamic_cast<Node*>(item))
    {
        this->addAction("make initial");
        this->addAction("make final");
        this->addAction("remove");
        connect(actions().at(0), &QAction::triggered, this, &ContextMenu::makeInitial );
        connect(actions().at(1), &QAction::triggered, this, &ContextMenu::makeFinal   );
        connect(actions().at(2), &QAction::triggered, this, &ContextMenu::remove      );
    }
    if (auto casted = dynamic_cast<BaseEdge*>(item))
    {
        this->addAction("rename");
        this->addAction("remove");
        connect(actions().at(0), &QAction::triggered, this, &ContextMenu::rename );
        connect(actions().at(1), &QAction::triggered, this, &ContextMenu::remove );
    }
}

ContextMenu::~ContextMenu()
{

}

void ContextMenu::makeInitial()
{
    if (auto casted = dynamic_cast<Node*>(item))
    {
        if (auto sandbox = dynamic_cast<SandboxWindow*>(WINDOWS->getCurWindow()))
            sandbox->getGraphicsView()->makeInitial(casted);
        else if (auto playground = dynamic_cast<PlaygroundWindow*>(WINDOWS->getCurWindow()))
            playground->getGraphicsView()->makeInitial(casted);
    }
}

void ContextMenu::makeFinal()
{
    if (auto casted = dynamic_cast<Node*>(item))
        casted->setFinal(!casted->isFinal());
}

void ContextMenu::rename()
{
    if (auto casted = dynamic_cast<BaseEdge*>(item))
    {
        if (auto sandbox = dynamic_cast<SandboxWindow*>(WINDOWS->getCurWindow()))
            sandbox->getGraphicsView()->startRenameEdge(casted);
        else if (auto playground = dynamic_cast<PlaygroundWindow*>(WINDOWS->getCurWindow()))
            playground->getGraphicsView()->startRenameEdge(casted);

    }
}

void ContextMenu::remove()
{
    if (auto sandbox = dynamic_cast<SandboxWindow*>(WINDOWS->getCurWindow()))
        sandbox->getGraphicsView()->removeObject(item);
    else if (auto playground = dynamic_cast<PlaygroundWindow*>(WINDOWS->getCurWindow()))
        playground->getGraphicsView()->removeObject(item);
}