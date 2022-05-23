#include "LoopEdge.h"
#include "src/Utils/Constants.h"
#include "src/Sandbox/Node.h"
#include "src/Sandbox/GraphicsView.h"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>

LoopEdge::LoopEdge(int id, Node *sourceNode, QString text)
    : BaseEdge(id, sourceNode, nullptr, text)
{
    qInfo("started loopedge()");
    objectType = eSandboxType::EDGE;
    angle = 90.f;
    radius = CONST["Edge"]["LoopEdge"]["radius"];
    offset = CONST["Edge"]["LoopEdge"]["offset"];
    adjust();
    qInfo("finished loopedge()");
}

QPointF LoopEdge::peakArrow() const
{
    QPointF p0(getCenterLine().p1());
    QPointF p1 = getCenterPos();
    float L = offset;
    int nodeRadius = CONST["Node"]["radius"];

    qreal a = (nodeRadius * nodeRadius - radius * radius + L * L) / (2 * L);
    qreal h = sqrt(nodeRadius * nodeRadius - a * a);
    QPointF p2   (p0.x() + a * (p1.x() - p0.x()) / L,
                    p0.y() + a * (p1.y() - p0.y()) / L);
    QPointF p3 (p2.x() - h * (p1.y() - p0.y()) / L,
                    p2.y() + h * (p1.x() - p0.x()) / L);
    return p3;
}

QPainterPath LoopEdge::shape() const {
    QPainterPath path1;
    path1.addEllipse(mapFromScene(getCenterPos()),
                        radius + 2, radius + 2);
    QPainterPath path2;
    path2.addEllipse(mapFromScene(getCenterPos()),
                        radius - 2, radius - 2);
    QPainterPath path3 = path1.subtracted(path2);
    return path3.united(pathText());
}

QRectF LoopEdge::boundingRect() const
{
    QRectF rCircle = enoughBoundingRect(shape().boundingRect());
    QRectF rArrow = enoughBoundingRect(arrowPolygon(peakArrow(), getArrowAngle()).boundingRect());
    QRectF rPoint = enoughBoundingRect(pathPoint(handlePos()).boundingRect());
    return rCircle.united(rArrow).united(rPoint);
}

void LoopEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen((isSelected() ? Qt::cyan: Qt::black), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawEllipse(static_cast<int>(mapFromScene(getCenterPos()).x() - radius),
                     static_cast<int>(mapFromScene(getCenterPos()).y() - radius),
                     2 * int(radius),
                     2 * int(radius));
    painter->setBrush((isSelected() ? Qt::cyan: Qt::black));
    if (isSelected()) {
        int pointSize = CONST["Edge"]["pointSize"];
        painter->drawEllipse(handlePos(), pointSize - 1, pointSize - 1);  // размер точки
    }
    painter->setPen(QPen((isSelected() ? Qt::cyan: Qt::black), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPolygon(arrowPolygon(peakArrow(), getArrowAngle()));
    painter->setFont(QFont("Sedoe UI", 16));
    painter->drawText(posText(), text);
}

QPointF LoopEdge::getCenterPos() const
{
    return QPointF(source->centeredPos().x()+offset*cos(angle * M_PI / 180),
                   source->centeredPos().y()-offset*sin(angle * M_PI / 180));
}

QLineF LoopEdge::getCenterLine() const
{
    return QLineF(source->centeredPos(), getCenterPos());
}

QPointF LoopEdge::handlePos() const
{
    return QPointF(mapFromScene(getCenterPos()).x()+radius*cos(angle * M_PI / 180),
                   mapFromScene(getCenterPos()).y()+radius*sin(angle * M_PI / 180));
}

void LoopEdge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // if (event->button() == Qt::MouseButton::LeftButton)
    //     flHandlePress = true;
    // BaseEdge::mousePressEvent(event);
}

void LoopEdge::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // if (flHandlePress) {
    //     QLineF newPosLine(mapFromScene(source->centeredPos()), event->pos());
    //     if (newPosLine.angle() != angle) {
    //         getCenterLine() = newPosLine;
    //         getCenterLine().setLength(offset);
    //         angle = getCenterLine().angle();
    //         getCenterPos() = getCenterLine().p2();
    //     }
    //     update();
    // }
    // else
    //     BaseEdge::mouseMoveEvent(event);
}

void LoopEdge::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // flHandlePress = false;
    // BaseEdge::mouseReleaseEvent(event);
}

float LoopEdge::getArrowAngle() const
{
    QLineF lineToArrow(getCenterPos(),peakArrow());
    return lineToArrow.angle() - 90;
}

QPointF LoopEdge::posText() const
{
    int textOffset = CONST["Edge"]["textOffset"];
    QLineF l1;
    l1.setP1(mapFromScene(getCenterPos()));
    l1.setAngle(angle);
    l1.setLength(radius+textOffset);
    return l1.p2();
}

QPainterPath LoopEdge::pathText() const
{
    QPainterPath path;
    QPointF textPoint = posText();
    int w = fm.boundingRect(text).width();
    int h = fm.boundingRect(text).height();
    qreal x = textPoint.x() - w/2;
    qreal y = textPoint.y();
    QPointF a(x,y);
    QPointF b(x,y-h);
    QPointF c(x+w,y-h);
    QPointF d(x+w,y);
    path.moveTo(a);
    path.lineTo(b);
    path.lineTo(c);
    path.lineTo(d);
    path.lineTo(a);
    return path;
}
QVariant LoopEdge::itemChange(GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsItem::itemChange(change, value);
}