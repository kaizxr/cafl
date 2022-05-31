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
    nlohmann::json getCurrentTaskData();
    nlohmann::json getData();

private:
    int currentTask;
    nlohmann::json currentTaskData;
    nlohmann::json data;
};