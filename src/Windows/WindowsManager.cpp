#include "src/Windows/WindowsManager.h"

#include "src/Windows/SandboxWindow/SandboxWindow.h"
#include "src/Windows/PlaygroundWindow/PlaygroundWindow.h"
#include "src/Windows/StartWindow/StartWindow.h"
#include "src/Windows/TaskConstructorWindow/SimpleTaskCreator.h"
#include "src/Windows/Simulation/MultipleInput.h"

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
        curWindow = createStartWindow();
    else if (windowType == "taskConstructor")
        curWindow = createSimpleTaskCreator();
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

std::shared_ptr<StartWindow> WindowsManager::createStartWindow()
{
    std::shared_ptr<StartWindow> window = std::make_shared<StartWindow>();
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

std::shared_ptr<Window::Simulation::MultipleInput> WindowsManager::createMultipleInputWindow()
{
    std::shared_ptr<Window::Simulation::MultipleInput> window = std::make_shared<Window::Simulation::MultipleInput>();
    window->show();
    window->initUI();
    return window;
}
