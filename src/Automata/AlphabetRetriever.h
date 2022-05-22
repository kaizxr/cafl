#pragma once
#include <QList>
#include <QString>

namespace AA
{
    class Automata;
    class AlphabetRetriver
    {
    public:
        AlphabetRetriver(){};
        virtual QList<QString> getAlphabet(Automata* automata) = 0;
    };
}
