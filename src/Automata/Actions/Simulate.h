#pragma once
#include <QSet>
#include <QString>
#include <QInputDialog>

namespace AA
{
    class Automata;
    class Simulator;
    class Configuration;
    class Object;
    
    namespace Actions
    {
        class Simulate
        {
        public:
            Simulate(AA::Automata* automata);
            virtual ~Simulate();
            virtual void handleInteraction(Automata* automata, AA::Simulator* simulator, QList<AA::Configuration*> configs, QInputDialog* initialInput);
            void actionPerformed();
        protected:
            AA::Simulator* getSimulator(AA::Automata* automata);
            QInputDialog* createInputDialog(QString title);
            QString name;
        private:

            AA::Automata* automata;
        };
    }
}