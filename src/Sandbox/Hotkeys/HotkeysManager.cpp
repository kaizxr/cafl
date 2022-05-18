#include "HotkeysManager.h"
#include <QKeyEvent>
HotkeysManager* HotkeysManager::instance = nullptr;

HotkeysManager* HotkeysManager::getInstance()
{
	if (!instance)
	{
        instance = new HotkeysManager();
    }
	return instance;
}

void HotkeysManager::cleanup()
{
	delete instance;
	instance = nullptr;
}

HotkeysManager::HotkeysManager()
{
}

HotkeysManager::~HotkeysManager()
{
}

void HotkeysManager::keyPressEvent(QKeyEvent *event)
{
}

void HotkeysManager::keyReleaseEvent(QKeyEvent *event)
{
}
