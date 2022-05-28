#pragma once
#include <QCheckBox>
#include <QToolButton>
#include <QPoint>
#include <QRegion>

class ToggleButton : public QToolButton
{
public:
    ToggleButton(QRect rect, QIcon icon = QIcon(), QWidget *parent = nullptr);
    virtual ~ToggleButton();
};