#pragma once
#include "Simulate.h"
#include <QMessageBox>

namespace AA
{
    namespace Actions
    {
        class FastRun : public Simulate
        {
        public:
            FastRun(AA::Automata* automata);
            ~FastRun();
            bool confirmContinue(int generated);
            void handleInteraction(Automata* automata, AA::Simulator* simulator, QList<AA::Configuration*> configs, QInputDialog* initialInput) override;

        protected:
            bool reportConfiguration(AA::Configuration* conf);
        };
    }
}