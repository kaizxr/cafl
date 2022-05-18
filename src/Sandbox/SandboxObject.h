#pragma once
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QFont>
#include <QFontMetrics>

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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF enoughBoundingRect(QRectF rect) const;

    QFont font;
    QFontMetrics fm;
    QString text;
    eSandboxType objectType;
    int objectId;
};
