#pragma once

#include "ltl.hpp"
#include "fsm.hpp"

namespace model::translator
{
    class Translator
    {
    private:

    public:
        Translator() {}
        ~Translator() {}
        fsm::Automaton translate(const ltl::Formula &formula);
    };
} // namespace model::
