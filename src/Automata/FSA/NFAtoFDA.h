#pragma once
#include <QList>

namespace AA
{
    class State;
    class Automata;
}

namespace FSA
{
    class NFAToDFA
    {
    public:
        NFAToDFA();
        ~NFAToDFA();
        AA::State* createInitialState(AA::Automata* nfa, AA::Automata* dfa);
        bool hasFinalState(QList<AA::State*> states, AA::Automata automata);
        QList<AA::State*> getStatesDest(AA::State* state, AA::Automata* automata);
    };
}