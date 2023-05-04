#pragma once

#include "ltl.hpp"
#include "fsm.hpp"
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <optional>

namespace model::translator
{
    using namespace model::ltl;
    using namespace model::fsm;

    using FormulaSet = std::unordered_set<Formula>;
    using AtomMap = std::map<std::string, bool>;
    using AtomPermutation = std::vector<AtomMap>;
    using FormulaMap = std::map<std::string, Formula>;
    using State = std::pair<const std::string, FormulaMap>;
    using States = std::vector<std::string>;
    using FinalStates = std::map<int, States>;
    using StateMap = std::map<std::string, FormulaMap>;

    class Translator
    {
    private:
        AtomPermutation get_permuation_atoms(const AtomMap &atoms);
        FormulaMap get_classic(const FormulaSet &closure, const AtomMap &atoms);
        StateMap get_local_states(const FormulaSet &closure, size_t &states_number, const FormulaMap &true_formulas);
        void handle_until_case(const Formula &closure_elem, State &local_state, StateMap &additional_states, size_t &states_number);

    protected:
        const Formula &simplify(const Formula &formula);
        FormulaSet get_closure(const Formula &formula);
        AtomPermutation get_atoms(const FormulaSet &closure);
        StateMap get_states(const FormulaSet &closure);
        States get_initials(const StateMap &states, const Formula &f);
        FinalStates get_finals(const StateMap &states, const Formula &f, const FormulaSet &closure);

    public:
        Translator() {}
        ~Translator() {}
        const Automaton translate(const Formula &formula);
    };
} // namespace model::
