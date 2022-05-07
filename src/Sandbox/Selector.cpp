#include "Selector.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "src/Sandbox/Node.h"

Selector::Selector(const QRectF &rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent)
{
    setPen(Qt::SolidLine);
    setBrush(Qt::red);
}

Selector::~Selector()
{
    
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

void Selector::checkNodes(std::list<std::shared_ptr<Node>> nodes)
{
    for (auto& node : nodes)
    {
        const auto& r = this->shape();
        const auto& l = node->shape();
        qInfo("selector shape: %f:%f:%f:%f",r.currentPosition().x(),r.currentPosition().y(),r.boundingRect().width(),r.boundingRect().height());
        qInfo("node shape: %f:%f:%f:%f",l.currentPosition().x(),l.currentPosition().y(),l.boundingRect().width(),l.boundingRect().height());

        if (this->collidesWithItem(node.get()))

        if (node->collidesWithItem(this))
            setSelected(true);
    }
}