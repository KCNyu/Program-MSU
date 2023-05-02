#include "translator.hpp"

namespace model::translator
{
    using namespace model::ltl;

    const Formula Translator::simplify(const Formula &formula)
    {
        switch (formula.kind())
        {
        case Formula::ATOM:
        {
            return P(formula.prop());
        }
        case Formula::NOT:
        {
            return !simplify(formula.lhs());
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
    const fsm::Automaton Translator::translate(const Formula &formula)
    {
        std::cout << "Translating formula: " << formula << std::endl;
        std::cout << "Simplified formula: " << simplify(formula) << std::endl;
        return fsm::Automaton();
    }
} // namespace model::translator
