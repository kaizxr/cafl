#pragma once
#include <memory>

class GraphicsView;
class ToolButtonGroup;
class BaseGraphEditorWindow
{
public:
    BaseGraphEditorWindow();
    virtual ~BaseGraphEditorWindow();

    GraphicsView* getGraphicsView();
    ToolButtonGroup* getButtonGroup();

protected:
    std::shared_ptr<GraphicsView> graphicsView;
    std::shared_ptr<ToolButtonGroup> buttonGroup;
};