#pragma once
#include "lib/json.hpp"

class PlaygroundManager
{
public:
    PlaygroundManager();
    ~PlaygroundManager();
    void parse();
    int getCurrentTaskId() const;
    void nextTask();
    void tryOpenTask(int forcedId);
    nlohmann::json getCurrentTaskData();
    nlohmann::json getData();

private:
    int forcedTaskId;
    int currentTaskId;
    nlohmann::json currentTaskData;
    nlohmann::json data;
};