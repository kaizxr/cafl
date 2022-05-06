#pragma once
#include "lib/json.hpp"

#define CONST Constants::getInstance()->data()

class Constants
{
public:
    static Constants* getInstance();
    static void cleanup();
    Constants();
    ~Constants();

    nlohmann::json data();
private:
    void parse();
    
    nlohmann::json json;
    static Constants* instance;
};
