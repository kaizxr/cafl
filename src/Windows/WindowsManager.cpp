#include "src/Windows/WindowsManager.h"

#include "src/Windows/SandboxWindow/SandboxWindow.h"
#include "src/Windows/TitleWindow/TitleWindow.h"

WindowsManager* WindowsManager::instance = nullptr;

WindowsManager* WindowsManager::getInstance()
{
	if (!instance)
	{
        instance = new WindowsManager();
    }
	return instance;
}

void WindowsManager::cleanup()
{
	delete instance;
	instance = nullptr;
}

WindowsManager::WindowsManager()
{
    curWindow = nullptr;
}

WindowsManager::~WindowsManager()
{
#ifdef DEBUG
    qInfo("~WindowsManager finished");
#endif
}

void WindowsManager::changeWindow(std::string windowType)
{
    if (curWindow)
    {
        curWindow->close();
        curWindow.reset();
        curWindow = nullptr;
    }

    if (windowType == "sandbox")
        curWindow = createSandboxWindow();
    else if (windowType == "title")
        curWindow = createTitleWindow();
#ifdef DEBUG
    else
        qInfo("error");
#endif
}

std::shared_ptr<SandboxWindow> WindowsManager::createSandboxWindow()
{
    std::shared_ptr<SandboxWindow> window = std::make_shared<SandboxWindow>();
    window->show();
    window->initUI();
    return window;
}

std::shared_ptr<TitleWindow> WindowsManager::createTitleWindow()
{
    std::shared_ptr<TitleWindow> window = std::make_shared<TitleWindow>();
    window->show();
    return window;
}