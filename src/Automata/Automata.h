#include "lib/json.hpp"
#include <QSet>
#include <QMap>
#include <QList>

namespace AA
{
    class State;
    class Transition;
    class Automata
    {
    public:
        Automata();
        virtual ~Automata();

        QList<Transition*> getTransitionsFromState(State* source);
        QList<Transition*> getTransitionsToState(State* dest);
        QList<Transition*> getTransitionsStateToState(State* source, State* dest);
        QList<Transition*> getTransitions();
        void addTransition(Transition* transition);
        void replaceTransition(Transition* oldT, Transition* newT);
        void removeTransition(Transition* transition);

        State* createState(QPoint point, int id = -1);
        void addState(State* state);
        void removeState(State* state);
        State* getStateById(int id);
        QList<State*> getStates();
        bool isState(State* state);

        State* setInitialState(State* state);
        State* getInitialState();
        bool isInitialState(State* state);

        void addFinalState(State* state);
        void removeFinalState(State* state);
        QList<State*> getFinalStates();
        bool isFinalState(State* state);

        nlohmann::json toJson();
    protected:
        QSet<State*> states;
        QSet<Transition*> transitions;
        QSet<State*> finalStates;

        QMap<int,QList<Transition*>> fromTransitions;
        QMap<int,QList<Transition*>> toTransitions;

        int lastGivenId;
        State* initialState;
        nlohmann::json data;
        

    private:
    };
}