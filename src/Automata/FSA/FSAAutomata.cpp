#include "FSAAutomata.h"
#include "src/Automata/State.h"
#include "FSATransition.h"
#include "src/Utils/Utils.h"
#include <iostream>

using namespace FSA;

Automata::Automata() : AA::Automata()
{
}

nlohmann::json Automata::toJson()
{
    qInfo("fsaa to json");
    nlohmann::json data;
    for (const auto& state : states)
    {
        const auto& stateStr = QString::number(state->getId()).toStdString().c_str();
        data["Automata"]["State"][stateStr]["pos"]["x"] = state->getPoint().x();
        data["Automata"]["State"][stateStr]["pos"]["y"] = state->getPoint().y();
    }
    for (const auto& state : getFinalStates())
    {
        const auto& stateStr = QString::number(state->getId()).toStdString().c_str();
        data["Automata"]["State"][stateStr]["final"] = true;
    }
    const auto& stateStr = QString::number(getInitialState()->getId()).toStdString().c_str();
    data["Automata"]["State"][stateStr]["initial"] = true;
    qInfo("start transitions");
    for (const auto& transition : transitions)
    {
        qInfo("start transitions");
        auto casted = dynamic_cast<FSA::Transition*>(transition);
        const auto& edgeStr = strFormat("%d->%d",casted->getSource()->getId(),casted->getDest()->getId()).c_str();
        data["Automata"]["Transition"][edgeStr]["source"] = casted->getSource()->getId();
        data["Automata"]["Transition"][edgeStr]["dest"] = casted->getDest()->getId();
        data["Automata"]["Transition"][edgeStr]["text"] = casted->getText().toStdString();
    }
    std::cout << std::setw(4) << data << std::endl;
    return data;
}
