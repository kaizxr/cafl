#pragma once
#include <QGraphicsView>

class QPlainTextEdit;
class Edge;
class Node;
class Selector;
class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget* parent = nullptr);
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
        ADD_EDGE,
        WAIT_EDGE_NAME,
        ADD_NODE,
        HAND_MOVE,
        MOVE
    };
private:
    void resizeEvent(QResizeEvent *event) override;
    void removeObjects();
    void setTool(int tooltype);
    
    std::shared_ptr<Selector> selector;

    QList<std::shared_ptr<Node>> nodes;
    QList<Edge*> edges;

    eActionType actionType;

    std::shared_ptr<Node> sourceNode;
    std::shared_ptr<Node> destNode;
    std::shared_ptr<QPlainTextEdit> textEdit;

    int lastGivenNodeId;
    int lastGivenEdgeId;
    int oldmx;
    int oldmy;
};