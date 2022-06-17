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
    if (in.peek() == std::ifstream::traits_type::eof())
    {
        in.close();
        in = std::ifstream("res/tasks/error.json");
    }
    in >> currentTaskData;
    qInfo("currentTask = %d", currentTaskId);
    in.close();
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
        else
        {
            data["tasks"]["prev"] = currentTaskId;
            data["tasks"]["current"] = ++currentTaskId;
        }
    }
    else
    {
        data["tasks"]["prev"] = currentTaskId;
        data["tasks"]["current"] = ++currentTaskId;
    }
    QFile::remove("res/tasks/data.json");
    std::ofstream out("res/tasks/data.json");
    out << std::setw(4) << data << std::endl;
    out.close();
}

void PlaygroundManager::tryOpenTask(int forcedId)
{
    data["tasks"]["is_forced"] = true;
    data["tasks"]["prev"] = currentTaskId;
    data["tasks"]["current"] = forcedId;

    std::ofstream out("res/tasks/data.json");
    out << std::setw(4) << data << std::endl;
    out.close();
}

nlohmann::json PlaygroundManager::getCurrentTaskData()
{
    return currentTaskData;
}
