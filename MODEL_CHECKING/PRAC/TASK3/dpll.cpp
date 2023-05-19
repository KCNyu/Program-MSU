#include "dpll.hpp"
namespace model::dpll
{
    CNF::CNF(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            throw std::runtime_error("Could not open file");
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (!line.empty() && (line[0] == 'c' || line[0] == '0'))
            {
                continue;
            }
            else if (line[0] == 'p')
            {
                std::istringstream iss(line);
                std::string tmp;
                if (!(iss >> tmp >> tmp >> num_variables >> num_clauses))
                {
                    throw std::runtime_error("Failed to read the problem specification");
                }
            }
            else if (!line.empty() && line[0] != '%')
            {
                _clauses.push_back({parse_clause(line), UNDEF});
            }
        }
    }
    Boolean Solver::propagate()
    {
        auto find_unit_clause = [](auto &clauses)
        {
            return std::find_if(clauses.begin(), clauses.end(), [](auto &clause)
                                { return clause.second == UNDEF && clause.first.size() == 1; });
        };

        auto unit_clause_iter = find_unit_clause(_cnf._clauses);
        while (unit_clause_iter != _cnf._clauses.end())
        {
            int literal = unit_clause_iter->first[0];
            unit_clause_iter->second = TRUE;

            Boolean result = apply(_cnf, {std::abs(literal), literal > 0 ? TRUE : FALSE});
            if (result == TRUE || result == FALSE)
            {
                return result;
            }
            unit_clause_iter = find_unit_clause(_cnf._clauses);
        }

        return _cnf.is_satisfied() ? TRUE : UNDEF;
    }
    Boolean Solver::apply(CNF &cnf, const Var &var)
    {
        for (auto &clause : cnf._clauses)
        {
            if (clause.second != UNDEF)
            {
                continue;
            }

            auto literal_it = std::find_if(clause.first.begin(), clause.first.end(),
                                           [&var](const auto &literal)
                                           { return literal == var.first || literal == -var.first; });

            if (literal_it != clause.first.end())
            {
                if ((*literal_it == var.first && var.second == FALSE) ||
                    (*literal_it == -var.first && var.second == TRUE))
                {
                    clause.first.erase(literal_it);
                    if (clause.first.empty())
                    {
                        return FALSE;
                    }
                }
                else
                {
                    clause.second = TRUE;
                    if (cnf.is_satisfied())
                    {
                        return TRUE;
                    }
                }
            }
        }

        return UNDEF;
    }
    Var Solver::choose(const CNF &cnf, const int &index)
    {
        std::map<int, int> literal_count;
        for (auto &clause : cnf._clauses)
        {
            if (clause.second != UNDEF)
            {
                continue;
            }

            for (auto &literal : clause.first)
            {
                literal_count[std::abs(literal)]++;
            }
        }

        auto max_literal = std::max_element(literal_count.begin(), literal_count.end(),
                                            [](const auto &a, const auto &b)
                                            { return a.second < b.second; });

        return {max_literal->first, index == 0 ? TRUE : FALSE};
    }
    bool Solver::solve()
    {
        std::stack<CNF> cnf_stack;
        cnf_stack.push(_cnf);

        while (!cnf_stack.empty())
        {
            _cnf = cnf_stack.top();
            cnf_stack.pop();

            Boolean result = propagate();
            if (result == TRUE)
            {
                return true;
            }
            else if (result == FALSE)
            {
                continue;
            }

            for (int i = 0; i < 2; i++)
            {
                CNF new_cnf = _cnf;
                Var var = choose(new_cnf, i);
                // std::cout << "Trying " << var.first << " = " << var.second << std::endl;

                result = apply(new_cnf, var);
                if (result == TRUE)
                {
                    return true;
                }
                else if (result == FALSE)
                {
                    continue;
                }
                cnf_stack.push(new_cnf);
                // std::cout << cnf_stack.size() << std::endl;
            }
        }

        return false;
    }
};
