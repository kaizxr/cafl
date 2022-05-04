#pragma once
#include <QGraphicsView>
// #include <QGraphicsScene>

class Node;
class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QRect rect, QWidget* parent = nullptr);
    ~GraphicsView();

    void addNode(std::shared_ptr<Node> node);
private:
    std::list<std::shared_ptr<Node>> nodes;
};