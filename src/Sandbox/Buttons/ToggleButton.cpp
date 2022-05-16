#include "ToggleButton.h"
#include <QPainter>

ToggleButton::ToggleButton(QRect rect, QWidget *parent) : QCheckBox(parent)
{
    this->setGeometry(rect);
    this->show();
    // connect(this,SIGNAL(QAbstractButton::toggled(bool checked)),this,SLOT(reactToToggle(bool checked)));
}

ToggleButton::~ToggleButton()
{
    
}

// void ToggleButton::paintEvent(QPaintEvent* event)
// {
//     QPainter painter(this);
//     QBrush reset = painter.brush();
//     if (isChecked())
//         painter.setBrush(QBrush(Qt::green));
//     else
//         painter.setBrush(reset);
//     painter.drawRect(rect());
//     // painter.drawRoundedRect(rect(),5,5);
// }

void ToggleButton::reactToToggle(bool checked)
{
    qInfo("%d:%d is toggled %d",x(),y(),checked);
}
