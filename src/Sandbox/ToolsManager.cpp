#include "ToolsManager.h"

ToolsManager* ToolsManager::instance = nullptr;

ToolsManager* ToolsManager::getInstance()
{
	if (!instance)
	{
        instance = new ToolsManager();
    }
	return instance;
}

void ToolsManager::cleanup()
{
	delete instance;
	instance = nullptr;
}

ToolsManager::ToolsManager()
{
	type = eToolType::NONE;
}

ToolsManager::~ToolsManager()
{
}

void ToolsManager::setToolType(eToolType type)
{
	this->type = type;
}

ToolsManager::eToolType ToolsManager::tool() const
{
	return type;
}


