#include "Automata.h"
#include "src/Automata/State.h"
#include "src/Automata/Transition.h"

using namespace AA;

Automata::Automata() {
    lastGivenId = 0;
}

Automata::~Automata() {
    
}

QList<Transition*> Automata::getTransitionsFromState(State* source) {
    QList<Transition*> list = fromTransitions[source->getId()];
    return list;
}

QList<Transition*> Automata::getTransitionsToState(State* dest) {
    QList<Transition*> list = toTransitions[dest->getId()];
    return list;
}

QList<Transition*> Automata::getTransitionsStateToState(State* source, State* dest) {
    QList<Transition*> temp = fromTransitions[source->getId()];
    QList<Transition*> list;
    for (const auto& trans : temp)
    {
        if (trans->getDest() == dest)
            list.append(trans);
    }
    return list;
}

QList<Transition*> Automata::getTransitions() {
    QList<Transition*> list(transitions.begin(),transitions.end());
}

void Automata::addTransition(Transition* transition) {
    if (transitions.contains(transition))
        return;
    if (transition->getDest() == nullptr || transition->getSource() == nullptr)
        return;
    transitions.insert(transition);
    if (fromTransitions.empty()) fromTransitions = QMap<int,QList<Transition*>>();
    QList<Transition*> list = fromTransitions[transition->getDest()->getId()];
    list.append(transition);
    fromTransitions[transition->getDest()->getId()];
    if (toTransitions.empty()) toTransitions = QMap<int,QList<Transition*>>();
    list = toTransitions[transition->getDest()->getId()];
    list.append(transition);
    toTransitions[transition->getDest()->getId()];
}

void Automata::replaceTransition(Transition* oldT, Transition* newT) {
    if (oldT->isEqualTo(newT))
        return;
    if (transitions.contains(newT))
        return;
    if (transitions.remove(oldT))
    {
        transitions.insert(newT);
        QList<Transition*> list = fromTransitions[oldT->getDest()->getId()];
        list.replace(list.indexOf(oldT),newT);
        fromTransitions[newT->getDest()->getId()];
        list = toTransitions[oldT->getDest()->getId()];
        list.replace(list.indexOf(oldT),newT);
        toTransitions[newT->getDest()->getId()];
    }
}

void Automata::removeTransition(Transition* transition) {
    transitions.remove(transition);
    QList<Transition*> list = fromTransitions[transition->getDest()->getId()];
    list.remove(list.indexOf(transition));
    fromTransitions[transition->getDest()->getId()];
    list = toTransitions[transition->getDest()->getId()];
    list.remove(list.indexOf(transition));
    toTransitions[transition->getDest()->getId()];
}

State* Automata::createState(QPoint point, int id) {
    if (id == -1)
        id = lastGivenId++;
    State* state = new State(id,point,this);
    addState(state);
    lastGivenId = id;
    return state;
}

void Automata::addState(State* state) {
    states.insert(state);
    fromTransitions.insert(state->getId(),QList<Transition*>());
    toTransitions.insert(state->getId(),QList<Transition*>());
}

void Automata::removeState(State* state) {
    QList<Transition*> list = getTransitionsFromState(state);
    for (auto transition : list)
        removeTransition(transition);
    list = getTransitionsToState(state);
    for (auto transition : list)
        removeTransition(transition);
    states.remove(state);
    finalStates.remove(state);
    if (state == initialState)
        initialState = nullptr;

    fromTransitions.remove(state->getId());
    toTransitions.remove(state->getId());
    delete state;
}

State* Automata::getStateById(int id) {
    for (auto state : states)
    {
        if (state->getId() == id)
            return state;
    }
    return nullptr;
}

QList<State*> Automata::getStates() {
    QList<State*> list(states.begin(),states.end());
    std::sort(list.begin(),list.end(),[](const State& a, const State& b){return a.getId() < b.getId();});
    return list;
}

bool Automata::isState(State* state) {
    return states.contains(state);
}

State* Automata::setInitialState(State* state) {
    State* oldIState = this->initialState;
    this->initialState = state;
    return oldIState;
}

State* Automata::getInitialState() {
    return initialState;
}

bool Automata::isInitialState(State* state) {
    return initialState == state;
}

void Automata::addFinalState(State* state) {
    finalStates.insert(state);
}

void Automata::removeFinalState(State* state) {
    finalStates.remove(state);
}

QList<State*> Automata::getFinalStates() {
    QList<State*> list(finalStates.begin(),finalStates.end());
    return list;
}

bool Automata::isFinalState(State* state) {
    return finalStates.contains(state);
}

nlohmann::json Automata::toJson() {
    //TO-DO:
}
