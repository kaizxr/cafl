#pragma once
#include "Object.h"
#include "lib/json.hpp"
#include <QPoint>

namespace AA
{
    class Automata;
    class State;
    class Transition : public Object
    {
    public:
        Transition(State* source, State* dest);
        virtual ~Transition();
        State* getSource();
        State* getDest();
        void setSource(State* state);
        void setDest(State* state);
        Automata* getAutomata();
        nlohmann::json toJson();
        virtual bool isEqualTo(Object* other);
        QPoint getControl();
        void setControl(QPoint point);
    private:
        State* source;
        State* dest;
        QPoint controlPoint;

        nlohmann::json data;
    };
}