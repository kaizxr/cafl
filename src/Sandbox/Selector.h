#pragma once
#include <QGraphicsRectItem>

class QPainterPath;
class Node;
class Selector : public QGraphicsRectItem
{
public:
    Selector(const QRectF &rect, QGraphicsItem *parent = nullptr);
    ~Selector();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void checkNodes();

    QList<QGraphicsItem *> getSelectedNodes();
    QPainterPath getPath() const;

private:
    QList<QGraphicsItem *> nodes;
};