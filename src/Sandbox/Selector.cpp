#include "Selector.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "src/Sandbox/Node.h"

#include <QList>

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
    QPoint upperLeft = QPoint(r.x(), r.y());
    QPoint upperRight = QPoint(r.width(), r.y());
    QPoint lowerLeft = QPoint(r.x(), r.height());
    QPoint lowerRight = QPoint(r.width(), r.height());
    painter->drawLine(upperLeft, upperRight);
    painter->drawLine(upperLeft, lowerLeft);
    painter->drawLine(upperRight, lowerRight);
    painter->drawLine(lowerLeft, lowerRight);
    update(updr);
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