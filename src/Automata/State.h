#include "lib/json.hpp"
#include <QPoint>

namespace AA
{
    class Automata;
    class State
    {
    public:
        State(int id, QPoint point, Automata* automata);
        ~State();
        QPoint getPoint();
        Automata* getAutomata();
        int getId() const;
        nlohmann::json toJson();
    protected:
        void setId(int id);
    private:
        Automata* automata;
        int id;
        QPoint point;
        nlohmann::json data;
    };
}