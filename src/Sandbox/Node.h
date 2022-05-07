#pragma once
#include <QGraphicsEllipseItem>

class Node : public QGraphicsEllipseItem
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
    
    void setSelected(bool value);
private:
    bool selected;
};
