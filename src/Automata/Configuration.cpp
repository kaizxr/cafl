#include "Configuration.h"
#include "State.h"

using namespace AA;

Configuration::Configuration(State* state, Configuration* parent)
    : currentState(state), parent(parent), focused(false)
{
}

Configuration::~Configuration()
{
}

State* Configuration::getCurrentState()
{
    return currentState;
}

void Configuration::setCurrentState(State* state)
{
    currentState = state;
}

Configuration* Configuration::getParent()
{
    return parent;
}

bool Configuration::isEqualTo(Object* other)
{
    auto casted = dynamic_cast<Configuration*>(other);
    if (parent != casted->parent)
        return false;
    return currentState == casted->currentState;
}

bool Configuration::isFocused()
{
    return focused;
}

void Configuration::setFocused(bool focused)
{
    this->focused = focused;
}

void Configuration::reset()
{
    setFocused(false);
}
