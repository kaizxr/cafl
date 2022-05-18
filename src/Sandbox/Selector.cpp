#include "Selector.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include "src/Sandbox/Node.h"

#include <QList>
#include <QGraphicsScene>

Selector::Selector(const QRectF &rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent)
{
    setPen(Qt::SolidLine);
    setBrush(Qt::red);
    setZValue(20);
}

Selector::~Selector()
{
    nodes.clear();
}

QRectF Selector::boundingRect() const
{
    if (rect().width() >= 0 && rect().height() >= 0)
        return QRectF(rect().x(),rect().y(),rect().x() + rect().width(),rect().y() + rect().height());
    else if (rect().width() <= 0 && rect().height() >= 0)
        return QRectF(rect().x() + rect().width(),rect().y(),rect().x(),rect().y() + rect().height());
    else if (rect().width() >= 0 && rect().height() <= 0)
        return QRectF(rect().x(),rect().y() + rect().height(),rect().x() + rect().width(),rect().y());
    else
        return QRectF(rect().x() + rect().width(),rect().y() + rect().height(),rect().x(),rect().y());
}

void Selector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const auto& r = boundingRect();
    float d = std::max(r.width(),r.height())*0.25f;
    const auto& updr = QRect(r.x()-d,r.y()-d,r.width()+d,r.height()+d);
    painter->drawPath(getPath());
    update(updr);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Selector::checkNodes()
{
    if (!nodes.empty())
    {
        for (auto node : nodes)
        {
            node->setSelected(false);
        }
    }
    nodes = collidingItems();
    for (auto node : nodes)
    {
        node->setSelected(true);
    }
}

QList<QGraphicsItem *> Selector::getSelectedNodes()
{
    return nodes;
}

QPainterPath Selector::getPath() const
{
    QPainterPath path;
    const auto& br = boundingRect();
    QPointF a = QPoint(br.x(),     br.y()     );
    QPointF b = QPoint(br.width(), br.y()     );
    QPointF c = QPoint(br.width(), br.height());
    QPointF d = QPoint(br.x(),     br.height());
    path.moveTo(a);
    path.lineTo(b);
    path.lineTo(c);
    path.lineTo(d);
    path.lineTo(a);
    return path;
}
