#include "ToolButtonGroup.h"
#include "ToggleButton.h"
#include "src/Sandbox/ToolsManager.h"
#include <QApplication>
#include <QWidget>

#include <iostream>

ToolButtonGroup::ToolButtonGroup(QWidget* widgetParent) : QButtonGroup(widgetParent)
{
    auto selectTool = new ToggleButton(QRect(8,8,32,32),QIcon(":/icons/icons/white_select.png"),widgetParent);
    selectTool->setToolTip("Инструмент \"Выбрать\" (Q)");
    selectTool->setStyleSheet("color: #000000;");
    auto nodeTool = new ToggleButton(QRect(48,8,32,32),QIcon(":/icons/icons/white_add_node.png"),widgetParent);
    nodeTool->setToolTip("Добавление вершины (W)");
    nodeTool->setStyleSheet("color: #000000;");
    auto edgeTool = new ToggleButton(QRect(88,8,32,32),QIcon(":/icons/icons/white_add_edge.png"),widgetParent);
    edgeTool->setToolTip("Добавление ребра (E)");
    edgeTool->setStyleSheet("color: #000000;");
    auto handTool = new ToggleButton(QRect(128,8,32,32),QIcon(":/icons/icons/white_hand.png"),widgetParent);
    handTool->setToolTip("Инструмент рука (R/Пробел)");
    handTool->setStyleSheet("color: #000000;");
    addButton(selectTool,0);
    addButton(nodeTool,1);
    addButton(edgeTool,2);
    addButton(handTool,3);

    currentActiveId = 0;
    connect(this,&QButtonGroup::buttonToggled,this,&ToolButtonGroup::reactToToggled);
    button(0)->setChecked(true);
}

ToolButtonGroup::~ToolButtonGroup()
{

}

void ToolButtonGroup::toggleButtonGroup(int buttonId)
{
    qInfo("ButtonToggled");
    qInfo("cur %d is %d",currentActiveId,false);
    qInfo("bId %d is %d",buttonId,true);
    button(currentActiveId)->setChecked(false);
    button(buttonId)->setChecked(true);
}

void ToolButtonGroup::setHolding(bool holding)
{
    this->holding = holding;
}

int ToolButtonGroup::getPrevActiveId() const
{
    return prevActiveId;
}

bool ToolButtonGroup::isHolding() const
{
    return holding;
}

void ToolButtonGroup::reactToToggled(QAbstractButton *button, bool checked)
{
    int tId = id(button);
    QApplication::restoreOverrideCursor();
    prevActiveId = currentActiveId;
    currentActiveId = tId;
    switch (tId)
    {
    case 0:
        if (!checked)
            button->setIcon(QIcon(":/icons/icons/white_select.png"));
        else
            button->setIcon(QIcon(":/icons/icons/selected_select.png"));
        TOOLS->setToolType(ToolsManager::eToolType::SELECT);
        break;
    case 1:
        if (!checked)
            button->setIcon(QIcon(":/icons/icons/white_add_node.png"));
        else
            button->setIcon(QIcon(":/icons/icons/selected_add_node.png"));
        TOOLS->setToolType(ToolsManager::eToolType::NODE);
        break;
    case 2:
        if (!checked)
            button->setIcon(QIcon(":/icons/icons/white_add_edge.png"));
        else
            button->setIcon(QIcon(":/icons/icons/selected_add_edge.png"));
        TOOLS->setToolType(ToolsManager::eToolType::EDGE);
        break;
    case 3:
        if (!checked)
            button->setIcon(QIcon(":/icons/icons/white_hand.png"));
        else
            button->setIcon(QIcon(":/icons/icons/selected_hand.png"));
        QApplication::setOverrideCursor(Qt::OpenHandCursor);
        TOOLS->setToolType(ToolsManager::eToolType::HAND);
        break;
    default:
        break;
    }
}
