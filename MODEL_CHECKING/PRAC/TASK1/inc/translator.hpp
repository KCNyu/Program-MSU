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
    using FormulaVec = std::vector<Formula>;

    using AtomMap = std::map<Formula, bool>;
    using AtomPermutation = std::vector<AtomMap>;

    using StateVec = std::vector<FormulaVec>;

    using States = std::vector<std::string>;
    using FinalStates = std::vector<States>;
    // source, symbols, target
    using Transitions = std::vector<std::tuple<std::string, std::set<std::string>, std::string>>;

    class Translator
    {
    private:
        AtomPermutation get_atoms(const FormulaSet &closure);
        AtomPermutation get_permuation_atoms(const AtomMap &atoms);

        FormulaVec get_classic(const FormulaSet &closure, const AtomMap &atoms);
        std::optional<bool> get_true_classic(const Formula &formula, const AtomMap &atoms);

        StateVec get_local_states(const FormulaSet &closure, const FormulaVec &classic);
        std::optional<bool> get_true_state(const Formula &formula, const FormulaVec &formulas);
        void handle_until_case(const Formula &elem, FormulaVec &local_state, StateVec &with_until_states);

        std::set<std::string> get_symbol(const FormulaVec &state);
        bool is_satisfyied(const FormulaVec &u_formulas, const FormulaVec &x_formulas, const FormulaVec &source, const FormulaVec &target);

        std::string get_state_name(const size_t &index) const { return _state_prefix + std::to_string(index); }
        std::string _state_prefix;

    protected:
        const Formula &simplify(const Formula &formula);
        FormulaSet get_closure(const Formula &formula);
        StateVec get_states(const FormulaSet &closure);

        States get_initials(const StateVec &states, const Formula &f);
        FinalStates get_finals(const StateVec &states, const Formula &f, const FormulaSet &closure);
        Transitions get_transitions(const StateVec &states, const FormulaSet &closure);

        const Automaton get_automaton(const StateVec &states, const States &initials, const FinalStates &finals, const Transitions &transitions);

    public:
        Translator(std::string prefix = "s") : _state_prefix(prefix) {}
        ~Translator() {}
        const Automaton translate(const Formula &formula);
    };
} // namespace model::
