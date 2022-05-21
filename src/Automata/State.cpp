#include "State.h"
#include "Automata.h"

using namespace AA;

State::State(int id, QPoint point, Automata* automata) : id(id), point(point), automata(automata)
{
}

State::~State()
{
    
}

QPoint State::getPoint()
{
    return point;
}

Automata* State::getAutomata()
{
    return automata;
}

int State::getId() const
{
    return id;
}

nlohmann::json State::toJson()
{
    
}

void State::setId(int id)
{
    this->id = id;
}