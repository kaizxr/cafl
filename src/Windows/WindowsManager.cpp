#include "src/Windows/WindowsManager.h"

#include "src/Windows/SandboxWindow/SandboxWindow.h"
#include "src/Windows/PlaygroundWindow/PlaygroundWindow.h"
#include "src/Windows/TitleWindow/TitleWindow.h"
#include "src/Windows/TaskConstructorWindow/SimpleTaskCreator.h"
#include "src/Windows/Simulation/Output.h"

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
    else if (windowType == "playground")
        curWindow = createPlaygroundWindow();
    else if (windowType == "title")
        curWindow = createTitleWindow();
    else if (windowType == "taskConstructor")
        curWindow = createSimpleTaskCreator();
    else if (windowType == "output")
        curWindow = createOutputWindow();
#ifdef DEBUG
    else
        qInfo("error");
#endif
}

QWidget* WindowsManager::getCurWindow()
{
    return curWindow.get();
}

std::shared_ptr<SandboxWindow> WindowsManager::createSandboxWindow()
{
    std::shared_ptr<SandboxWindow> window = std::make_shared<SandboxWindow>();
    window->show();
    window->initUI();
    return window;
}

std::shared_ptr<PlaygroundWindow> WindowsManager::createPlaygroundWindow()
{
    std::shared_ptr<PlaygroundWindow> window = std::make_shared<PlaygroundWindow>();
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

std::shared_ptr<SimpleTaskCreator> WindowsManager::createSimpleTaskCreator()
{
    std::shared_ptr<SimpleTaskCreator> window = std::make_shared<SimpleTaskCreator>();
    window->show();
    window->initUI();
    return window;
}

std::shared_ptr<Window::Simulation::Output> WindowsManager::createOutputWindow()
{
    std::shared_ptr<Window::Simulation::Output> window = std::make_shared<Window::Simulation::Output>();
    window->show();
    window->initUI();
    return window;
}