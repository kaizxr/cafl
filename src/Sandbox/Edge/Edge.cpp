#include "Edge.h"
#include "src/Utils/Constants.h"
#include "src/Sandbox/Node.h"
#include "src/Sandbox/GraphicsView.h"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>

Edge::Edge(int id, Node *sourceNode, Node *destNode, QString text)
    : BaseEdge(id, sourceNode, destNode, text)
{
    objectType = eSandboxType::EDGE;

    beforeLine.setPoints(source->centeredPos(), dest->centeredPos());
    QLineF line1(source->centeredPos(), dest->centeredPos());
    line1.setLength(line1.length() / 2);
    QLineF line2(line1.p2(), line1.p1());
    QLineF line3 = line2.normalVector();
    int countCopy = 0;
    foreach (auto e, source->getEdges()) {
        if (e->destNode() == dest) {
            countCopy++;
        }
    }
    line3.setLength(pow(-1, countCopy) * countCopy * 20);
    bezier.setX(line3.p2().x());
    bezier.setY(line3.p2().y());
    adjust();
}

Edge::Edge(const QJsonObject &json)
    : BaseEdge()
{
    adjust();
}

QPointF Edge::posText() const
{
    QPointF textPoint;
    int radius = CONST["Node"]["radius"];
    int textOffset = CONST["Edge"]["textOffset"];
    if(source != dest) {
        QPainterPath path = pathBezierCurve();
        textPoint = path.pointAtPercent(0.5);
        qreal angle = getAngleAtMiddle(path);
        qreal dx = textOffset * sin(angle * M_PI / 180);
        qreal dy = -textOffset * cos(angle * M_PI / 180);
        textPoint += QPointF(dx,dy);
    } else {
        textPoint = QPointF(boundingRect().center().x() - radius / 2, boundingRect().center().y());
    }
    return textPoint;
}

QPainterPath Edge::pathBezierCurve() const {
    QPainterPath path;
    path.moveTo(mapFromScene(source->centeredPos()));
    QPointF newBezier = newPosBezier();
    path.quadTo(newBezier,mapFromScene(dest->centeredPos()));
    return path;
}

QPainterPath Edge::shape() const {
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    if (source != dest) {
        if (!isSelected()) {
            path = pathBezierCurve().united(pathText());
        } else {
            path = pathPoint(newPosBezier());
        }
    } else {
        int radius = CONST["Node"]["radius"];
        path.addEllipse(source->centeredPos() + QPointF(radius, -radius),
                        radius + 2, radius + 2);
    }
    return path;
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();
    if (source != dest) {
        QPainterPath path = pathBezierCurve();
        QPolygonF pText;
        QPointF textPoint = posText();
        int w = fm.boundingRect(text).width();
        int h = fm.boundingRect(text).height();
        qreal x = textPoint.x() - w/2;
        qreal y = textPoint.y();
        qreal angle = -getAngleAtMiddle(pathBezierCurve());
        qreal sinA = sin(angle * M_PI / 180);
        qreal cosA = cos(angle * M_PI / 180);
        QPointF a(x,y);
        QPointF b(x-h*sinA,y-h*cosA);
        QPointF c(b.x()+w*cosA,b.y()-h*sinA);
        QPointF d(x+w*cosA,y-h*sinA);
        pText << a << b << c << d;
        QPolygonF pBezier;
        pBezier << bezier + QPointF(-1, -1)
                << bezier + QPointF(2, 0)
                << bezier + QPointF(0, 2)
                << bezier + QPointF(-2, 0);
        return path.boundingRect()
                .united(pText.boundingRect())
                .united(pathPoint(newPosBezier()).boundingRect());
    }
    return shape().boundingRect();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!source || !dest)
        return;
    QTransform reset = painter->transform();
    double angle;
    int radius = CONST["Node"]["radius"];
    QPointF arrowPos;
    QPainterPath myPath;
    painter->setPen(QPen((isSelected() ? Qt::cyan: Qt::black), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPointF bezierPaint = newPosBezier();
    QLineF line(bezierPaint, mapFromScene(dest->centeredPos()));
    if (source != dest) {
        myPath.moveTo(mapFromScene(source->centeredPos()));
        QPointF bezierPaint = newPosBezier();
        myPath.quadTo(bezierPaint,mapFromScene(dest->centeredPos()));
        painter->drawPath(myPath);

        line.setLength(line.length() - radius);
        if (qFuzzyCompare(line.length(), qreal(0.)))
            return;
        angle = myPath.angleAtPercent(myPath.percentAtLength(myPath.length()-radius-10));
        arrowPos = myPath.pointAtPercent(myPath.percentAtLength(myPath.length()-radius));
    } else {
        painter->drawArc(static_cast<int>(source->centeredPos().x()),
                         static_cast<int>(source->centeredPos().y()) - 2 * radius,
                         2 * radius,
                         2 * radius,
                         16 * 180, 16 * -270);
        angle = 1.07 * M_PI;
        painter->setBrush((option->state & QStyle::State_Selected ? Qt::cyan: Qt::black));
        arrowPos = dest->centeredPos() + QPointF(radius, 0);
    }
    painter->setBrush((isSelected() ? Qt::cyan: Qt::black));
    painter->setPen(QPen((isSelected() ? Qt::cyan: Qt::black), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPolygon(arrowPolygon(arrowPos, angle));
    painter->setFont(font);
    drawText(painter,myPath,text);
    painter->setTransform(reset);

    if (isSelected()) {
        int pointSize = CONST["Edge"]["pointSize"];
        painter->drawEllipse(bezierPaint, pointSize - 1, pointSize - 1);
    }
    SandboxObject::paint(painter, option, widget);
}

void Edge::drawText(QPainter *painter, QPainterPath path, QString text)
{
    QPointF textPoint = mapToScene(path.pointAtPercent(0.5));
    // qreal d = (textPoint.x() - source->x()) * (dest->y() - source->y())
    //      - (textPoint.y() - source->y()) * (dest->x() - source->x());
    QPointF temp = path.pointAtPercent(path.percentAtLength(CONST["Node"]["radius"]));
    
    qreal angle = getAngleAtMiddle(path);
    QTransform trans;
    trans.translate(textPoint.x(),textPoint.y());
    trans.rotate(angle);
    trans.translate(-textPoint.x(),-textPoint.y());
    int textOffset = CONST["Edge"]["textOffset"];
    trans.translate(0,-textOffset);
    // if (d >= 0)
    //     trans.translate(0,-textOffset);
    // else
    //     trans.translate(0,textOffset);

    painter->setTransform(trans);
    painter->drawText(textPoint.x()-fm.boundingRect(text).width()/2,textPoint.y(),text);
}

QPointF Edge::newPosBezier() const
{
        QLineF line1(mapFromScene(source->centeredPos()), mapFromScene(dest->centeredPos()));
        QLineF beforeBezier(beforeLine.p1(), bezier);
        QLineF line2 = line1;
        line2.setAngle(line1.angle() - (beforeLine.angle() - beforeBezier.angle()));
        line2.setLength(line1.length() / beforeLine.length() * beforeBezier.length());
        return line2.p2();
}

QVariant Edge::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionChange:
        bezier = newPosBezier();
        break;
    case ItemPositionHasChanged:
        beforeLine.setPoints(mapFromScene(source->centeredPos()), mapFromScene(dest->centeredPos()));
        adjust();
        break;
    default:
        break;
    };
    return QGraphicsItem::itemChange(change, value);
}

QPainterPath Edge::pathText() const {
    QPainterPath path;
    QPointF textPoint = posText();
    int w = fm.boundingRect(text).width();
    int h = fm.boundingRect(text).height();
    qreal x = textPoint.x() - w/2;
    qreal y = textPoint.y();
    qreal angle = -getAngleAtMiddle(pathBezierCurve());
    qreal sinA = sin(angle * M_PI / 180);
    qreal cosA = cos(angle * M_PI / 180);
    QPointF a(x,y);
    QPointF b(x-h*sinA,y-h*cosA);
    QPointF c(b.x()+w*cosA,b.y()-h*sinA);
    QPointF d(x+w*cosA,y-h*sinA);
    path.moveTo(a);
    path.lineTo(b);
    path.lineTo(c);
    path.lineTo(d);
    path.lineTo(a);
    return path;
}

qreal Edge::getAngleAtMiddle(QPainterPath path) const
{
    qreal angle = -path.angleAtPercent(0.5);
    if (source->pos().x() >= dest->pos().x())
        angle += 180;
    return angle;
}
