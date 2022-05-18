#include "ToolButtonGroup.h"
#include "ToggleButton.h"
#include "src/Sandbox/ToolsManager.h"
#include <QWidget>

ToolButtonGroup* ToolButtonGroup::instance = nullptr;

ToolButtonGroup* ToolButtonGroup::getInstance(QWidget* widgetParent)
{
	if (!instance)
	{
        instance = new ToolButtonGroup(widgetParent);
    }
	return instance;
}

void ToolButtonGroup::cleanup()
{
	delete instance;
	instance = nullptr;
}

ToolButtonGroup::ToolButtonGroup(QWidget* widgetParent) : QButtonGroup(widgetParent)
{
    addButton(new ToggleButton(QRect(8,8,32,32),widgetParent),0); // select tool
    addButton(new ToggleButton(QRect(48,8,32,32),widgetParent),1); // addNode tool
    addButton(new ToggleButton(QRect(88,8,32,32),widgetParent),2); // addEdge tool
    addButton(new ToggleButton(QRect(128,8,32,32),widgetParent),3); // hand tool
    connect(this,&QButtonGroup::buttonToggled,this,&ToolButtonGroup::reactToToggled);
    button(0)->setChecked(true);
}

ToolButtonGroup::~ToolButtonGroup()
{

}

int ToolButtonGroup::getCurrentActiveId()
{
    return currentActiveId;
}


void ToolButtonGroup::reactToToggled(QAbstractButton *button, bool checked)
{
    qInfo("button %d is toggled to %d",id(button),checked);
    int tId = id(button);
    currentActiveId = tId;
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
    case 3:
        TOOLS->setToolType(ToolsManager::eToolType::HAND);
        break;
    default:
        break;
    }
}
