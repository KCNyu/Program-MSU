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
    Boolean Solver::propagate(CNF &cnf)
    {
        auto find_unit_clause = [](auto &clauses)
        {
            return std::find_if(clauses.begin(), clauses.end(), [](auto &clause)
                                { return clause.second == UNDEF && clause.first.size() == 1; });
        };

        auto unit_clause_iter = find_unit_clause(cnf._clauses);
        while (unit_clause_iter != cnf._clauses.end())
        {
            int literal = unit_clause_iter->first[0];
            unit_clause_iter->second = TRUE;

            Boolean result = apply(cnf, {std::abs(literal), literal > 0 ? TRUE : FALSE});
            if (result == TRUE || result == FALSE)
            {
                return result;
            }
            unit_clause_iter = find_unit_clause(cnf._clauses);
        }

        return cnf.is_satisfied() ? TRUE : UNDEF;
    }
    Boolean Solver::apply(CNF &cnf, const Var &var)
    {
        for (auto &clause : cnf._clauses)
        {
            if (clause.second != UNDEF)
            {
                continue;
            }
            for (auto &literal : clause.first)
            {
                if (literal == var.first)
                {
                    if (var.second == FALSE)
                    {
                        clause.first.erase(std::remove(clause.first.begin(), clause.first.end(), literal), clause.first.end());

                        if (clause.first.empty())
                        {
                            return FALSE;
                        }
                        break;
                    }
                    clause.second = TRUE;
                    if (cnf.is_satisfied())
                    {
                        return TRUE;
                    }
                    break;
                }
                else if (literal == -var.first)
                {
                    if (var.second == TRUE)
                    {
                        clause.first.erase(std::remove(clause.first.begin(), clause.first.end(), literal), clause.first.end());
                        if (clause.first.empty())
                        {
                            return FALSE;
                        }
                        break;
                    }
                    clause.second = TRUE;
                    if (cnf.is_satisfied())
                    {
                        return TRUE;
                    }
                    break;
                }
            }
        }
        return UNDEF;
    }
    bool Solver::solve()
    {
        std::stack<CNF> cnf_stack;
        cnf_stack.push(_cnf);

        while (!cnf_stack.empty())
        {
            CNF cnf = cnf_stack.top();
            cnf_stack.pop();

            Boolean result = propagate(cnf);
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
                CNF new_cnf = cnf;
                Var var;
                for (const auto &clause : new_cnf._clauses)
                {
                    if (clause.second != UNDEF)
                    {
                        continue;
                    }
                    for (const auto &literal : clause.first)
                    {
                        var = {std::abs(literal), i == 0 ? TRUE : FALSE};
                    }
                }
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
            }
        }

        return false;
    }
};
