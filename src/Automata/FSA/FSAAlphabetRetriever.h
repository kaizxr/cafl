#pragma once
#include "src/Automata/AlphabetRetriever.h"

namespace FSA
{
    class AlphabetRetriver : public AA::AlphabetRetriver
    {
    public:
        AlphabetRetriver();
        ~AlphabetRetriver();
        QList<QString> getAlphabet(AA::Automata* automata) override;
    };
}
