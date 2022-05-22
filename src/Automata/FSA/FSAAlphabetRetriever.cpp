#include "FSAAlphabetRetriever.h"
#include "FSATransition.h"
#include "src/Automata/Automata.h"

using namespace FSA;

AlphabetRetriver::AlphabetRetriver()
{
}

AlphabetRetriver::~AlphabetRetriver()
{
}

QList<QString> AlphabetRetriver::getAlphabet(AA::Automata* automata)
{
    QList<QString> list;
    const auto& transitions = automata->getTransitions();
    for (const auto& transition : transitions)
    {
        auto casted = dynamic_cast<Transition*>(transition);
        const auto& text = casted->getText();
        if (!text.isEmpty() && !list.contains(text))
            list.append(text);
    }
    return list;
}
