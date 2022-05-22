#include "FSATransition.h"

using namespace FSA;

Transition::Transition(AA::State* source, AA::State* dest, QString text)
    : AA::Transition(source,dest), text(text)
{
}

Transition::~Transition()
{
}

QString Transition::getText() const
{
    return text;
}

void Transition::setText(QString text)
{
    this->text = text;
}

bool Transition::isEqualTo(Object* other)
{
    if (auto casted = dynamic_cast<Transition*>(other))
        return AA::Transition::isEqualTo(casted) && text == casted->text;
    return false;
}
