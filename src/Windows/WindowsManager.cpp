#include "src/Windows/WindowsManager.h"

#include "src/Windows/SandboxWindow/SandboxWindow.h"
#include "src/Windows/TitleWindow/TitleWindow.h"

WindowsManager* WindowsManager::instance = nullptr;

WindowsManager* WindowsManager::getInstance()
{
	if (!instance)
	{
        qInfo("new WM instance");
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
    qInfo("~WindowsManager finished");
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
    else
        qInfo("error");
}

std::shared_ptr<SandboxWindow> WindowsManager::createSandboxWindow()
{
    std::shared_ptr<SandboxWindow> window = std::make_shared<SandboxWindow>();
    window->show();
    return window;
}

std::shared_ptr<TitleWindow> WindowsManager::createTitleWindow()
{
    std::shared_ptr<TitleWindow> window = std::make_shared<TitleWindow>();
    window->show();
    return window;
}