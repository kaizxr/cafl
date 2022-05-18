#include "ToggleButton.h"
#include <QPainter>

ToggleButton::ToggleButton(QRect rect, QWidget *parent) : QCheckBox(parent)
{
    this->setGeometry(rect);
    this->show();
}

ToggleButton::~ToggleButton()
{
    
}

