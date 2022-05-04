#include "GraphicsView.h"

#include "src/Utils/Utils.h"

GraphicsView::GraphicsView(QRect rect, QWidget* parent) : QGraphicsView(parent)
{
    std::string wh;
    qInfo("GraphicsView constructor");
    this->setScene(new QGraphicsScene());
    this->setSceneRect(rect);
    wh = strFormat("rect = %d:%d:%d:%d\n ", rect.x(), rect.y(), rect.width(), rect.height());
    qInfo(wh.c_str());
    wh = strFormat("scene rect = %f:%f:%f:%f\n ", scene()->sceneRect().x(), scene()->sceneRect().y(), scene()->sceneRect().width(), scene()->sceneRect().height());
    qInfo(wh.c_str());
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::addNode(std::shared_ptr<Node> node)
{
    nodes.push_back(node);
}