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
    qInfo("Edge(%d,%d,%d)",id,sourceNode->id(),destNode->id());
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
    if(source != dest) {
        QPointF bezierNew = newPosBezier();
        QLineF line1(bezierNew, mapFromScene(dest->centeredPos())), line2;
        line1.setLength(line1.length() - radius);
        qreal anglRad = line1.angle() * M_PI / 180;
        qreal widthText, hightText;
        widthText = 8 * text.size();
        hightText = 14;
        qreal lenLine1 = line1.length();
        if (line1.angle() > 0 && line1.angle() <= 90) {
            line1.setLength(line1.length() - (widthText * cos(anglRad) + hightText * sin(anglRad)));
            if (lenLine1 > (widthText * cos(anglRad) + hightText * sin(anglRad))) {
                line2.setPoints(line1.p2(), line1.p1());
            } else {
                line2.setPoints(line1.p1(), line1.p2());
            }
            QLineF line3 = line2.normalVector();
            line3.setLength(10 * sin(anglRad) + (hightText + 10) * cos(anglRad));
            textPoint = line3.p2();
        } else if (line1.angle() > 90 && line1.angle() <= 180) {
            line1.setLength(line1.length() - (5 * -cos(anglRad) + hightText * sin(anglRad)));
            if (lenLine1 > (5 * -cos(anglRad) + hightText * sin(anglRad))) {
                line2.setPoints(line1.p2(), line1.p1());
            } else {
                line2.setPoints(line1.p1(), line1.p2());
            }
            QLineF line3 = line2.normalVector();
            line3.setLength(10 * -cos(anglRad) + 10 * sin(anglRad));
            textPoint = line3.p2();
        } else if (line1.angle() > 180 && line1.angle() <= 270) {
            QLineF line11(line1.p2(), bezierNew);
            line11.setLength(5);
            line2.setPoints(line11.p2(), line11.p1());
            QLineF line3 = line2.normalVector();
            line3.setLength(hightText * -cos(anglRad) + 5 * -sin(anglRad));
            textPoint = line3.p2();
        } else {
            QLineF line11(line1.p2(), bezierNew);
            line11.setLength(5 * -sin(anglRad) + widthText * cos(anglRad));
            line2.setPoints(line11.p2(), line11.p1());
            QLineF line3 = line2.normalVector();
            line3.setLength(5.0);
            textPoint = line3.p2();
        }
    } else {
        textPoint = QPointF(boundingRect().center().x() - radius / 2, boundingRect().center().y());
    }
    return textPoint;
}

QPainterPath Edge::pathBezierCurve() const {
    QPainterPath path;
    qreal qOffset = 5;
    QPointF newBezier = newPosBezier();
    QLineF line0(mapFromScene(source->centeredPos()), newBezier);
    QLineF line1(newBezier, mapFromScene(dest->centeredPos()));
    qreal dx0 = qOffset * sin(line0.angle() * M_PI / 180);
    qreal dy0 = qOffset * cos(line0.angle() * M_PI / 180);
    qreal dx1 = qOffset * sin(line1.angle() * M_PI / 180);
    qreal dy1 = qOffset * cos(line1.angle() * M_PI / 180);
    QPointF offset0(dx0, dy0);
    QPointF offset1(dx1, dy1);
    path.moveTo(mapFromScene(source->centeredPos() + offset0));
    path.cubicTo(newBezier + (offset0 + offset1) / 2,
                 newBezier + (offset0 + offset1) / 2,
                 mapFromScene(dest->centeredPos()) + offset1);
    path.lineTo(mapFromScene(dest->centeredPos()) - offset1);
    path.cubicTo(newBezier - (offset0 + offset1) / 2,
                 newBezier - (offset0 + offset1) / 2,
                 mapFromScene(source->centeredPos()) - offset0);
    path.lineTo(mapFromScene(source->centeredPos()) + offset0);
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
        QPolygonF pText;
        QPointF textPoint = posText();
        qreal x = textPoint.x();
        qreal y = textPoint.y();
        pText << QPointF(x, y)
              << QPointF(x, y - 18)
              << QPointF(x + 8 * text.size(), y - 18)
              << QPointF(x + 8 * text.size(), y + 4)
              << QPointF(x, y + 4);
        QPolygonF pBezier;
        pBezier << bezier + QPointF(-1, -1)
                << bezier + QPointF(2, 0)
                << bezier + QPointF(0, 2)
                << bezier + QPointF(-2, 0);
        return pathBezierCurve().boundingRect()
                .united(pText.boundingRect())
                .united(pathPoint(newPosBezier()).boundingRect());
    }
    return shape().boundingRect();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!source || !dest)
        return;
    double angle;
    int radius = CONST["Node"]["radius"];
    QPointF peak, destArrowP1, destArrowP2;
    painter->setPen(QPen((isSelected() ? Qt::cyan: Qt::black), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPointF bezierPaint = newPosBezier();
    QLineF line(bezierPaint, mapFromScene(dest->centeredPos()));
    if (source != dest) {
        QPainterPath myPath;
        myPath.moveTo(mapFromScene(source->centeredPos()));
        QPointF bezierPaint = newPosBezier();
        myPath.cubicTo(bezierPaint, bezierPaint, mapFromScene(dest->centeredPos()));

        painter->drawPath(myPath);
        line.setLength(line.length() - radius);
        if (qFuzzyCompare(line.length(), qreal(0.)))
            return;

        angle = std::atan2(-line.dy(), line.dx());

        destArrowP1 = line.p2() + QPointF(sin(angle - M_PI / 1.8) * qMin(arrowSize, line.length()),
                                                  cos(angle - M_PI / 1.8) * qMin(arrowSize, line.length()));
        destArrowP2 = line.p2() + QPointF(sin(angle - M_PI + M_PI / 1.8) * qMin(arrowSize, line.length()),
                                                  cos(angle - M_PI + M_PI / 1.8) * qMin(arrowSize, line.length()));
        peak = line.p2();
    } else {
        painter->drawArc(static_cast<int>(source->centeredPos().x()),
                         static_cast<int>(source->centeredPos().y()) - 2 * radius,
                         2 * radius,
                         2 * radius,
                         16 * 180, 16 * -270);
        angle = 1.07 * M_PI;
        destArrowP1 = dest->centeredPos()+ QPointF(sin(angle - M_PI / 1.8) * arrowSize + radius,
                                                 cos(angle - M_PI / 1.8) * arrowSize);
        destArrowP2 = dest->centeredPos() + QPointF(sin(angle - M_PI + M_PI / 1.8) * arrowSize + radius,
                                                 cos(angle - M_PI + M_PI / 1.8) * arrowSize);
        painter->setBrush((option->state & QStyle::State_Selected ? Qt::cyan: Qt::black));
        peak = dest->centeredPos() + QPointF(radius, 0);

    }
    painter->setBrush((isSelected() ? Qt::cyan: Qt::black));
    painter->setPen(QPen((isSelected() ? Qt::cyan: Qt::black), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPolygon(arrowPolygon(peak, line.angle()));
    painter->setFont(QFont("Times", 11));
    painter->drawText(posText(), text);
    if (isSelected()) {
        int pointSize = CONST["Edge"]["pointSize"];
        painter->drawEllipse(bezierPaint, pointSize - 1, pointSize - 1);
    }
    SandboxObject::paint(painter, option, widget);
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