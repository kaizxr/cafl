#include "GraphicsView.h"

#include "src/Utils/Utils.h"
#include "src/Sandbox/Node.h"
#include "src/Sandbox/Selector.h"
#include "src/Sandbox/Edge/Edge.h"

#include <QGraphicsItem>
#include <QMouseEvent>

#define DEBUG

GraphicsView::GraphicsView(QRect rect, QWidget* parent) : QGraphicsView(parent)
{
#ifdef DEBUG
    qInfo("GraphicsView constructor");
#endif
    this->setScene(new QGraphicsScene(this));
    this->setSceneRect(rect);
#ifdef DEBUG
    qInfo("scene rect = %f:%f:%f:%f\n ", scene()->sceneRect().x(), scene()->sceneRect().y(), scene()->sceneRect().width(), scene()->sceneRect().height());
#endif
    lastGivenNodeId = 0;
    lastGivenEdgeId = 0;
    actionType = eActionType::NONE;
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::addNode(int x, int y)
{
    std::shared_ptr<Node> node = std::make_shared<Node>(lastGivenNodeId++, QPoint(x, y));
    scene()->addItem(node.get());
    nodes.push_back(node);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
#ifdef DEBUG
    qInfo("GraphicsView::mousePressEvent");
#endif
    QGraphicsView::mousePressEvent(event);

    oldmx = event->pos().x();
    oldmy = event->pos().y();
    
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        bool intersects = false;
        for (const auto& node : nodes)
        {
            if (node->contains(event->pos()-node->pos()))
            {
                intersects = true;
                if (selectedNodes.indexOf(node.get()) == -1 && selectedNodes.empty())
                {
                    selectedNodes.push_back(node.get());
                    node->setSelected(true);
                }
            }
        }

        if (!selector && !scene()->selectedItems().size())
        {
            selectedNodes.clear();
            actionType = eActionType::SELECT;
            selector = std::make_shared<Selector>(QRect(event->pos().x(),event->pos().y(),10,10));
            scene()->addItem(selector.get());
        }
        else if (!selector && scene()->selectedItems().size())
        {
            actionType = eActionType::MOVE;
        }
    }
    else if (event->button() == Qt::MouseButton::MiddleButton)
    {
        addNode(event->pos().x(),event->pos().y());
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
        actionType = eActionType::ADD_EDGE;

        for (const auto& node : nodes)
        {
            if (node->contains(event->pos()-node->pos()))
            {
                sourceNode = node;
                qInfo("source node id = %d pos = %f:%f",sourceNode->id(),sourceNode->pos().x(),sourceNode->pos().y());
                break;
            }
        }

    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
#ifdef DEBUG_MOVE
    qInfo("GraphicsView::mouseMoveEvent");
#endif
    switch (actionType)
    {
    case eActionType::NONE:
        break;
    case eActionType::SELECT:
#ifdef DEBUG_MOVE
        qInfo("move eActionType::SELECT");
#endif
        selector->setRect(
            selector->rect().x(), selector->rect().y(),
            event->pos().x() - selector->rect().x(),
            event->pos().y() - selector->rect().y()
        );

        selector->checkNodes();
        break;
    case eActionType::MOVE:
#ifdef DEBUG_MOVE
        qInfo("eActionType::MOVE");
        qInfo("size = %d",selectedNodes.size());
#endif
        for (auto& node : selectedNodes)
        {
#ifdef DEBUG_MOVE
            qInfo("moveBy = %d:%d",event->pos().x()-oldmx,event->pos().y()-oldmy);
#endif
            if (node->type() == (int)eSandboxType::NODE)
                node->moveBy(event->pos().x()-oldmx,event->pos().y()-oldmy);
        }
        break;
    }
    oldmx = event->pos().x();
    oldmy = event->pos().y();
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    switch (actionType)
    {
    case eActionType::NONE:
        break;
    case eActionType::SELECT:
#ifdef DEBUG
        qInfo("release eActionType::SELECT");
        qInfo("remove selector");
#endif
        selectedNodes = selector->getSelectedNodes();
        scene()->removeItem(selector.get());
        selector.reset();
        break;
    case eActionType::MOVE:
#ifdef DEBUG
        qInfo("release eActionType::MOVE");
        qInfo("size = %d",selectedNodes.size());
#endif
        if (selectedNodes.size() == 1)
        {
            selectedNodes.front()->setSelected(false);
            selectedNodes.clear();
        }
        break;
    case eActionType::ADD_EDGE:
        for (const auto& node : nodes)
        {
            if (node->contains(event->pos()-node->pos()))
            {
                destNode = node;
                qInfo("dest node id = %d pos = %f:%f",destNode->id(),destNode->pos().x(),destNode->pos().y());
                Edge* edge = new Edge(lastGivenEdgeId++,sourceNode.get(),destNode.get());
                edges.append(edge);
                scene()->addItem(edge);
                break;
            }
        }
        break;
    }

    QGraphicsView::mouseReleaseEvent(event);
    actionType = eActionType::NONE;
}
