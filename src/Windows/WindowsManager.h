#pragma once
#include <QWindow>

#define WINDOWS WindowsManager::getInstance()

namespace Window::Simulation
{
    class MultipleInput;
}

class SandboxWindow;
class PlaygroundWindow;
class SimpleTaskCreator;
class StartWindow;
class WindowsManager
{
public:
    static WindowsManager* getInstance();
    static void cleanup();
    WindowsManager();
    ~WindowsManager();
    void changeWindow(std::string windowType = "title");
    QWidget* getCurWindow();

private:
    std::shared_ptr<SandboxWindow> createSandboxWindow();
    std::shared_ptr<PlaygroundWindow> createPlaygroundWindow();
    std::shared_ptr<StartWindow> createStartWindow();
    std::shared_ptr<SimpleTaskCreator> createSimpleTaskCreator();
    std::shared_ptr<Window::Simulation::MultipleInput> createMultipleInputWindow();

    static WindowsManager* instance;
    std::shared_ptr<QWidget> curWindow;
};