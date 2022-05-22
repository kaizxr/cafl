#include "FSAConfiguration.h"
#include "src/Automata/State.h"
#include "src/Automata/Automata.h"

using namespace FSA;

Configuration::Configuration(AA::State* state, Configuration* parent, QString input, QString unprocessedInput)
    : AA::Configuration(state,parent), input(input), unprocessedInput(unprocessedInput)
{
}

Configuration::~Configuration()
{
}

QString Configuration::getInput()
{
    return input;
}

QString Configuration::getUnprocessed()
{
    return unprocessedInput;
}

void Configuration::setUnprocessedInput(QString unprocessedInput)
{
    this->unprocessedInput = unprocessedInput;
}

bool Configuration::isAccepted()
{
    if (!unprocessedInput.isEmpty())
        return false;
    AA::State* state = getCurrentState();
    AA::Automata* automata = state->getAutomata();
    return automata->isFinalState(state);
}

bool Configuration::isEqualTo(Object* other)
{
    if (other == this)
        return true;
    if (auto casted = dynamic_cast<Configuration*>(other))
    {
        return AA::Configuration::isEqualTo(other) &&
            unprocessedInput == casted->unprocessedInput;
    }
    return false;
}
