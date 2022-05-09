#pragma once
#include <QGraphicsItem>
#include <QPen>

class Node : public QGraphicsItem
{
public:
    Node(qreal x, qreal y, qreal radius, QGraphicsItem* parent = nullptr);
    ~Node();
    
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPen pen;
    int radius;
    bool selected;
};
