#pragma once
#include <QWindow>

#define WINDOWS WindowsManager::getInstance()

namespace Window::Simulation
{
    class Output;
}

class SandboxWindow;
class TitleWindow;
class WindowsManager
{
public:
    static WindowsManager* getInstance();
    static void cleanup();
    WindowsManager();
    ~WindowsManager();
    void changeWindow(std::string windowType = "title");
    SandboxWindow* getSandboxWindow();

private:
    std::shared_ptr<SandboxWindow> createSandboxWindow();
    std::shared_ptr<TitleWindow> createTitleWindow();
    std::shared_ptr<Window::Simulation::Output> createOutputWindow();

    static WindowsManager* instance;
    std::shared_ptr<QWidget> curWindow;
};