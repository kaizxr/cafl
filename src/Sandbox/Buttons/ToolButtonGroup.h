#pragma once
#include <QButtonGroup>

class QWidget;
class ToolButtonGroup : public QButtonGroup
{
public:
    ToolButtonGroup(QWidget* widgetParent = nullptr);
    ~ToolButtonGroup();
    void toggleButtonGroup(int buttonId);
    void setHolding(bool holding);
    int getPrevActiveId() const;
    bool isHolding() const;
private:
    int currentActiveId;
    int prevActiveId;
    bool holding;

private slots:
    void reactToToggled(QAbstractButton *button, bool checked);
};