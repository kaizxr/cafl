#pragma once
#include <QGraphicsView>

class Node;
class Selector;
class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QRect rect, QWidget* parent = nullptr);
    ~GraphicsView();

    void addNode(int x, int y);

    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    std::list<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Selector> selector;
};