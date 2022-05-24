#pragma once
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
    void remove();
    virtual void onTextChanged(int code) override;
    virtual QPointF posText(QPainterPath path = QPainterPath()) const = 0;
protected:
    QPolygonF arrowPolygon(QPointF peak, qreal angle) const;
    virtual QPainterPath pathText() const = 0;
    
    Node *source, *dest;
    qreal arrowSize;
    static int _idStatic;
};
