#pragma once
#include "FastRun.h"
#include <QMessageBox>

namespace AA
{
    namespace Actions
    {
        class MultipleRun : public FastRun
        {
        public:
            MultipleRun(AA::Automata* automata, QList<QString> inputs);
            ~MultipleRun();
            bool confirmContinue(int generated);
            void handleInteraction(Automata* automata, AA::Simulator* simulator, QList<AA::Configuration*> configs, QInputDialog* initialInput) override;
            void preHandle() override;
            QList<QString> getOutputs() const;
        protected:
            bool reportConfiguration(AA::Configuration* conf);
        private:
            QList<QString> inputs;
            QList<QString> outputs;
        };
    }
}