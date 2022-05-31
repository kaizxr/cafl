#include "SingletonManager.h"

#include "Constants.h"
#include "Utils.h"
#include "src/Windows/WindowsManager.h"
#include "src/Sandbox/ToolsManager.h"
#include "src/Sandbox/Buttons/ToolButtonGroup.h"
#include "src/Automata/Helpers/SimulateHelper.h"

SingletonManager* SingletonManager::instance = nullptr;

SingletonManager* SingletonManager::getInstance()
{
	if (!instance)
	{
        instance = new SingletonManager();
    }
	return instance;
}

void SingletonManager::cleanup()
{
	delete instance;
	instance = nullptr;
}

SingletonManager::SingletonManager()
{
    curWindow = nullptr;
}

SingletonManager::~SingletonManager()
{
}

void SingletonManager::reload()
{
    Constants::getInstance()->cleanup();
    SIMULATE->cleanup();
    TOOLBOX->cleanup();
    TOOLS->cleanup();
}