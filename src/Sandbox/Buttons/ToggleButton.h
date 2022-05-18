#pragma once
#include <QCheckBox>

class ToggleButton : public QCheckBox
{
public:
    ToggleButton(QRect rect, QWidget *parent = nullptr);
    virtual ~ToggleButton();
};