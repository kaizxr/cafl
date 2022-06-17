#include "Automata.h"
#include "src/Automata/State.h"
#include "src/Automata/Transition.h"
#include "src/Utils/Utils.h"

using namespace AA;

Automata::Automata() {
    initialState = nullptr;
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
    return list;
}

void Automata::addTransition(Transition* transition) {
    if (transitions.contains(transition))
        return;
    if (transition->getDest() == nullptr || transition->getSource() == nullptr)
        return;
    transitions.insert(transition);
    if (fromTransitions.empty()) fromTransitions = QMap<int,QList<Transition*>>();
    QList<Transition*> list = fromTransitions[transition->getSource()->getId()];
    list.append(transition);
    fromTransitions[transition->getSource()->getId()] = list;
    if (toTransitions.empty()) toTransitions = QMap<int,QList<Transition*>>();
    list = toTransitions[transition->getDest()->getId()];
    list.append(transition);
    toTransitions[transition->getDest()->getId()] = list;
}

void Automata::replaceTransition(Transition* oldT, Transition* newT) {
    if (oldT->isEqualTo(newT))
        return;
    if (transitions.contains(newT))
        return;
    if (transitions.remove(oldT))
    {
        transitions.insert(newT);
        QList<Transition*> list = fromTransitions[oldT->getSource()->getId()];
        list.replace(list.indexOf(oldT),newT);
        fromTransitions[newT->getSource()->getId()] = list;
        list = toTransitions[oldT->getDest()->getId()];
        list.replace(list.indexOf(oldT),newT);
        toTransitions[newT->getDest()->getId()] = list;
    }
}

void Automata::removeTransition(Transition* transition) {
    transitions.remove(transition);
    QList<Transition*> list = fromTransitions[transition->getSource()->getId()];
    list.remove(list.indexOf(transition));
    fromTransitions[transition->getSource()->getId()] = list;
    list = toTransitions[transition->getDest()->getId()];
    list.remove(list.indexOf(transition));
    toTransitions[transition->getDest()->getId()] = list;
}

State* Automata::createState(QPointF point, int id, QString text) {
    if (id == -1)
        id = lastGivenId++;
    if (text.isEmpty())
        text = QString::number(id);
    State* state = new State(id,point,this,text);
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
    // std::sort(list.begin(),list.end());
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

#include <iostream>
nlohmann::json Automata::toJson() {
    //TO-DO:
    nlohmann::json data;
    for (const auto& state : states)
    {
        const auto& stateStr = QString::number(state->getId()).toStdString().c_str();
        data["Automata"]["State"][stateStr]["pos"]["x"] = state->getPoint().x();
        data["Automata"]["State"][stateStr]["pos"]["y"] = state->getPoint().y();
    }
    for (const auto& transition : transitions)
    {
        const auto& edgeStr = strFormat("%d->%d",transition->getSource()->getId(),transition->getDest()->getId()).c_str();
        data["Automata"]["Transition"][edgeStr]["source"] = transition->getSource()->getId();
        data["Automata"]["Transition"][edgeStr]["dest"] = transition->getDest()->getId();
    }
    std::cout << std::setw(4) << data << std::endl;
    return data;
}
