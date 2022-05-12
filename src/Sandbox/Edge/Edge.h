#pragma once
#include "BaseEdge.h"

class Edge : public BaseEdge
{
public:
    Edge(int id, Node *sourceNode, Node *destNode = nullptr, QString text = nullptr);
    Edge(const QJsonObject &json);

protected:
    QPointF bezier;
    QLineF beforeLine;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPointF newPosBezier() const;
    QPointF posText() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QPainterPath pathBezierCurve() const;
};