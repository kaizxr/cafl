#pragma once
#include <QWindow>

#define SINGLE SingletonManager::getInstance()

class SingletonManager
{
public:
    static SingletonManager* getInstance();
    static void cleanup();
    SingletonManager();
    ~SingletonManager();
    void reload();

private:
    static SingletonManager* instance;
    std::shared_ptr<QWidget> curWindow;
};