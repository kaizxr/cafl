#include "GraphicsView.h"

#include "src/Utils/Utils.h"
#include "src/Utils/Constants.h"
#include "src/Sandbox/Node.h"
#include "src/Sandbox/Selector.h"

#include <QMouseEvent>

GraphicsView::GraphicsView(QRect rect, QWidget* parent) : QGraphicsView(parent)
{
    qInfo("GraphicsView constructor");
    this->setScene(new QGraphicsScene(this));
    this->setSceneRect(rect);
    qInfo("scene rect = %f:%f:%f:%f\n ", scene()->sceneRect().x(), scene()->sceneRect().y(), scene()->sceneRect().width(), scene()->sceneRect().height());
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::addNode(int x, int y)
{
    int radius = CONST["Node"]["radius"];
    std::shared_ptr<Node> node = std::make_shared<Node>(x,y,radius);
    scene()->addItem(node.get());
    nodes.push_back(node);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    qInfo("x:y %d:%d",x,y);
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        qInfo("add selector");
        selector = std::make_shared<Selector>(QRect(x,y,10,10));
        scene()->addItem(selector.get());
    }
    else if (event->button() == Qt::MouseButton::MiddleButton)
    {
        qInfo("add node");
        addNode(x,y);
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {

    }

    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (selector)
    {
        qInfo("selector move event");
        auto r = selector->rect();
        r.setWidth(event->pos().x() - r.x());
        r.setHeight(event->pos().y() - r.y());
        selector->setRect(r);

        selector->checkNodes(nodes);
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    if (selector)
    {
        qInfo("remove selector");
        scene()->removeItem(selector.get());
        selector.reset();
    }
    QGraphicsView::mouseReleaseEvent(event);
}
