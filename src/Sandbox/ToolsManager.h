#pragma once

#define TOOLS ToolsManager::getInstance()

class ToolsManager final
{
public:
    enum class eToolType
    {
        NONE = -1,
        SELECT,
        NODE,
        EDGE
    };
    static ToolsManager* getInstance();
    static void cleanup();
    ToolsManager();
    ~ToolsManager();
    void setToolType(eToolType type);
    eToolType tool() const;
    
private:
    eToolType type;
    static ToolsManager* instance;
};
