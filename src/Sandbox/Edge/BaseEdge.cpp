#include "Edge.h"
#include "src/Utils/Constants.h"
#include "src/Sandbox/Node.h"

BaseEdge::BaseEdge(int id, Node* sourceNode, Node* destNode, QString text)
    : SandboxObject(id, text),
      source(sourceNode), dest(destNode)
{
    arrowSize = CONST["Edge"]["arrowSize"];
    if (!dest) {
        dest = source;
    }
    source->addEdge(this);
    if (source != dest) {
        dest->addEdge(this);
    }
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

BaseEdge::BaseEdge() : SandboxObject(0)
{
    arrowSize = CONST["Edge"]["arrowSize"];
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

BaseEdge::~BaseEdge()
{
    source->removeEdge(this);
    if (source != dest)
        dest->removeEdge(this);
}

void BaseEdge::setTextContent(QString text)
{
    SandboxObject::setTextContent(text);
    adjust();
}

void BaseEdge::adjust()
{
    if (!source || !dest)
        return;

    prepareGeometryChange();
    if(source != dest) {
        for (auto edg : source->getEdges()) {
            if (edg->sourceNode() == dest) {
                if(objectId > edg->objectId) {
                    edg->adjust();
                }
                break;
            }
        }
    }
}

QPainterPath BaseEdge::pathPoint(QPointF point) const {
    QPainterPath path;
    int pointSize = CONST["Edge"]["pointSize"];
    path.moveTo(point + QPointF(-pointSize, -pointSize));
    path.lineTo(point + QPointF(pointSize, -pointSize));
    path.lineTo(point + QPointF(pointSize, pointSize));
    path.lineTo(point + QPointF(-pointSize, pointSize));
    path.lineTo(point + QPointF(-pointSize, -pointSize));
    return path;
}

BaseEdge *BaseEdge::create(const QJsonObject &json)
{
    // QJsonObject jsonIt = json["Item"].toObject();
    // if (jsonIt["Type"].toInt() == eSandboxType::EDGE) {
    //     return new Edge(json, graphicsView);
    // } else if (jsonIt["Type"].toInt() == eSandboxType::CYCLE_EDGE) {
    //     return new EdgeCircle(json, graphicsView);
    // }
    return nullptr;
}

QPolygonF BaseEdge::arrowPolygon(QPointF peak, qreal angle) const
{
    QPainterPath p;
    QLineF l1, l2;
    l1.setP1(peak);
    l1.setLength(arrowSize);
    l1.setAngle(angle + 180 - 10);
    l2.setP1(peak);
    l2.setLength(arrowSize);
    l2.setAngle(angle + 180 + 10);
    return QPolygonF() << peak << l1.p2() << l2.p2();
}

QPainterPath BaseEdge::pathText() const {
    QPainterPath path;
    QPointF textPoint = posText();
    qreal x = textPoint.x();
    qreal y = textPoint.y();
    path.moveTo(x, y);
    path.lineTo(x, y - 18); // for QFont("Times", 11)
    path.lineTo(x + 8 * text.size(), y - 18);
    path.lineTo(x + 8 * text.size(), y + 4);
    path.lineTo(x, y + 4);
    path.lineTo(x, y);
    return path;
}