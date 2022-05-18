#include <QGraphicsItem>
#include "src/Sandbox/SandboxObject.h"

class Node;
class BaseEdge : public SandboxObject
{
protected:
    BaseEdge(int id, Node *sourceNode, Node *destNode = nullptr, QString text = nullptr);
    BaseEdge();
public:
    virtual ~BaseEdge() override;
    void setTextContent(QString text) override;
    inline Node *sourceNode() const { return source; }
    inline Node *destNode() const { return dest; }
    void adjust();
    QPainterPath pathPoint(QPointF point) const;
    static BaseEdge *create(const QJsonObject &json);
    void remove();
protected:
    QPolygonF arrowPolygon(QPointF peak, qreal angle) const;
    virtual QPointF posText() const = 0;
    virtual QPainterPath pathText() const = 0;
    
    Node *source, *dest;
    qreal arrowSize;
    static int _idStatic;
};
