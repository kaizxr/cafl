#pragma once
#include <QGraphicsView>

class Edge;
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

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    enum class eActionType
    {
        NONE,
        SELECT,
        MOVE,
        ADD_EDGE
    };
private:
    void removeObjects();
    
    std::shared_ptr<Selector> selector;

    QList<QGraphicsItem*> selectedNodes;

    QList<std::shared_ptr<Node>> nodes;
    QList<Edge*> edges;

    eActionType actionType;

    std::shared_ptr<Node> sourceNode;
    std::shared_ptr<Node> destNode;

    int lastGivenNodeId;
    int lastGivenEdgeId;
    int oldmx;
    int oldmy;
};