#include "State.h"
#include "Automata.h"

using namespace AA;

State::State(int id, QPointF point, Automata* automata) : id(id), point(point), automata(automata)
{
}

State::~State()
{
    
}

QPointF State::getPoint()
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

// bool State::operator<(const State& other)
// {
//     return this->id < other.id;
// }

void State::setId(int id)
{
    this->id = id;
}
