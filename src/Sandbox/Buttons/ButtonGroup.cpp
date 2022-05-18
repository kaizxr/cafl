#include "ButtonGroup.h"
#include "ToggleButton.h"
#include "src/Sandbox/ToolsManager.h"

ButtonGroup::ButtonGroup(QWidget* widgetParent) : QButtonGroup(widgetParent)
{
    addButton(new ToggleButton(QRect(8,8,32,32),widgetParent),0); // select tool
    addButton(new ToggleButton(QRect(48,8,32,32),widgetParent),1); // addNode tool
    addButton(new ToggleButton(QRect(88,8,32,32),widgetParent),2); // addEdge tool
    connect(this,&QButtonGroup::buttonToggled,this,&ButtonGroup::reactToToggled);
    button(0)->setChecked(true);
}

ButtonGroup::~ButtonGroup()
{

}

void ButtonGroup::reactToToggled(QAbstractButton *button, bool checked)
{
    qInfo("button %d is toggled to %d",id(button),checked);
    int tId = id(button);
    switch (tId)
    {
    case 0:
        TOOLS->setToolType(ToolsManager::eToolType::SELECT);
        break;
    case 1:
        TOOLS->setToolType(ToolsManager::eToolType::NODE);
        break;
    case 2:
        TOOLS->setToolType(ToolsManager::eToolType::EDGE);
        break;
    default:
        break;
    }
}
