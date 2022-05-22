#pragma once
#include "src/Sandbox/SandboxObject.h"
#include <QGraphicsItem>
#include <QPen>

class BaseEdge;
class Node : public SandboxObject
{
public:
    Node(int id, QPoint pos, QString text = nullptr, QGraphicsItem* parent = nullptr);
    ~Node();
    
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    QList<BaseEdge*> getEdges() const;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    QPoint centeredPos() const;
    void addEdge(BaseEdge *edge);
    void removeEdge(BaseEdge *edge);

    bool isInitial();
    void setInitial(bool initial);
    bool isFinal();
    void setFinal(bool final);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    QList<BaseEdge*> edgeList;
    QPointF newPos;
    QPen pen;
    int radius;
    bool selected;

    bool initial;
    bool final;
};
