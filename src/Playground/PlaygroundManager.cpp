#include "PlaygroundManager.h"
#include "fstream"
#include "src/Utils/Utils.h"
#include <QtCore>

PlaygroundManager::PlaygroundManager()
{
    qInfo("PlaygroundManager");
    parse();
}

PlaygroundManager::~PlaygroundManager()
{
}

void PlaygroundManager::parse()
{
    std::ifstream in("res/tasks/data.json");
    in >> data;
    in.close();
    currentTask = data["tasks"]["current"];
    in = std::ifstream(strFormat("res/tasks/task_%d/task_%d.json",currentTask,currentTask));
    in >> currentTaskData;
    qInfo("currentTask = %d", currentTask);
}

int PlaygroundManager::getCurrentTaskId() const
{
    return currentTask;
}

void PlaygroundManager::nextTask()
{
    data["tasks"]["current"] = ++currentTask;

    std::ofstream out("res/tasks/data.json");
    out << std::setw(4) << data << std::endl;
}

nlohmann::json PlaygroundManager::getCurrentTaskData()
{
    return currentTaskData;
}
