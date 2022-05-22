#pragma once
#include "Object.h"
#include "lib/json.hpp"
#include <QPointF>

namespace AA
{
    class Automata;
    class State : public Object
    {
    public:
        State(int id, QPointF point, Automata* automata);
        ~State();
        QPointF getPoint();
        Automata* getAutomata();
        int getId() const;
        nlohmann::json toJson();
        // bool operator<(const State& other);
    protected:
        void setId(int id);
    private:
        Automata* automata;
        int id;
        QPointF point;
        nlohmann::json data;
    };
}