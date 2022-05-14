#include "src/Sandbox/SandboxObject.h"
#include "src/Sandbox/GraphicsView.h"
#include "src/Utils/Constants.h"
#include <QPainter>

class GraphicsView;

SandboxObject::SandboxObject(int id, QString text)
    : text(text), objectId(id)
{
    objectType = eSandboxType::NONE;
    if (text.isEmpty()) {
        this->text = QString("%1").arg(objectId);
    } else {
        this->text = text;
    }
}

int SandboxObject::id() const
{
    return objectId;
}

void SandboxObject::setTextContent(QString text) {
    this->text = text;
    update();
}

void SandboxObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void SandboxObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF SandboxObject::enoughBoundingRect(QRectF rect) const
{
    const qreal enough = CONST["Sandbox"]["enough"];
    rect.moveCenter(rect.center() - QPointF(enough, enough));
    rect.setSize(rect.size() + QSizeF(2 * enough, 2 * enough));
    return rect;
}
