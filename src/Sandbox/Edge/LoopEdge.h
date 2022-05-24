#pragma once
#include "BaseEdge.h"

class LoopEdge : public BaseEdge
{
public:
    LoopEdge(int id, Node *sourceNode, QString text = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPointF getCenterPos() const;
    QLineF getCenterLine() const;
    QPointF handlePos() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QPainterPath shape() const override;
    QPointF posText(QPainterPath path = QPainterPath()) const override;
protected:
    QPointF peakArrow() const;
    float getArrowAngle() const;
    virtual QPainterPath pathText() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    
    bool flHandlePress;
    QPointF center;
    QLineF centerLine;

    float radius;
    float angle;
    float offset;
};
