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
            return X(simplify(formula.lhs()));
        }
        case Formula::G:
        {
            return !(U(TRUE(), !simplify(formula.lhs())));
        }
        case Formula::F:
        {
            return U(TRUE(), simplify(formula.lhs()));
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
            closure_set = get_closure(formula.arg());
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
    AtomMap Translator::get_atoms(const FormulaSet &closure)
    {
        AtomMap atoms;
        for (const auto &elem : closure)
        {
            std::cout << elem << std::endl;
            if (elem.kind() == Formula::ATOM || elem.kind() == Formula::X)
            {
                if (elem.kind() == Formula::ATOM && elem.prop() == "true")
                {
                    continue;
                }
                atoms.insert({elem.prop(), false});
            }
        }
        return atoms;
    }
    // FormulaMap Translator::get_true_closure_formulas(FormulaSet &closure, AtomMap &atoms)
    // {
    //     FormulaMap true_formulas;
    //     for (const auto &closure_elem : closure)
    //     {
    //         if (closure_elem(atoms) == Formula::TRUE)
    //         {
    //             true_formulas.insert({closure_elem.prop(), closure_elem});
    //         }
    //     }
    //     return true_formulas;
    // }

    // std::map<std::string, FormulaMap> get_states_for_atoms_values(const std::vector<Formula> &closure, size_t &states_number, const FormulaMap &true_formulas)
    // {
    //     std::map<std::string, FormulaMap> local_states;
    //     local_states.insert({"s" + std::to_string(states_number++), true_formulas});

    //     for (const auto &closure_elem : closure)
    //     {
    //         std::map<std::string, FormulaMap> additional_states;
    //         for (auto &local_state : local_states)
    //         {
    //             if (local_state.second.find(closure_elem.prop()) != local_state.second.end())
    //                 continue;

    //             // Handle U (Until) case
    //             if (closure_elem.kind() == Formula::U)
    //             {
    //                 handle_until_case(closure_elem, local_state, additional_states, states_number);
    //                 continue;
    //             }

    //             auto closure_elem_value = closure_elem(local_state.second);
    //             if (closure_elem_value == Formula::TRUE)
    //             {
    //                 local_state.second.insert({closure_elem.prop(), closure_elem});
    //             }
    //         }
    //         local_states.insert(additional_states.begin(), additional_states.end());
    //     }
    //     return local_states;
    // }

    // void handle_until_case(const Formula &closure_elem, std::pair<const std::string, FormulaMap> &local_state, std::map<std::string, FormulaMap> &additional_states, size_t &states_number)
    // {
    //     if (local_state.second.find(closure_elem.rhs().prop()) != local_state.second.end())
    //     {
    //         local_state.second.insert({closure_elem.prop(), closure_elem});
    //     }
    //     else if (local_state.second.find(closure_elem.lhs().prop()) != local_state.second.end())
    //     {
    //         auto new_state_name = "s" + std::to_string(states_number++);
    //         additional_states.insert({new_state_name, local_state.second});
    //         additional_states[new_state_name].insert({closure_elem.prop(), closure_elem});
    //         auto neg_until = !closure_elem;
    //         local_state.second.insert({neg_until.prop(), neg_until});
    //     }
    //     else
    //     {
    //         auto neg_until = !closure_elem;
    //         local_state.second.insert({neg_until.prop(), neg_until});
    //     }
    // }
    StateMap Translator::get_states(const FormulaSet &closure)
    {
        AtomMap atoms = get_atoms(closure);
        std::cout << "Atoms:" << std::endl;
        for (const auto &atom : atoms)
        {
            std::cout << atom.first << " " << atom.second << std::endl;
        }
        size_t rows_number = 1 << atoms.size();

        auto generate_permutations = [](const AtomMap &atoms)
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
        };

        std::vector<AtomMap> atoms_permutations = generate_permutations(atoms);
        for (const auto &ap : atoms_permutations)
        {
            for (const auto &a : ap)
            {
                std::cout << a.first << " " << a.second << " ";
            }
            std::cout << std::endl;
        }

        // // Transform atoms_values permutations into corresponding states.
        // std::vector<std::map<std::string, FormulaMap>> local_states_vector;
        // local_states_vector.reserve(rows_number);
        // size_t states_number = 1;
        // std::transform(atoms_permutations.begin(), atoms_permutations.end(), std::back_inserter(local_states_vector), [&](const auto &av)
        //                {
        // FormulaMap true_formulas = get_true_closure_formulas(closure, av);
        // return get_states_for_atoms_values(closure, states_number, true_formulas); });

        // Merge all the local_states into a single states map.
        StateMap states;
        // for (const auto &local_states : local_states_vector)
        // {
        //     states.insert(local_states.begin(), local_states.end());
        // }

        return states;
    }
    const Automaton Translator::translate(const Formula &formula)
    {
        const Formula &simplified = simplify(formula);

        std::cout << "Translating formula: " << formula << std::endl;
        std::cout << "Simplified formula: " << simplified << std::endl;

        FormulaSet closure = get_closure(simplified);
        std::transform(closure.begin(), closure.end(), std::inserter(closure, closure.end()),
                       [](const Formula &f)
                       { return !f; });

        StateMap states = get_states(closure);
        return Automaton();
    }
} // namespace model::translator
