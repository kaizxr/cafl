#include "lib/json.hpp"
#include <QPoint>

namespace AA
{
    class Automata;
    class State;
    class Transition
    {
    public:
        Transition(State* source, State* dest);
        ~Transition();
        State* getSource();
        State* getDest();
        void setSource(State* state);
        void setDest(State* state);
        Automata* getAutomata();
        nlohmann::json toJson();
        bool isEqualTo(Transition* other);
        QPoint getControl();
        void setControl(QPoint point);
    private:
        State* source;
        State* dest;
        QPoint controlPoint;

        nlohmann::json data;
    };
}