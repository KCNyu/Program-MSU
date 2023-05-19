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
    Var Solver::choose(const CNF &cnf)
    {
        size_t min_clause_size = std::numeric_limits<size_t>::max();
        int min_clause_index = -1;

        for (int i = 0; i < cnf._clauses.size(); i++)
        {
            if (cnf._clauses[i].second != UNDEF)
            {
                continue;
            }

            size_t clause_size = cnf._clauses[i].first.size();
            if (clause_size > 0 && clause_size < min_clause_size)
            {
                min_clause_size = clause_size;
                min_clause_index = i;
            }
        }

        return {abs(cnf._clauses[min_clause_index].first[0]), TRUE};
    }
    bool Solver::solve()
    {
        std::stack<std::shared_ptr<CNF>> cnf_stack;
        cnf_stack.push(std::make_shared<CNF>(_cnf));

        while (!cnf_stack.empty())
        {
            std::shared_ptr<CNF> cnf = cnf_stack.top();
            cnf_stack.pop();

            Boolean result = propagate(*cnf);
            if (result == TRUE)
            {
                return true;
            }
            else if (result == FALSE)
            {
                continue;
            }
            Var var = choose(*cnf);
            for (int i = 0; i < 2; i++)
            {
                std::shared_ptr<CNF> new_cnf = std::make_shared<CNF>(*cnf);

                if (i == 1)
                {
                    var.second = FALSE;
                }

                result = apply(*new_cnf, var);
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
