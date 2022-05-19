#pragma once
#include <QButtonGroup>

#define TOOLBOX ToolButtonGroup::getInstance()

class QWidget;
class ToolButtonGroup : public QButtonGroup
{
public:
    static ToolButtonGroup* getInstance(QWidget* widgetParent = nullptr);
    static void cleanup();
    ToolButtonGroup(QWidget* widgetParent = nullptr);
    ~ToolButtonGroup();
    void toggleButtonGroup(int buttonId);
    void setHolding(bool holding);
    int getPrevActiveId() const;
    bool isHolding() const;
private:
    static ToolButtonGroup* instance;
    int currentActiveId;
    int prevActiveId;
    bool holding;

private slots:
    void reactToToggled(QAbstractButton *button, bool checked);

};