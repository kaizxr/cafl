#pragma once
#include "Object.h"

namespace AA
{
    class State;
    class Configuration : public Object
    {
    public:
        Configuration(State* state, Configuration* parent);
        virtual ~Configuration();
        State* getCurrentState();
        void setCurrentState(State* state);
        Configuration* getParent();
        virtual bool isAccepted() = 0;
        virtual bool isEqualTo(Object* other);
        bool isFocused();
        void setFocused(bool focused);
        void reset();
    private:
        bool focused;
        State* currentState;
        Configuration* parent;
    };
}