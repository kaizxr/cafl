#pragma once
#include "src/Automata/Transition.h"
#include <QString>

namespace FSA
{
    class Transition : public AA::Transition
    {
    public:
        Transition(AA::State* source, AA::State* dest, QString text);
        ~Transition();
        QString getText() const;
        bool isEqualTo(Object* other) override;
    protected:
        void setText(QString text);
        QString text;
    };
}