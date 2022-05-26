#pragma once
#include <QList>
#include <QString>
#define SIMULATE SimulateHelper::getInstance()

class SimulateHelper
{
public:
    static SimulateHelper* getInstance();
    static void cleanup();
    SimulateHelper();
    ~SimulateHelper();

    void startFastRun();
    void startMultipleRun(QList<QString> inputs);

    QList<QString> outputs;

private:
    QList<QString> inputs;
    static SimulateHelper* instance;
};
