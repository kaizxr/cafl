#include "TraceObject.h"
#include "src/Utils/Constants.h"
#include <QPolygonF>
#include <QPainter>

using namespace Window::Simulation::FastRun;

TraceObject::TraceObject(AA::Configuration* conf, QWidget* parent)
{
    qInfo("START TraceObject constructor");
    int x, y, w, h;
    x = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["State"]["x"];
    y = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["State"]["y"];
    w = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["State"]["radius"];
    qInfo("x,y,w = %d,%d,%d",x,y,w);
    state = std::make_shared<QGraphicsEllipseItem>(x,y,w,w,this);

    x = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["Input"]["x"];
    y = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["Input"]["y"];
    w = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["Input"]["w"];
    h = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["Input"]["h"];
    qInfo("x,y,w,h = %d,%d,%d,%d",x,y,w,h);
    inputRect = std::make_shared<QGraphicsRectItem>(x,y,w,h,this);
    inputLabel = std::make_shared<QGraphicsTextItem>();
    inputLabel->setPos(x+5,y+h-10);

    QPolygonF polygon;
    auto pointsData = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["InitialSign"]["Points"];
    for (auto& p : pointsData)
    {
        x = p["x"];
        y = p["y"];
        qInfo("x,y = %d,%d",x,y);
        polygon.append(QPointF(x,y));
    }
    initialSign = std::make_shared<QGraphicsPolygonItem>(polygon,this);

    polygon.clear();
    pointsData = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["ParentArrow"]["Points"];
    for (auto& p : pointsData)
    {
        x = p["x"];
        y = p["y"];
        qInfo("x,y = %d,%d",x,y);
        polygon.append(QPointF(x,y));
    }
    parentArrow = std::make_shared<QGraphicsPolygonItem>(polygon,this);
    qInfo("END TraceObject constructor");

}

TraceObject::TraceObject(AA::Configuration* conf, QPoint pos, QWidget* parent) : TraceObject(conf, parent)
{
    this->setPos(pos);
}

TraceObject::~TraceObject()
{
}

QRectF TraceObject::boundingRect() const
{
    // TO-DO: CONST
    int w = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["w"];
    int h  = CONST["Window"]["Simulation"]["FastRun"]["TraceObject"]["h"];
    return QRectF(0,0,w,h);
}

void TraceObject::setInput(QString input)
{
    if (inputLabel)
        inputLabel->setPlainText(input);
}

void TraceObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    state->paint(painter,option,widget);
    inputRect->paint(painter,option,widget);
    painter->drawText(inputLabel->pos(),inputLabel->toPlainText());
    if (initialSign)
        initialSign->paint(painter,option,widget);
    parentArrow->paint(painter,option,widget);
}
