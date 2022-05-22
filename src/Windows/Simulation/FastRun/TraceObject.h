#pragma once
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>

namespace AA
{
    class Configuration;
}

namespace Window
{
    namespace Simulation
    {
        namespace FastRun
        {
            class TraceObject : public QGraphicsItem
            {
            public:
                TraceObject(AA::Configuration* conf, QWidget* parent = nullptr);
                TraceObject(AA::Configuration* conf, QPoint pos, QWidget* parent = nullptr);
                ~TraceObject();

                QRectF boundingRect() const override;
                void setInput(QString input);
            protected:
                void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

                std::shared_ptr<QGraphicsEllipseItem> state;
                std::shared_ptr<QGraphicsTextItem> inputLabel;
                std::shared_ptr<QGraphicsRectItem> inputRect;
                std::shared_ptr<QGraphicsPolygonItem> initialSign;
                std::shared_ptr<QGraphicsPolygonItem> parentArrow;
            };
        }
    }
}