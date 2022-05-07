#pragma once
#include <QGraphicsRectItem>

class Node;
class Selector : public QGraphicsRectItem
{
public:
    Selector(const QRectF &rect, QGraphicsItem *parent = nullptr);
    ~Selector();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void checkNodes(std::list<std::shared_ptr<Node>> nodes);

private:
    QPoint startPoint;
};