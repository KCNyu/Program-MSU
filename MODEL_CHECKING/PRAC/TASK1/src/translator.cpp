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
        std::vector<AtomMap> permutations;
        size_t rows_number = 1 << atoms.size();
        permutations.reserve(rows_number);

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
                atoms.insert({elem.prop(), false});
            }
        }
        return get_permuation_atoms(atoms);
    }
    std::optional<bool> caculate(const Formula &formula, const AtomMap &atoms)
    {
        using OpFunc = std::function<std::optional<bool>(const Formula &, const AtomMap &)>;

        std::unordered_map<Formula::Kind, OpFunc> operations = {
            {Formula::ATOM, [](const Formula &formula, const AtomMap &atoms) -> std::optional<bool>
             {
                 if (formula.prop() == "true")
                     return true;
                 if (formula.prop() == "false")
                     return false;
                 return atoms.at(formula.prop());
             }},
            {Formula::X, [](const Formula &formula, const AtomMap &atoms) -> std::optional<bool>
             {
                 return atoms.at(formula.prop());
             }},
            {Formula::NOT, [](const Formula &formula, const AtomMap &atoms) -> std::optional<bool>
             {
                 auto arg_result = caculate(formula.lhs(), atoms);
                 return arg_result.has_value() ? std::optional<bool>(!*arg_result) : std::nullopt;
             }},
            {Formula::AND, [](const Formula &formula, const AtomMap &atoms) -> std::optional<bool>
             {
                 auto lhs_result = caculate(formula.lhs(), atoms);
                 auto rhs_result = caculate(formula.rhs(), atoms);
                 if (!lhs_result.has_value() || !rhs_result.has_value())
                     return std::nullopt;
                 return std::optional<bool>(*lhs_result && *rhs_result);
             }},
            {Formula::OR, [](const Formula &formula, const AtomMap &atoms) -> std::optional<bool>
             {
                 auto lhs_result = caculate(formula.lhs(), atoms);
                 auto rhs_result = caculate(formula.rhs(), atoms);
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
    std::optional<bool> caculate(const Formula &formula, const FormulaMap &formulas)
    {
        using OpFunc = std::function<std::optional<bool>(const Formula &, const FormulaMap &)>;

        std::unordered_map<Formula::Kind, OpFunc> operations = {
            {Formula::ATOM, [](const Formula &formula, const FormulaMap &formulas) -> std::optional<bool>
             {
                 return formulas.find(formula.prop()) != formulas.end();
             }},
            {Formula::X, [](const Formula &formula, const FormulaMap &formulas) -> std::optional<bool>
             {
                 return formulas.find(formula.prop()) != formulas.end();
             }},
            {Formula::NOT, [](const Formula &formula, const FormulaMap &formulas) -> std::optional<bool>
             {
                 if (formulas.find(formula.prop()) != formulas.end())
                     return true;
                 auto arg_result = caculate(formula.arg(), formulas);
                 if (arg_result.has_value())
                     return !*arg_result;
                 return std::nullopt;
             }},
            {Formula::AND, [](const Formula &formula, const FormulaMap &formulas) -> std::optional<bool>
             {
                 if (formulas.find(formula.prop()) != formulas.end())
                     return true;
                 auto lhs_result = caculate(formula.lhs(), formulas);
                 auto rhs_result = caculate(formula.rhs(), formulas);
                 if (!lhs_result.has_value() || !rhs_result.has_value())
                     return std::nullopt;
                 return std::optional<bool>(*lhs_result && *rhs_result);
             }},
            {Formula::OR, [](const Formula &formula, const FormulaMap &formulas) -> std::optional<bool>
             {
                 if (formulas.find(formula.prop()) != formulas.end())
                     return true;
                 auto lhs_result = caculate(formula.lhs(), formulas);
                 auto rhs_result = caculate(formula.rhs(), formulas);
                 if (!lhs_result.has_value() || !rhs_result.has_value())
                     return std::nullopt;
                 return std::optional<bool>(*lhs_result || *rhs_result);
             }}};

        auto it = operations.find(formula.kind());
        if (it != operations.end())
        {
            return it->second(formula, formulas);
        }

        return std::nullopt;
    }
    FormulaMap Translator::get_classic(const FormulaSet &closure, const AtomMap &atoms)
    {
        FormulaMap classic;
        for (const auto &elem : closure)
        {
            if (caculate(elem, atoms).value_or(false))
            {
                classic.insert({elem.prop(), elem});
            }
        }
        return classic;
    }

    StateMap Translator::get_local_states(const FormulaSet &closure, size_t &states_number, const FormulaMap &true_formulas)
    {
        StateMap local_states;
        local_states.insert({"s" + std::to_string(states_number++), true_formulas});

        for (const auto &elem : closure)
        {
            StateMap additional_states;
            for (auto &local_state : local_states)
            {
                if (local_state.second.find(elem.prop()) != local_state.second.end())
                    continue;

                if (elem.kind() == Formula::U)
                {
                    handle_until_case(elem, local_state, additional_states, states_number);
                    continue;
                }

                auto closure_elem_value = caculate(elem, local_state.second);
                if (closure_elem_value.value_or(false))
                {
                    local_state.second.insert({elem.prop(), elem});
                }
            }
            local_states.insert(additional_states.begin(), additional_states.end());
        }
        return local_states;
    }

    void Translator::handle_until_case(const Formula &closure_elem, State &local_state, StateMap &additional_states, size_t &states_number)
    {
        if (local_state.second.find(closure_elem.rhs().prop()) != local_state.second.end())
        {
            local_state.second.insert({closure_elem.prop(), closure_elem});
        }
        else if (local_state.second.find(closure_elem.lhs().prop()) != local_state.second.end())
        {
            auto new_state_name = "s" + std::to_string(states_number++);
            additional_states.insert({new_state_name, local_state.second});
            additional_states[new_state_name].insert({closure_elem.prop(), closure_elem});
            auto neg_until = !closure_elem;
            local_state.second.insert({neg_until.prop(), neg_until});
        }
        else
        {
            auto neg_until = !closure_elem;
            local_state.second.insert({neg_until.prop(), neg_until});
        }
    }
    StateMap Translator::get_states(const FormulaSet &closure)
    {
        AtomPermutation atoms = get_atoms(closure);
        // StateMap states;

        // size_t states_number = 1;
        // for (auto &atom : atoms)
        // {
        //     FormulaMap classic = get_classic(closure, atom);
        //     std::cout << "-------------------" << std::endl;
        //     for (const auto &elem : classic)
        //     {
        //         std ::cout << elem.first << " " << elem.second << std::endl;
        //     }
        //     std::cout << "-------------------" << std::endl;
        //     StateMap local_states = get_local_states(closure, states_number, classic);

        //     for (const auto &local_state : local_states)
        //     {
        //         states.insert({local_state.first, local_state.second});
        //     }
        // }
        // Transform atoms_values permutations into corresponding states.
        std::vector<StateMap> local_states_vector;
        local_states_vector.reserve(atoms.size() * atoms.size());
        size_t states_number = 1;
        std::transform(atoms.begin(), atoms.end(), std::back_inserter(local_states_vector), [&](const auto &av)
                       {
        FormulaMap classic = get_classic(closure, av);
        return get_local_states(closure, states_number, classic); });

        StateMap states;
        for (const auto &local_states : local_states_vector)
        {
            states.insert(local_states.begin(), local_states.end());
        }

        return states;
    }
    States Translator::get_initials(const StateMap &states, const Formula &f)
    {
        std::vector<std::string> initials;
        for (const auto &state : states)
        {
            if (state.second.find(f.prop()) != state.second.end())
                initials.push_back(state.first);
        }

        return initials;
    }
    FinalStates Translator::get_finals(const StateMap &states, const Formula &f, const FormulaSet &closure)
    {
        FinalStates final_states;
        std::map<int, Formula> u_formulas;
        size_t current_ind = 0;
        for (const auto &f_closure : closure)
        {
            if (f_closure.kind() == Formula::U)
            {
                u_formulas.insert({current_ind, f_closure});
                current_ind++;
            }
        }

        for (const auto &u_formula : u_formulas)
        {
            std::vector<std::string> final_statest_subset;
            for (const auto &state : states)
            {
                if (state.second.find(u_formula.second.prop()) == state.second.end() ||
                    state.second.find(u_formula.second.rhs().prop()) != state.second.end())
                {
                    final_statest_subset.push_back(state.first);
                }
            }
            final_states.insert({u_formula.first, final_statest_subset});
        }

        return final_states;
    }

    std::set<std::string> get_symbol(const std::map<std::string, Formula> &state)
    {
        std::set<std::string> symbol;
        for (const auto &f_state : state)
        {
            if (f_state.second.kind() == Formula::ATOM &&
                f_state.second.prop() != "true" && f_state.second.prop() != "false")
                symbol.insert(f_state.first);
        }
        return symbol;
    }

    bool check_obligations(const std::vector<Formula> &u_formulas,
                           const std::vector<Formula> &x_formulas,
                           const std::map<std::string, Formula> &state_from,
                           const std::map<std::string, Formula> &state_to)
    {
        for (const auto &x_f : x_formulas)
        {
            if ((state_from.find(x_f.prop()) == state_from.end()) != (state_to.find(x_f.lhs().prop()) == state_to.end()))
                return false;
        }
        for (const auto &u_f : u_formulas)
        {
            if (not((state_from.find(u_f.prop()) != state_from.end()) ==
                    ((state_from.find(u_f.rhs().prop()) != state_from.end()) || ((state_from.find(u_f.lhs().prop()) != state_from.end()) &&
                                                                                 (state_to.find(u_f.prop()) != state_to.end())))))
                return false;
        }
        return true;
    }

    std::vector<std::tuple<std::string, std::set<std::string>, std::string>>
    make_transitions(const std::map<std::string, std::map<std::string, Formula>> &states,
                     const FormulaSet &closure)
    {
        std::vector<std::tuple<std::string, std::set<std::string>, std::string>> transitions;
        std::vector<Formula> u_formulas, x_formulas;

        // find all functions with U and X
        for (const auto &f_closure : closure)
        {
            if (f_closure.kind() == Formula::U)
                u_formulas.push_back(f_closure);
            if (f_closure.kind() == Formula::X)
                x_formulas.push_back(f_closure);
        }

        for (const auto &state_from : states)
        {
            auto symbol = get_symbol(state_from.second);
            for (const auto &state_to : states)
            {
                if (check_obligations(u_formulas, x_formulas, state_from.second, state_to.second))
                {
                    transitions.emplace_back(state_from.first, symbol, state_to.first);
                }
            }
        }

        return transitions;
    }

    const Automaton Translator::translate(const Formula &formula)
    {
        const Formula &simplified = simplify(formula);

        std::cout << "Translating formula: " << formula << std::endl;
        std::cout << "Simplified formula: " << simplified << std::endl;

        FormulaSet closure_set = get_closure(simplified);
        FormulaSet closure;
        closure.reserve(closure_set.size() * 2);
        closure.insert(closure_set.begin(), closure_set.end());
        std::transform(closure_set.begin(), closure_set.end(), std::inserter(closure, closure.end()),
                       [](const Formula &f)
                       { return !f; });

        StateMap states = get_states(closure);

        std::cout << "States:" << std::endl;
        for (const auto &state : states)
        {
            std::cout << state.first << ": ";
            for (const auto &formulas : state.second)
            {
                std::cout << formulas.first << ", ";
            }
            std::cout << std::endl;
        }

        States initials = get_initials(states, simplified);
        std::cout << "Initials: ";
        for (const auto &initial : initials)
        {
            std::cout << initial << ", ";
        }
        std::cout << std::endl;

        FinalStates finals = get_finals(states, simplified, closure);
        std::cout << "Finals: " << std::endl;
        for (const auto &final : finals)
        {
            std::cout << final.first << ": ";
            for (const auto &final_state : final.second)
            {
                std::cout << final_state << ", ";
            }
            std::cout << std::endl;
        }
        auto transitions = make_transitions(states, closure);

        Automaton automaton;
        for (const auto &s : states)
        {
            automaton.add_state(s.first);
        }
        for (const auto &s : initials)
        {
            automaton.set_initial(s);
        }
        for (const auto &f_subset : finals)
        {
            for (const auto &s : f_subset.second)
            {
                automaton.set_final(f_subset.first, s);
            }
        }
        for (const auto &t : transitions)
        {
            automaton.add_trans(std::get<0>(t), std::get<1>(t), std::get<2>(t));
        }
        // std::cout << "Automaton: " << std::endl;
        // std::cout << automaton << std::endl;
        return automaton;
    }
} // namespace model::translator
