#pragma once
#include <QButtonGroup>

class ButtonGroup : public QButtonGroup
{
public:
    ButtonGroup(QWidget* widgetParent = nullptr);
    ~ButtonGroup();
private slots:
    void reactToToggled(QAbstractButton *button, bool checked);
};