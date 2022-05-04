#include "Node.h"

#include "src/Utils/Utils.h"
#include <QBrush>

Node::Node(qreal x, qreal y, qreal radius, QGraphicsItem* parent) : QGraphicsEllipseItem(0,0,radius,radius,parent)
{
    // std::string temp;
    // qInfo("Node constructor");
    // temp = strFormat("xy = %f:%f\n ", x, y);
    // qInfo(temp.c_str());
    setPos(x, y);
    // temp = strFormat("pos = %f:%f\n ", this->pos().x(), this->pos().y());
    // qInfo(temp.c_str());
    setBrush(Qt::blue);
    setAcceptHoverEvents(true);
}

Node::~Node()
{

}
