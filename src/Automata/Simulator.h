#pragma once
#include <QList>
#include <QSet>

namespace AA
{
    class Automata;
    class Configuration;
    class Simulator
    {
    public:
        Simulator(Automata* automata)
            : automata(automata), configs(QSet<Configuration*>()) {};
        virtual ~Simulator(){};
        virtual QList<Configuration*> getInitialConfigs(QString input) = 0;
        virtual QList<Configuration*> stepConfigs(Configuration* config) = 0;
        virtual bool isAccepted() = 0;
        virtual bool simulateInput(QString input) = 0;
        Automata* getAutomata();
    protected:
        Automata* automata;
        QSet<Configuration*> configs;
    };
}