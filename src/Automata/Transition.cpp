#include "Transition.h"
#include "src/Automata/State.h"
using namespace AA;

Transition::Transition(State* source, State* dest) {
    this->source = source;
    this->dest = dest;
}

Transition::~Transition() {
    
}

State* Transition::getSource() {
    return source;
}

State* Transition::getDest() {
    return dest;
}

void Transition::setSource(State* state) {
    source = state;
}

void Transition::setDest(State* state) {
    dest = state;
}

Automata* Transition::getAutomata() {
    return dest->getAutomata();
}

nlohmann::json Transition::toJson() {
    // TO-DO:
}

bool Transition::isEqualTo(Transition* other) {
    if (dynamic_cast<Transition*>(other))
        return dest == other->dest && source == other->source;
    return false;
}

QPoint Transition::getControl() {
    // Thinking:
}

void Transition::setControl(QPoint point) {
    // Thinking:
}
