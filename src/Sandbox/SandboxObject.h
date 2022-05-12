#pragma once
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

enum class eSandboxType
{
    NONE = -1,
    NODE,
    EDGE,
    CYCLE_EDGE
};

class SandboxObject : public QGraphicsItem
{
public:
    SandboxObject(int id, QString text = nullptr);
    int type() const override { return static_cast<int>(objectType); }
    int id() const;
    virtual void setTextContent(QString text);
    virtual QString textContent() const { return text; }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
protected:

    QString text;
    eSandboxType objectType;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int objectId;
    QRectF enoughBoundingRect(QRectF rect) const;
};