#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <memory>

namespace model::dpll
{
    enum Boolean
    {
        TRUE,
        FALSE,
        UNDEF
    };
    using Clause = std::pair<std::vector<int>, Boolean>;
    using Var = std::pair<int, Boolean>;

    class CNF
    {
    private:
        std::vector<int> parse_clause(const std::string &line)
        {
            std::vector<int> clause;
            std::istringstream iss(line);
            int literal;
            while (iss >> literal && literal != 0)
            {
                clause.push_back(literal);
            }
            return clause;
        }

    public:
        std::vector<Clause> _clauses;

        int num_variables;
        int num_clauses;

        CNF(const std::string &filename);
        bool is_satisfied()
        {
            return std::all_of(_clauses.begin(), _clauses.end(), [](const Clause &clause)
                               { return clause.second == TRUE; });
        }
    };
    class Solver
    {
    private:
        CNF _cnf;
        Boolean propagate(CNF &cnf);

    protected:
        Var choose(const CNF &cnf);
        Boolean apply(CNF &cnf, const Var &var);

    public:
        Solver(const std::string &filename) : _cnf(filename) {}
        bool solve();
    };
}; // namespace model::dpll