#pragma once

#include "ltl.hpp"
#include "fsm.hpp"
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>

namespace model::translator
{
    using namespace model::ltl;
    using namespace model::fsm;

    using FormulaSet = std::unordered_set<Formula>;
    using AtomMap = std::map<std::string, bool>;
    using FormulaMap = std::unordered_map<std::string, Formula>;
    using StateMap = std::unordered_map<std::string, FormulaMap>;

    class Translator
    {
    protected:
        const Formula &simplify(const Formula &formula);
        FormulaSet get_closure(const Formula &formula);
        AtomMap get_atoms(const FormulaSet &closure);
        StateMap get_states(const FormulaSet &closure);

    public:
        Translator() {}
        ~Translator() {}
        const Automaton translate(const Formula &formula);
    };
} // namespace model::
