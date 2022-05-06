#include "Constants.h"
// parse
#include <fstream>
#include <QTCore>

#include <iostream>

#include <QFile>
#include <QJsonDocument>

Constants* Constants::instance = nullptr;

Constants* Constants::getInstance()
{
	if (!instance)
	{
        instance = new Constants();
    }
	return instance;
}

void Constants::cleanup()
{
	delete instance;
	instance = nullptr;
}

Constants::Constants()
{
    parse();
}

Constants::~Constants()
{
}

nlohmann::json Constants::data()
{
	return json;
}

void Constants::parse()
{
	std::ifstream in("./res/constants.json");
	json = nlohmann::json::parse(in);
}
