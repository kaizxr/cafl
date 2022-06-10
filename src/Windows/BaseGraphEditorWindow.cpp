#include "BaseGraphEditorWindow.h"
#include "src/Sandbox/GraphicsView.h"
#include "src/Sandbox/Buttons/ToolButtonGroup.h"

BaseGraphEditorWindow::BaseGraphEditorWindow()
{
}

BaseGraphEditorWindow::~BaseGraphEditorWindow()
{
}

GraphicsView* BaseGraphEditorWindow::getGraphicsView()
{
    return graphicsView.get();
}

ToolButtonGroup* BaseGraphEditorWindow::getButtonGroup()
{
    return buttonGroup.get();
}
