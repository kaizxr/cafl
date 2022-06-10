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
    currentTaskId = data["tasks"]["current"];
    in = std::ifstream(strFormat("res/tasks/task_%d/task_%d.json",currentTaskId,currentTaskId));
    in >> currentTaskData;
    qInfo("currentTask = %d", currentTaskId);
}

int PlaygroundManager::getCurrentTaskId() const
{
    return currentTaskId;
}

void PlaygroundManager::nextTask()
{
    if (data["tasks"].contains("is_forced"))
    {
        if (bool isForced = data["tasks"]["is_forced"])
        {
            data["tasks"]["is_forced"] = false;
            currentTaskId = data["tasks"]["prev"];
            data["tasks"]["prev"] = currentTaskId;
            data["tasks"]["current"] = ++currentTaskId;
        }
    }
    else
    {
        data["tasks"]["prev"] = currentTaskId;
        data["tasks"]["current"] = ++currentTaskId;
    }

    std::ofstream out("res/tasks/data.json");
    out << std::setw(4) << data << std::endl;
}

void PlaygroundManager::tryOpenTask(int forcedId)
{
    data["tasks"]["is_forced"] = true;
    data["tasks"]["prev"] = currentTaskId;
    data["tasks"]["current"] = forcedId;

    std::ofstream out("res/tasks/data.json");
    out << std::setw(4) << data << std::endl;
}

nlohmann::json PlaygroundManager::getCurrentTaskData()
{
    return currentTaskData;
}
