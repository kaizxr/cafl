#include "Node.h"

#include "src/Utils/Utils.h"
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>

Node::Node(qreal x, qreal y, qreal radius, QGraphicsItem* parent)
{
    pen = QPen(Qt::black, 2);
    this->radius = radius;
    selected = false;

    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(10);

    setPos(x - radius, y - radius);
    setAcceptHoverEvents(true);
}

Node::~Node()
{

}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef DEBUG
    qInfo("Node::mousePressEvent");
#endif
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef DEBUG
    qInfo("Node::mouseMoveEvent");
#endif
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef DEBUG
    qInfo("Node::mouseReleaseEvent");
#endif
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef DEBUG
    qInfo("Node::mouseDoubleClickEvent");
#endif
}


void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void Node::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
#ifdef DEBUG
    qInfo("Node::hoverMoveEvent");
#endif
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-pen.width(), -pen.width(), 2 * radius + pen.width(), 2 * radius + pen.width());
    return path;
}

QRectF Node::boundingRect() const
{
    return shape().boundingRect();
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush((option->state & QStyle::State_Selected ? Qt::cyan: Qt::white));
    painter->setPen(pen);
    painter->drawEllipse(0, 0, 2 * radius, 2 * radius);
    painter->setFont(QFont("Times", 12, QFont::Bold));
}

