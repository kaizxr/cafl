#pragma once
#include "src/Automata/Simulator.h"

namespace FSA
{
    class StepByStepSimulator : public AA::Simulator
    {
    public:
        StepByStepSimulator(AA::Automata* automata);
        ~StepByStepSimulator();
        QList<AA::Configuration*> getInitialConfigs(QString input) override;
        QList<AA::Configuration*> stepConfigs(AA::Configuration* config) override;
        bool isAccepted() override;
        bool simulateInput(QString input) override;
    };
}