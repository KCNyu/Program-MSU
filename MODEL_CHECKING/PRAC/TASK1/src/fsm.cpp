#include "fsm.hpp"

namespace model::fsm
{
    std::ostream &operator<<(std::ostream &out, const State &state)
    {
        return out << state.label();
    }

    std::ostream &operator<<(std::ostream &out, const Transition &transition)
    {
        out << transition.source();
        out << " --[";

        bool separator = false;
        for (auto i = transition.symbol().begin(); i != transition.symbol().end(); i++)
        {
            out << (separator ? ", " : "") << *i;
            separator = true;
        }

        out << "]--> ";
        out << transition.target();

        return out;
    }
    std::ostream &operator<<(std::ostream &out, const Automaton &automaton)
    {
        bool separator;

        out << "S0 = {";
        separator = false;
        for (const auto &state : automaton._initial_states)
        {
            out << (separator ? ", " : "") << state;
        }
        out << "}" << std::endl;

        for (const auto &entry : automaton._final_states)
        {
            out << "F" << entry.first << " = {";
            separator = false;
            for (const auto &state : entry.second)
            {
                out << (separator ? ", " : "") << state;
            }
            out << "}" << std::endl;
        }

        out << "T = {" << std::endl;
        separator = false;
        for (const auto &entry : automaton._transitions)
        {
            for (const auto &transition : entry.second)
            {
                out << (separator ? "\n" : "") << "  " << transition;
                separator = true;
            }
        }
        out << std::endl
            << "}";

        return out;
    }
} // namespace model::fsm
