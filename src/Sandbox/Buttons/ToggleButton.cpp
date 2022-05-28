#include "ToggleButton.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

ToggleButton::ToggleButton(QRect rect, QIcon icon, QWidget *parent) : QToolButton(parent)
{
    setGeometry(rect);
    setIcon(icon);
    show();
    setCheckable(true);
}

ToggleButton::~ToggleButton()
{
}
