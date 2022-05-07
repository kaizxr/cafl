#include "Node.h"

#include "src/Utils/Utils.h"
#include <QBrush>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>

Node::Node(qreal x, qreal y, qreal radius, QGraphicsItem* parent) : QGraphicsEllipseItem(0,0,radius,radius,parent)
{
    selected = false;

    setPos(x - radius / 2, y - radius / 2);
    setBrush(Qt::blue);
    setAcceptHoverEvents(true);
}

Node::~Node()
{

}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qInfo("Node::mousePressEvent");
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qInfo("Node::mouseReleaseEvent");
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}


void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void Node::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

void Node::setSelected(bool value)
{
    selected = value;
    if (selected)
    {
        setBrush(Qt::red);
    }
    else
    {
        setBrush(Qt::blue);
    }
}
