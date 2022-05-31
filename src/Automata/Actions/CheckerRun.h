#pragma once
#include "MultipleRun.h"
#include <QMessageBox>

namespace AA
{
    namespace Actions
    {
        class CheckerRun : public MultipleRun
        {
        public:
            CheckerRun(AA::Automata* automata, QList<QString> inputs);
            ~CheckerRun();
        protected:
            bool reportConfiguration(AA::Configuration* conf) override;
        private:
            QList<QString> inputs;
            QList<QString> outputs;
        };
    }
}