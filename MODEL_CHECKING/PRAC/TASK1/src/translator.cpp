#include "translator.hpp"

namespace model::translator
{
    const Formula &Translator::simplify(const Formula &formula)
    {
        switch (formula.kind())
        {
        case Formula::ATOM:
        {
            return P(formula.prop());
        }
        case Formula::NOT:
        {
            return !simplify(formula.arg());
        }
        case Formula::AND:
        {
            return simplify(formula.lhs()) && simplify(formula.rhs());
        }
        case Formula::OR:
        {
            return simplify(formula.lhs()) || simplify(formula.rhs());
        }
        case Formula::IMPL:
        {
            return !simplify(formula.lhs()) || simplify(formula.rhs());
        }
        case Formula::X:
        {
            return X(simplify(formula.arg()));
        }
        case Formula::G:
        {
            return !(U(TRUE(), !simplify(formula.arg())));
        }
        case Formula::F:
        {
            return U(TRUE(), simplify(formula.arg()));
        }
        case Formula::U:
        {
            return U(simplify(formula.lhs()), simplify(formula.rhs()));
        }
        case Formula::R:
        {
            return !(U(!simplify(formula.lhs()), !simplify(formula.rhs())));
        }
        default:
        {
            throw std::runtime_error("Unknown formula kind");
        }
        }
    }

    FormulaSet Translator::get_closure(const Formula &formula)
    {
        FormulaSet closure_set;

        switch (formula.kind())
        {
        case Formula::ATOM:
        {
            closure_set.insert(formula);
            break;
        }
        case Formula::NOT:
        {
            closure_set = get_closure(formula.lhs());
            break;
        }
        case Formula::AND:
        case Formula::OR:
        case Formula::U:
        {
            closure_set = get_closure(formula.lhs());
            closure_set.merge(get_closure(formula.rhs()));
            closure_set.insert(formula);
            break;
        }
        case Formula::X:
        {
            closure_set = get_closure(formula.lhs());
            closure_set.insert(formula);
            break;
        }
        case Formula::IMPL:
        case Formula::G:
        case Formula::F:
        case Formula::R:
        default:
        {
            break;
        }
        }

        return closure_set;
    }

    AtomPermutation Translator::get_permuation_atoms(const AtomMap &atoms)
    {
        AtomPermutation permutations;

        std::function<void(size_t, AtomMap)> generate_permutations_rec = [&](size_t index, AtomMap current_atoms)
        {
            if (index == atoms.size())
            {
                permutations.push_back(current_atoms);
                return;
            }

            auto atom_iter = std::next(atoms.begin(), index);
            current_atoms[atom_iter->first] = false;
            generate_permutations_rec(index + 1, current_atoms);

            current_atoms[atom_iter->first] = true;
            generate_permutations_rec(index + 1, current_atoms);
        };

        generate_permutations_rec(0, atoms);
        return permutations;
    }

    AtomPermutation Translator::get_atoms(const FormulaSet &closure)
    {
        AtomMap atoms;
        for (const auto &elem : closure)
        {
            if (elem.kind() == Formula::ATOM || elem.kind() == Formula::X)
            {
                if (elem.kind() == Formula::ATOM && elem.prop() == "true")
                {
                    continue;
                }
                atoms[elem] = false;
            }
        }
        return get_permuation_atoms(atoms);
    }

    std::optional<bool> Translator::get_true_classic(const Formula &formula, const AtomMap &atoms)
    {
        using OpFunc = std::function<std::optional<bool>(const Formula &, const AtomMap &)>;

        std::unordered_map<Formula::Kind, OpFunc> operations = {
            {Formula::ATOM, [](const Formula &f, const AtomMap &atoms) -> std::optional<bool>
             {
                 if (f.prop() == "true")
                 {
                     return true;
                 }
                 return atoms.at(f);
             }},
            {Formula::X, [](const Formula &f, const AtomMap &atoms) -> std::optional<bool>
             {
                 return atoms.at(f);
             }},
            {Formula::NOT, [this](const Formula &f, const AtomMap &atoms) -> std::optional<bool>
             {
                 auto arg_result = get_true_classic(f.arg(), atoms);
                 return arg_result.has_value() ? std::optional<bool>(!*arg_result) : std::nullopt;
             }},
            {Formula::AND, [this](const Formula &f, const AtomMap &atoms) -> std::optional<bool>
             {
                 auto lhs_result = get_true_classic(f.lhs(), atoms);
                 auto rhs_result = get_true_classic(f.rhs(), atoms);
                 if (!lhs_result.has_value() || !rhs_result.has_value())
                     return std::nullopt;
                 return std::optional<bool>(*lhs_result && *rhs_result);
             }},
            {Formula::OR, [this](const Formula &f, const AtomMap &atoms) -> std::optional<bool>
             {
                 auto lhs_result = get_true_classic(f.lhs(), atoms);
                 auto rhs_result = get_true_classic(f.rhs(), atoms);
                 if (!lhs_result.has_value() || !rhs_result.has_value())
                     return std::nullopt;
                 return std::optional<bool>(*lhs_result || *rhs_result);
             }}};

        auto it = operations.find(formula.kind());
        if (it != operations.end())
        {
            return it->second(formula, atoms);
        }

        return std::nullopt;
    }

    FormulaVec Translator::get_classic(const FormulaSet &closure, const AtomMap &atoms)
    {
        FormulaVec classic;
        std::copy_if(closure.begin(), closure.end(), std::back_inserter(classic),
                     [&](const Formula &elem)
                     { return get_true_classic(elem, atoms).value_or(false); });
        return classic;
    }

    std::optional<bool> Translator::get_true_state(const Formula &formula, const FormulaVec &formulas)
    {
        using OpFunc = std::function<std::optional<bool>(const Formula &, const FormulaVec &)>;

        std::unordered_map<Formula::Kind, OpFunc> operations = {
            {Formula::ATOM, [](const Formula &formula, const FormulaVec &formulas) -> std::optional<bool>
             {
                 return std::find(formulas.begin(), formulas.end(), formula) != formulas.end();
             }},
            {Formula::X, [](const Formula &formula, const FormulaVec &formulas) -> std::optional<bool>
             {
                 return std::find(formulas.begin(), formulas.end(), formula) != formulas.end();
             }},
            {Formula::NOT, [this](const Formula &formula, const FormulaVec &formulas) -> std::optional<bool>
             {
                 if (std::find(formulas.begin(), formulas.end(), formula) != formulas.end())
                 {
                     return true;
                 }
                 auto arg_result = get_true_state(formula.arg(), formulas);
                 if (arg_result.has_value())
                 {
                     return !*arg_result;
                 }
                 return std::nullopt;
             }},
            {Formula::AND, [this](const Formula &formula, const FormulaVec &formulas) -> std::optional<bool>
             {
                 if (std::find(formulas.begin(), formulas.end(), formula) != formulas.end())
                 {
                     return true;
                 }
                 auto lhs_result = get_true_state(formula.lhs(), formulas);
                 auto rhs_result = get_true_state(formula.rhs(), formulas);
                 if (!lhs_result.has_value() || !rhs_result.has_value())
                 {
                     return std::nullopt;
                 }
                 return std::optional<bool>(*lhs_result && *rhs_result);
             }},
            {Formula::OR, [this](const Formula &formula, const FormulaVec &formulas) -> std::optional<bool>
             {
                 if (std::find(formulas.begin(), formulas.end(), formula) != formulas.end())
                 {
                     return true;
                 }
                 auto lhs_result = get_true_state(formula.lhs(), formulas);
                 auto rhs_result = get_true_state(formula.rhs(), formulas);
                 if (lhs_result.has_value() && *lhs_result)
                 {
                     return true;
                 }
                 else if (rhs_result.has_value() && *rhs_result)
                 {
                     return true;
                 }
                 return false;
             }},
            {Formula::U, [](const Formula &formula, const FormulaVec &formulas) -> std::optional<bool>
             {
                 if (std::find(formulas.begin(), formulas.end(), formula) != formulas.end())
                 {
                     return true;
                 }
                 return std::nullopt;
             }}};

        auto it = operations.find(formula.kind());
        if (it != operations.end())
        {
            return it->second(formula, formulas);
        }

        return std::nullopt;
    }

    StateVec Translator::get_local_states(const FormulaSet &closure, const FormulaVec &classic)
    {
        StateVec local_states;
        local_states.push_back(classic);

        for (const auto &elem : closure)
        {
            StateVec with_until_states;
            for (auto &local_state : local_states)
            {
                if (std::find(local_state.begin(), local_state.end(), elem) != local_state.end())
                {
                    continue;
                }
                else if (elem.kind() == Formula::U)
                {
                    handle_until_case(elem, local_state, with_until_states);
                }
                else if (get_true_state(elem, local_state).value_or(false))
                {
                    local_state.push_back(elem);
                }
            }
            std::move(std::begin(with_until_states), std::end(with_until_states), std::back_inserter(local_states));
        }
        return local_states;
    }

    void Translator::handle_until_case(const Formula &elem, FormulaVec &local_state, StateVec &with_until_states)
    {
        if (std::find(local_state.begin(), local_state.end(), elem.rhs()) != local_state.end())
        {
            local_state.push_back(elem);
        }
        else if (std::find(local_state.begin(), local_state.end(), elem.lhs()) != local_state.end())
        {
            with_until_states.push_back(local_state);
            with_until_states.back().push_back(elem);

            Formula neg_elem = !elem;
            local_state.push_back(neg_elem);
        }
        else
        {
            Formula neg_elem = !elem;
            local_state.push_back(neg_elem);
        }
    }

    StateVec Translator::get_states(const FormulaSet &closure)
    {
        AtomPermutation atoms = get_atoms(closure);

        StateVec states;

        for (const auto &atom : atoms)
        {
            FormulaVec classic = get_classic(closure, atom);
            StateVec local_states = get_local_states(closure, classic);

            std::move(std::begin(local_states), std::end(local_states), std::back_inserter(states));
        }
        return states;
    }

    States Translator::get_initials(const StateVec &states, const Formula &f)
    {
        States initials;
        size_t current_ind = 0;

        std::transform(states.begin(), states.end(), std::back_inserter(initials), [&](const auto &state)
                       {
                           ++current_ind;
                           if (std::find(state.begin(), state.end(), f) != state.end())
                           {
                               return get_state_name(current_ind);
                           }
                           return std::string{}; });

        initials.erase(std::remove_if(initials.begin(), initials.end(), [](const std::string &s)
                                      { return s.empty(); }),
                       initials.end());

        return initials;
    }

    FinalStates Translator::get_finals(const StateVec &states, const Formula &f, const FormulaSet &closure)
    {
        FinalStates finals;

        std::for_each(closure.begin(), closure.end(), [&](const Formula &elem)
                      {
        if (elem.kind() == Formula::U)
        {
            States final;
            size_t current_ind = 0;

            std::transform(states.begin(), states.end(), std::back_inserter(final), [&](const auto &state) {
                ++current_ind;
                if (std::find(state.begin(), state.end(), elem) == state.end() || std::find(state.begin(), state.end(), elem.rhs()) != state.end())
                {
                    return get_state_name(current_ind);
                }
                return std::string{};
            });

            final.erase(std::remove_if(final.begin(), final.end(), [](const std::string &s) { return s.empty(); }), final.end());

            finals.push_back(final);
        } });

        return finals;
    }

    std::set<std::string> Translator::get_symbol(const FormulaVec &state)
    {
        std::set<std::string> symbol;

        std::transform(state.begin(), state.end(), std::inserter(symbol, symbol.end()),
                       [&](const Formula &f)
                       {
                           return (f.kind() == Formula::ATOM && f.prop() != "true") ? f.prop() : "";
                       });

        symbol.erase("");

        return symbol;
    }

    // Conditions for the implementation of obligations
    bool Translator::is_satisfyied(const FormulaVec &u_formulas, const FormulaVec &x_formulas, const FormulaVec &source, const FormulaVec &target)
    {
        auto x_satisfy = [&](const Formula &x_f)
        {
            bool left = std::find(source.begin(), source.end(), x_f) != source.end();
            bool right = std::find(target.begin(), target.end(), x_f.arg()) != target.end();
            return left == right;
        };

        auto u_satisfy = [&](const Formula &u_f)
        {
            bool left = std::find(source.begin(), source.end(), u_f) != source.end();
            bool right = std::find(source.begin(), source.end(), u_f.rhs()) != source.end() ||
                         (std::find(target.begin(), target.end(), u_f) != target.end() && std::find(source.begin(), source.end(), u_f.lhs()) != source.end());
            return left == right;
        };

        return std::all_of(x_formulas.begin(), x_formulas.end(), x_satisfy) &&
               std::all_of(u_formulas.begin(), u_formulas.end(), u_satisfy);
    }

    Transitions Translator::get_transitions(const StateVec &states, const FormulaSet &closure)
    {
        FormulaVec x_formulas, u_formulas;

        std::copy_if(closure.begin(), closure.end(), std::back_inserter(x_formulas),
                     [](const Formula &f)
                     { return f.kind() == Formula::X; });

        std::copy_if(closure.begin(), closure.end(), std::back_inserter(u_formulas),
                     [](const Formula &f)
                     { return f.kind() == Formula::U; });

        Transitions transitions;

        size_t source_ind = 0;
        for (const auto &source : states)
        {
            source_ind++;
            size_t target_ind = 0;
            for (const auto &target : states)
            {
                target_ind++;
                if (is_satisfyied(u_formulas, x_formulas, source, target))
                {
                    transitions.push_back({get_state_name(source_ind), get_symbol(source), get_state_name(target_ind)});
                }
            }
        }
        return transitions;
    }

    const Automaton Translator::get_automaton(const StateVec &states, const States &initials, const FinalStates &finals, const Transitions &transitions)
    {
        Automaton automaton;

        size_t current_ind = 1;
        std::for_each(states.begin(), states.end(), [&](const auto &)
                      { automaton.add_state(get_state_name(current_ind++)); });

        std::for_each(initials.begin(), initials.end(), [&](const auto &s)
                      { automaton.set_initial(s); });

        size_t final_ind = 0;
        std::for_each(finals.begin(), finals.end(), [&](const auto &final)
                      {
        std::for_each(final.begin(), final.end(), [&](const auto &s) {
            automaton.set_final(final_ind, s);
        });
        ++final_ind; });

        std::for_each(transitions.begin(), transitions.end(), [&](const auto &t)
                      { automaton.add_trans(std::get<0>(t), std::get<1>(t), std::get<2>(t)); });

        return automaton;
    }

    const Automaton Translator::translate(const Formula &formula)
    {
        const Formula &simplified = simplify(formula);

        // get closure with negation
        FormulaSet closure_set = get_closure(simplified);
        FormulaSet closure;
        closure.insert(closure_set.begin(), closure_set.end());
        std::transform(closure_set.begin(), closure_set.end(), std::inserter(closure, closure.end()),
                       [](const Formula &f)
                       { return !f; });

        StateVec states = get_states(closure);

        States initials = get_initials(states, simplified);
        FinalStates finals = get_finals(states, simplified, closure);
        Transitions transitions = get_transitions(states, closure);

        return get_automaton(states, initials, finals, transitions);
    }
} // namespace model::translator
