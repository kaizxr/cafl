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
    QPainterPath path;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void drawText(QPainter *painter, QPainterPath path, QString text);
    QPointF newPosBezier() const;
    QPointF posText() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QPainterPath pathBezierCurve() const;
    QPainterPath pathText() const override;
    qreal getAngleAtMiddle(QPainterPath path) const;
};