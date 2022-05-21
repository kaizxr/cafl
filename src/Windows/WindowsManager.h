#pragma once
#include <QMainWindow>

#define WINDOWS WindowsManager::getInstance()

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

    static WindowsManager* instance;
    std::shared_ptr<QMainWindow> curWindow;
};