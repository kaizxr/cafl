#include "Node.h"

#include "src/Utils/Utils.h"
#include "src/Utils/Constants.h"
#include "src/Sandbox/Edge/Edge.h"
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>

Node::Node(int id, QPoint pos, QString text, QGraphicsItem* parent) : SandboxObject(id, text)
{
    objectType = eSandboxType::NODE;
    pen = QPen(Qt::black, 2);
    radius = CONST["Node"]["radius"];
    selected = false;

    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(10);

    setPos(pos.x() - radius, pos.y() - radius);
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
    Q_UNUSED(event);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef DEBUG
    qInfo("Node::mouseMoveEvent");
#endif
    Q_UNUSED(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef DEBUG
    qInfo("Node::mouseReleaseEvent");
#endif
    Q_UNUSED(event);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef DEBUG
    qInfo("Node::mouseDoubleClickEvent");
#endif
    Q_UNUSED(event);
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
    Q_UNUSED(event);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
    Q_UNUSED(event);
}

QList<BaseEdge*> Node::getEdges() const
{
    return edgeList;
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

QPoint Node::centeredPos() const
{
    return QPoint(
        pos().x() + boundingRect().width() / 2,
        pos().y() + boundingRect().height() / 2
    );
}

void Node::addEdge(BaseEdge *edge)
{
    if (!edgeList.contains(edge))
        edgeList.push_back(edge);
}

void Node::removeEdge(BaseEdge *edge)
{
    QMutableListIterator<BaseEdge *> iter(edgeList);
    while (iter.hasNext()) {
        BaseEdge *e = iter.next();
        if (e == edge) {
            iter.remove();
            break;
        }
    }
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush((option->state & QStyle::State_Selected ? Qt::cyan: Qt::white));
    painter->setPen(pen);
    painter->drawEllipse(0, 0, 2 * radius, 2 * radius);
    painter->setFont(QFont("Times", 12, QFont::Bold));
    Q_UNUSED(widget);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (BaseEdge *edge, edgeList) {
            edge->adjust();
        }
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}