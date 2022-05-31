#pragma once
#include <QGraphicsView>
#include "src/Sandbox/TextBox/TextListener.h"
#include "lib/json.hpp"
namespace AA
{
    class Automata;
}
class TextBox;
class QPlainTextEdit;
class BaseEdge;
class Node;
class Selector;
class GraphicsView : public QGraphicsView, public TextListener
{
public:
    GraphicsView(QWidget* parent = nullptr);
    ~GraphicsView();
    void reload();
    nlohmann::json toJson();
    void writeToJson();
    void openFromJson(const nlohmann::json& data);

    void addNode(int x, int y, int id = -1, bool isFinal = false, bool isInitial = false);
    void addEdge(int sourceId, int destId, QString text = nullptr, int id = -1);
    std::shared_ptr<Node> getNodeById(int id);

    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void onTextChanged(int code) override;

    void selectAllObjects();
    void startSimulateAction(QList<QString> input);
    AA::Automata* convertToFSA();
    void makeInitial(Node* node);
    void startRenameEdge(BaseEdge* edge);
    void removeObject(QGraphicsItem* item);
    AA::Automata* getAutomata();

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
    void makeNodesFinal();
    void tryMakeInitial();
    BaseEdge* checkEdge(Node* source, Node* dest);
    void setEdgeName(int code);
    
    std::shared_ptr<Selector> selector;

    QList<std::shared_ptr<Node>> nodes;
    QList<BaseEdge*> edges;

    eActionType actionType;

    BaseEdge* renamingEdge;
    std::shared_ptr<Node> initialNode;
    std::shared_ptr<Node> sourceNode;
    std::shared_ptr<Node> destNode;
    std::shared_ptr<TextBox> textEdit;

    int lastGivenNodeId;
    int lastGivenEdgeId;
    int oldmx;
    int oldmy;
};
