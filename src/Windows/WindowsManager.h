#pragma once
#include <QMainWindow>

class SandboxWindow;
class TitleWindow;
class WindowsManager
{
public:
    static WindowsManager* getInstance();
    static void cleanup();
    WindowsManager();
    ~WindowsManager();

    std::shared_ptr<SandboxWindow> createSandboxWindow();
    std::shared_ptr<TitleWindow> createTitleWindow();
    void changeWindow(std::string windowType = "title");

private:
    static WindowsManager* instance;
    std::shared_ptr<QMainWindow> curWindow;
};

inline WindowsManager* WINDOWS() {
    return WindowsManager::getInstance();
}