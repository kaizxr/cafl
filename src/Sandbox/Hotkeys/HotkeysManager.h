#pragma once

#define HOTKEYS HotkeysManager::getInstance()

class QKeyEvent;
class HotkeysManager final
{
public:
    static HotkeysManager* getInstance();
    static void cleanup();
    HotkeysManager();
    ~HotkeysManager();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    static HotkeysManager* instance;
};
