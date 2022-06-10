#include "GraphicsView.h"

#include "src/Utils/Utils.h"
#include "src/Sandbox/Node.h"
#include "src/Sandbox/Selector.h"
#include "src/Sandbox/Edge/Edge.h"
#include "src/Sandbox/Edge/LoopEdge.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QKeyEvent>

#include "src/Utils/Constants.h"
#include "src/Sandbox/ToolsManager.h"
#include "src/Sandbox/Buttons/ToolButtonGroup.h"
#include <QAbstractButton>

#include "src/Windows/WindowsManager.h"
#include "src/Windows/SandboxWindow/SandboxWindow.h"
#include <QPlainTextEdit>
#include <iostream>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>

#include "src/Sandbox/TextBox/TextBox.h"
#include <src/Windows/Simulation/Output.h>
#include "src/Automata/Helpers/SimulateHelper.h"

#define DEBUG

GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView(parent)
{
#ifdef DEBUG
    qInfo("GraphicsView constructor");
#endif
    this->setScene(new QGraphicsScene(this));
    lastGivenNodeId = 0;
    lastGivenEdgeId = 0;
    actionType = eActionType::NONE;
    textEdit = nullptr;
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::reload()
{
    selectAllObjects();
    removeObjects();
    lastGivenEdgeId = 0;
    lastGivenNodeId = 0;
    initialNode.reset();
    sourceNode.reset();
    destNode.reset();
    textEdit.reset();
    selector.reset();
    nodes.clear();
    edges.clear();
    actionType = eActionType::NONE;
    update(0,0,rect().width(),rect().height());
}

nlohmann::json GraphicsView::toJson()
{
    nlohmann::json data;
    for (const auto& node : nodes)
    {
        const auto& nodeStr = QString::number(node->id()).toStdString().c_str();
        data["Graph"]["Node"][nodeStr]["pos"]["x"] = node->pos().x();
        data["Graph"]["Node"][nodeStr]["pos"]["y"] = node->pos().y();
        if (node->isInitial())
            data["Graph"]["Node"][nodeStr]["initial"] = true;
        if (node->isFinal())
            data["Graph"]["Node"][nodeStr]["final"] = true;
    }
    for (const auto& edge : edges)
    {
        const auto& edgeStr = QString::number(edge->id()).toStdString().c_str();
        data["Graph"]["Edge"][edgeStr]["source"] = edge->sourceNode()->id();
        data["Graph"]["Edge"][edgeStr]["dest"] = edge->destNode()->id();
        data["Graph"]["Edge"][edgeStr]["text"] = edge->textContent().toStdString().c_str();
    }
    std::cout << std::setw(4) << data << std::endl;
    return data;
}

void GraphicsView::writeToJson()
{
    if (auto casted = dynamic_cast<SandboxWindow*>(WINDOWS->getCurWindow()))
    {
        const auto& data = toJson();
        casted->saveJson(data);
    }
}

void GraphicsView::openFromJson(const nlohmann::json& data)
{
    qInfo("openFromJson");
    if (data.is_null())
        return;
    selectAllObjects();
    removeObjects();
    lastGivenEdgeId = 0;
    lastGivenNodeId = 0;
    qInfo("objects removed");
    for (auto it = data["Graph"]["Node"].begin(); it != data["Graph"]["Node"].end(); ++it)
    {
        std::cout << it.key() << " | " << it.value() << "\n";
        auto id = std::stoi(it.key());
        int radius = CONST["Node"]["radius"];
        int x = it.value()["pos"]["x"];
        int y = it.value()["pos"]["y"];
        bool final = false;
        bool initial = false;
        if (it.value().contains("final"))
            final = it.value()["final"];
        if (it.value().contains("initial"))
            initial = it.value()["initial"];
        x += radius;
        y += radius;
        addNode(x,y,id,final,initial);
    }
    std::cout << "nodes added" << std::endl;
    if (data["Graph"].contains("Edge") && data["Graph"]["Edge"].is_array())
    {
        for (auto it = data["Graph"]["Edge"].begin(); it != data["Graph"]["Edge"].end(); ++it)
        {
            std::cout << it.key() << " | " << it.value() << "\n";
            auto id = std::stoi(it.key());
            int sourceId = it.value()["source"];
            int destId = it.value()["dest"];
            std::string stdtext = it.value()["text"];
            QString text(stdtext.c_str());
            addEdge(sourceId,destId,text,id);
        }
        std::cout << "edges added" << std::endl;
    }
}

void GraphicsView::addNode(int x, int y, int id, bool isFinal, bool isInitial)
{
    if (id == -1)
        id = lastGivenNodeId++;
    else
        lastGivenNodeId = id+1;
    std::shared_ptr<Node> node = std::make_shared<Node>(id, QPoint(x, y));
    node->setFinal(isFinal);
    node->setInitial(isInitial);
    scene()->addItem(node.get());
    if (nodes.length() == 0)
    {
        node->setInitial(true);
        initialNode = node;
    }
    nodes.push_back(node);
}

void GraphicsView::addEdge(int sourceId, int destId, QString text, int id)
{
    auto oldEdge = checkEdge(getNodeById(sourceId).get(),getNodeById(destId).get());

    if (!oldEdge)
    {
        if (id == -1)
        id = lastGivenEdgeId++;
        else
            lastGivenEdgeId = id+1;
        BaseEdge* edge;
        if (sourceId != destId)
            edge = new Edge(id,getNodeById(sourceId).get(),getNodeById(destId).get(),text);
        else
            edge = new LoopEdge(id,getNodeById(sourceId).get(),text);
        edges.append(edge);
        scene()->addItem(edge);
    }
    else
    {
        if (!text.isEmpty())
        {
            const auto oldText = oldEdge->textContent().split("; ");
            bool existing = false;

            for (const auto& t : oldText)
            {
                if (t == text)
                {
                    existing = true;
                    break;
                }
            }
            if (!existing)
            {
                text = oldEdge->textContent() + "; " + text;
                oldEdge->setTextContent(text);
            }
        }
    }
}

BaseEdge* GraphicsView::checkEdge(Node* source, Node* dest)
{
    const auto& list = source->getEdges();

    for (const auto& edge : list)
    {
        if (edge->sourceNode()->id() == source->id() && edge->destNode()->id() == dest->id())
            return edge;
    }
    return nullptr;
}

std::shared_ptr<Node> GraphicsView::getNodeById(int id)
{
    for (const auto& node : nodes)
        if (node->id() == id)
            return node;
    return nullptr;
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        for (const auto& edge : edges)
        {
            if (edge->contains(event->pos()-edge->pos()))
            {
                startRenameEdge(edge);
            }
        }
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
    oldmx = event->pos().x();
    oldmy = event->pos().y();
    
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        const auto& tool = TOOLS->tool();
        bool intersects = false;
        switch (tool)
        {
        case ToolsManager::eToolType::SELECT:
            QGraphicsView::mousePressEvent(event);

            for (const auto& node : nodes)
            {
                if (node->contains(event->pos()-node->pos()))
                {
                    intersects = true;
                    if (scene()->selectedItems().indexOf(node.get()) == -1 && scene()->selectedItems().empty())
                    {
                        node->setSelected(true);
                    }
                    else if (scene()->selectedItems().indexOf(node.get()) == -1 && !scene()->selectedItems().empty())
                    {
                        scene()->clearSelection();
                        node->setSelected(true);
                    }
                }
            }
            for (const auto& edge : edges)
            {
                if (edge->contains(event->pos()-edge->pos()))
                {
                    intersects = true;
                    if (scene()->selectedItems().indexOf(edge) == -1 && scene()->selectedItems().empty())
                    {
                        edge->setSelected(true);
                    }
                    else if (scene()->selectedItems().indexOf(edge) == -1 && !scene()->selectedItems().empty())
                    {
                        scene()->clearSelection();
                        edge->setSelected(true);
                    }
                }
            }
            if (!intersects)
                scene()->clearSelection();

            if (!selector && !scene()->selectedItems().size())
            {
                selector = std::make_shared<Selector>(QRect(event->pos().x(),event->pos().y(),0,0));
                scene()->addItem(selector.get());
                actionType = eActionType::SELECT;
            }
            else if (!selector && scene()->selectedItems().size())
                actionType = eActionType::MOVE;
            break;
        case ToolsManager::eToolType::NODE:

            addNode(event->pos().x(),event->pos().y());
            actionType = eActionType::ADD_NODE;
            break;
        case ToolsManager::eToolType::EDGE:
            for (const auto& node : nodes)
            {
                if (node->contains(event->pos()-node->pos()))
                {
                    sourceNode = node;
                    qInfo("source node id = %d pos = %f:%f",sourceNode->id(),sourceNode->pos().x(),sourceNode->pos().y());
                    break;
                }
            }
            actionType = eActionType::ADD_EDGE;
            break;
        case ToolsManager::eToolType::HAND:
            actionType = eActionType::HAND_MOVE;
            break;
        default:
            break;
        }
        
    }
    else if (event->button() == Qt::MouseButton::MiddleButton)
    {
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    // to prevent out of bounds event while mouse is holding
    int localX = event->x();
    int localY = event->y();
    if (event->x() < 0) localX = 0;
    if (event->x() > rect().width()) localX = rect().width();
    if (event->y() < 0) localY = 0;
    if (event->y() > rect().height()) localY = rect().height();

    switch (actionType)
    {
    case eActionType::NONE:
        break;
    case eActionType::SELECT:
        selector->setRect(
            selector->rect().x(), selector->rect().y(),
            localX - selector->rect().x(),
            localY - selector->rect().y()
        );
        scene()->setSelectionArea(selector->getPath());

        selector->checkNodes();
        break;
    case eActionType::ADD_NODE:
        break;
    case eActionType::ADD_EDGE:
        break;
    case eActionType::HAND_MOVE:
        for (auto& node : scene()->items())
        {
            if (node->type() == (int)eSandboxType::NODE)
                node->moveBy(localX-oldmx,localY-oldmy);
        }
        break;
    case eActionType::MOVE:
        for (auto& node : scene()->selectedItems())
        {
            if (node->type() == (int)eSandboxType::NODE)
                node->moveBy(localX-oldmx,localY-oldmy);
        }
        break;
    }
    oldmx = localX;
    oldmy = localY;
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    switch (actionType)
    {
    case eActionType::NONE:
        break;
    case eActionType::SELECT:
#ifdef DEBUG
        qInfo("release eActionType::SELECT");
        qInfo("remove selector");
#endif
        scene()->removeItem(selector.get());
        selector.reset();
        break;
    case eActionType::ADD_EDGE:
        for (const auto& node : nodes)
        {
            if (node->contains(event->pos()-node->pos()))
            {
                destNode = node;
                qInfo("dest node id = %d pos = %f:%f",destNode->id(),destNode->pos().x(),destNode->pos().y());
                
                int radius = CONST["Node"]["radius"];
                auto dPos = destNode->pos()+QPointF(radius,radius);
                auto sPos = sourceNode->pos()+QPointF(radius,radius);
                int w = CONST["Edge"]["InputBox"]["w"];
                int h = CONST["Edge"]["InputBox"]["h"];
                auto rect = QRect((dPos.x()+sPos.x())/2,(dPos.y()+sPos.y())/2,w,h);
                textEdit = std::make_shared<TextBox>(rect,QString(),false,this);
                actionType = eActionType::WAIT_EDGE_NAME;
                return;
            }
        }
        break;
    case eActionType::HAND_MOVE:
        break;
    case eActionType::MOVE:
        break;
    }

    QGraphicsView::mouseReleaseEvent(event);
    if (actionType != eActionType::WAIT_EDGE_NAME)
        actionType = eActionType::NONE;
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) //for holding down one button
    {
        return;
    }
    if (event->key() == Qt::Key_Delete)
    {
        removeObjects();
    }
    if (event->key() == Qt::Key_Q)
    {
        const auto& toolType = ToolsManager::eToolType::SELECT;
        TOOLS->setToolType(toolType);
        if (auto window = dynamic_cast<BaseGraphEditorWindow*>(WINDOWS->getCurWindow()))
            window->getButtonGroup()->toggleButtonGroup((int)toolType);
    }
    if (event->key() == Qt::Key_W)
    {
        const auto& toolType = ToolsManager::eToolType::NODE;
        TOOLS->setToolType(toolType);
        if (auto window = dynamic_cast<BaseGraphEditorWindow*>(WINDOWS->getCurWindow()))
            window->getButtonGroup()->toggleButtonGroup((int)toolType);
    }
    if (event->key() == Qt::Key_E)
    {
        const auto& toolType = ToolsManager::eToolType::EDGE;
        TOOLS->setToolType(toolType);
        if (auto window = dynamic_cast<BaseGraphEditorWindow*>(WINDOWS->getCurWindow()))
            window->getButtonGroup()->toggleButtonGroup((int)toolType);
    }
    if (event->key() == Qt::Key_R)
    {
        const auto& toolType = ToolsManager::eToolType::HAND;
        TOOLS->setToolType(toolType);
        if (auto window = dynamic_cast<BaseGraphEditorWindow*>(WINDOWS->getCurWindow()))
            window->getButtonGroup()->toggleButtonGroup((int)toolType);
    }
    if (event->key() == Qt::Key_Space)
    {
        qInfo("press space");
        if (auto window = dynamic_cast<BaseGraphEditorWindow*>(WINDOWS->getCurWindow()))
        {
            auto toolbox = window->getButtonGroup();
            if (!toolbox->isHolding())
            {
                qInfo("TOOLBOX !isHolding");
                const auto& toolType = ToolsManager::eToolType::HAND;
                TOOLS->setToolType(toolType);
                toolbox->toggleButtonGroup((int)toolType);
                toolbox->setHolding(true);
            }
        }
    }
    if (event->key() == Qt::Key_D)
    {
        SIMULATE->startFastRun();
    }
    if (event->key() == Qt::Key_F)
    {
        qInfo("F");
        tryMakeFinal();
    }
    if (event->key() == Qt::Key_G)
    {
        qInfo("G");
        tryMakeInitial();
    }
    if (event->key() == Qt::Key_S)
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            qInfo("ctrl+s was called");
            writeToJson();
        }
    }
    if (event->key() == Qt::Key_O)
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            qInfo("ctrl+o was called");
            if (auto casted = dynamic_cast<SandboxWindow*>(WINDOWS->getCurWindow()))
                casted->openGraph();
        }
    }
    if (event->key() == Qt::Key_F2)
    {
        if (auto casted = dynamic_cast<BaseEdge*>(scene()->selectedItems().front()))
            startRenameEdge(casted);
    }
    if (event->key() == Qt::Key_Z)
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            qInfo("ctrl+z was called");
        }
    }
    if (event->key() == Qt::Key_C)
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            qInfo("ctrl+c was called");
        }
    }
    if (event->key() == Qt::Key_V)
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            qInfo("ctrl+v was called");
        }
    }
    if (event->key() == Qt::Key_A)
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            qInfo("ctrl+a was called");
            selectAllObjects();
        }
    }
    QGraphicsView::keyPressEvent(event);
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) //for holding down one button
    {
        return;
    }
    if (event->key() == Qt::Key_Space)
    {
        if (auto window = dynamic_cast<BaseGraphEditorWindow*>(WINDOWS->getCurWindow()))
        {
            auto toolbox = window->getButtonGroup();
            if (toolbox->isHolding())
            {
                const int t = toolbox->getPrevActiveId();
                TOOLS->setToolType((ToolsManager::eToolType)t);
                toolbox->toggleButtonGroup(t);
                toolbox->setHolding(false);
            }
        }
    }
    QGraphicsView::keyReleaseEvent(event);
}

void GraphicsView::onTextChanged(int code)
{
    setEdgeName(code);
}

void GraphicsView::setEdgeName(int code)
{
    auto edgeText = textEdit->toPlainText();

    if (edgeText.isEmpty())
        edgeText = "λ";

    if (code == 0) // add new edge
    {
        qInfo(edgeText.toStdString().c_str());
        addEdge(sourceNode->id(),destNode->id(),edgeText);
    }
    else if (code == 1) // rename existing edge
    {
        if (auto casted = dynamic_cast<BaseEdge*>(renamingEdge))
        {
            casted->setTextContent(edgeText);
        }
    }
    textEdit.reset();
    textEdit = nullptr;
    actionType = eActionType::NONE;
    sourceNode = nullptr;
    destNode = nullptr;
    renamingEdge = nullptr;
    this->setFocus();
}

void GraphicsView::startRenameEdge(BaseEdge* edge)
{
    scene()->clearSelection();
    edge->setSelected(true);

    renamingEdge = edge;
    auto pos = edge->posText();
    int w = CONST["Edge"]["InputBox"]["w"];
    int h = CONST["Edge"]["InputBox"]["h"];
    auto rect = QRect(pos.x()-w/2,pos.y()-h/2,w,h);
    textEdit = std::make_shared<TextBox>(rect,renamingEdge->textContent(),true,this);
    actionType = eActionType::WAIT_EDGE_NAME;
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    auto newSize = event->size();
    scene()->setSceneRect(QRect(0,0,newSize.width(),newSize.height()));
}

void GraphicsView::removeObject(QGraphicsItem* item)
{
    scene()->clearSelection();
    item->setSelected(true);
    removeObjects();
}

void GraphicsView::removeObjects()
{
    qInfo("delete");
    if (scene()->selectedItems().size())
    {
        QList<QGraphicsItem*> edgesToRemove;
        QList<std::shared_ptr<Node>> nodesToRemove;
        QList<QGraphicsItem*> selected = scene()->selectedItems();
        for (const auto& item : selected)
        {
            if (auto node = dynamic_cast<Node*>(item))
            {
                for (auto& edge : node->getEdges())
                {
                    if (edgesToRemove.indexOf(edge) == -1)
                    {
                        edge->remove();
                        edges.removeAll(edge);
                        edgesToRemove.append(edge);
                    }
                }
                for (auto& n : nodes)
                {
                    if (n->id() == node->id())
                    {
                        nodesToRemove.append(n);
                        break;
                    }
                }
            }
            else if (auto edge = dynamic_cast<BaseEdge*>(item))                
            {
                if (edgesToRemove.indexOf(edge) == -1)
                {
                    edge->remove();
                    edges.removeAll(edge);
                    edgesToRemove.append(edge);
                }
            }
        }
        for (const auto& item : edgesToRemove)
        {
            auto edge = dynamic_cast<BaseEdge*>(item);
            qInfo("remove edge %d s = %d d = %d", edge->id(),edge->sourceNode()->id(),edge->destNode()->id());
            delete item;
            qInfo("edge removed");
        }
        for (const auto& item : nodesToRemove)
        {
            auto s = item.use_count();
            qInfo("remove node %d", item->id());
            if (item->isInitial())
            {
                auto ss = initialNode.use_count();
                initialNode.reset();
                s = item.use_count();
                ss = initialNode.use_count();
            }
            const auto& i = nodes.indexOf(item);
            nodes.takeAt(i).reset();
            s = item.use_count();
            qInfo("node removed");
        }
    }
    qInfo("updated nodes size: %lld", nodes.size());
    qInfo("updated edges size: %lld", edges.size());
}

void GraphicsView::tryMakeFinal()
{
    if (scene()->selectedItems().size() > 0)
    {
        for (const auto& item : scene()->selectedItems())
        {
            if (auto casted = dynamic_cast<Node*>(item))
            {
                casted->setFinal(!casted->isFinal());
                qInfo("set to %d", casted->isFinal());
            }
        }
    }
}

void GraphicsView::tryMakeInitial()
{
    if (scene()->selectedItems().size() > 0)
    {
        if (scene()->selectedItems().size() == 1)
        {
            const auto item = scene()->selectedItems().front();
            if (auto casted = dynamic_cast<Node*>(item))
            {
                makeInitial(casted);
            }
        }
        else
        {
            Node* casted;
            int initialNodeCount = 0;
            for (const auto& item : scene()->selectedItems())
            {
                if (casted = dynamic_cast<Node*>(item))
                {
                    initialNodeCount++;
                }
            }
            if (initialNodeCount == 1)
            {
                makeInitial(casted);
            }
        }
    }
}

void GraphicsView::makeInitial(Node* item)
{
    if (initialNode)
    {
        bool itemIsInit = item->isInitial();
        initialNode->setInitial(false);
        int radius = CONST["Node"]["radius"];
        update(initialNode->centeredPos().x()-radius*2,
            initialNode->centeredPos().y()-radius*2,
            radius*4,radius*4);
        if (itemIsInit)
            return;
    }
    for (const auto& node : nodes)
    {
        if (node->id() == item->id())
            initialNode = node;
    }
    initialNode->setInitial(true);
}

#include "src/Automata/FSA/FSAAutomata.h"
#include "src/Automata/FSA/FSAConfiguration.h"
#include "src/Automata/FSA/FSATransition.h"
#include "src/Automata/State.h"
#include "src/Automata/Actions/FastRun.h"
#include "src/Automata/Actions/MultipleRun.h"
#include "src/Automata/FSA/FSAStepByStepSimulator.h"

void GraphicsView::startSimulateAction(QList<QString> inputs)
{
    auto automata = convertToFSA();

    if (inputs.isEmpty())
    {
        auto fr = AA::Actions::FastRun(automata);
        fr.preHandle();
    }
    else
    {
        auto ml = AA::Actions::MultipleRun(automata, inputs);
        ml.preHandle();
    }
}

AA::Automata* GraphicsView::convertToFSA()
{
    auto automata = new FSA::Automata();
    auto states = QList<AA::State*>();
    auto transitions = QList<FSA::Transition*>();

    for (const auto& node : nodes)
    {
        auto state = automata->createState(node->pos(),node->id());
        if (node->isInitial())
            automata->setInitialState(state);
        if (node->isFinal())
            automata->addFinalState(state);
    }
    for (const auto& edge : edges)
    {
        auto findState = [&](const int& id)->AA::State*{
            for (const auto& state : states)
                if (state->getId() == id)
                    return state;
            return nullptr;
        };
        auto transition = new FSA::Transition(
            automata->getStateById(edge->sourceNode()->id()),
            automata->getStateById(edge->destNode()->id()),
            edge->textContent());
        automata->addTransition(transition);
    }
    return automata;
}

void GraphicsView::selectAllObjects()
{
    scene()->clearSelection();
    QPainterPath path;
    path.moveTo(0,0);
    path.lineTo(width(),0);
    path.lineTo(width(),height());
    path.lineTo(0,height());
    path.lineTo(0,0);
    scene()->setSelectionArea(path);
}
