#pragma once
#include "src/Automata/Automata.h"

namespace FSA
{
    class Automata : public AA::Automata
    {
    public:
        Automata();
        nlohmann::json toJson() override;
    };
}