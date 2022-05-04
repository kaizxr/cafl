#pragma once
#include <QGraphicsEllipseItem>

class Node : public QGraphicsEllipseItem
{
public:
    Node(qreal x, qreal y, qreal radius, QGraphicsItem* parent = nullptr);
    ~Node();

};
