/*
 * Copyright 2021 ISP RAS (http://www.ispras.ru)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */

#include "bdd.h"

namespace model::bdd
{

    const Node Bdd::zero(-1, nullptr, nullptr);
    const Node Bdd::one(-1, nullptr, nullptr);

    std::ostream &operator<<(std::ostream &out, const Node &node)
    {
        static int level = 0;
        std::string indent(level, '\t');
        std::string branch = indent + (level > 0 ? "|-" : "");

        if (&node == &Bdd::zero)
        {
            out << branch << "[zero]\n";
            return out;
        }
        if (&node == &Bdd::one)
        {
            out << branch << "[one]\n";
            return out;
        }

        out << branch << "Node(" << node.var << ")\n";

        if (node.low)
        {
            out << indent << "|-Low:\n";
            ++level;
            out << *(node.low);
            --level;
        }
        if (node.high)
        {
            out << indent << "|-High:\n";
            ++level;
            out << *(node.high);
            --level;
        }

        return out;
    }

    const bool Bdd::value(const Formula &formula)
    {
        switch (formula.kind())
        {
        case Formula::FALSE:
        {
            return false;
        }
        case Formula::TRUE:
        {
            return true;
        }
        case Formula::NOT:
        {
            return !value(formula.arg());
        }
        case Formula::AND:
        {
            return value(formula.lhs()) && value(formula.rhs());
        }
        case Formula::OR:
        {
            return value(formula.lhs()) || value(formula.rhs());
        }
        case Formula::XOR:
        {
            return value(formula.lhs()) != value(formula.rhs());
        }
        case Formula::IMPL:
        {
            return !value(formula.lhs()) || value(formula.rhs());
        }
        case Formula::EQ:
        {
            return value(formula.lhs()) == value(formula.rhs());
        }
        case Formula::VAR: // Should not happen
        default:
        {
            std::cerr << "Error: unexpected formula kind" << std::endl;
            exit(1);
        }
        }
    }
    const Formula &Bdd::apply_var(const Formula &formula, const Var &var)
    {
        switch (formula.kind())
        {
        case Formula::FALSE:
        {
            return Formula::F;
        }
        case Formula::TRUE:
        {
            return Formula::T;
        }
        case Formula::VAR:
        {
            if (formula.var() == var.first)
            {
                return var.second ? Formula::T : Formula::F;
            }
            else
            {
                return formula;
            }
        }
        case Formula::NOT:
        {
            return !apply_var(formula.arg(), var);
        }
        case Formula::AND:
        {
            return apply_var(formula.lhs(), var) && apply_var(formula.rhs(), var);
        }
        case Formula::OR:
        {
            return apply_var(formula.lhs(), var) || apply_var(formula.rhs(), var);
        }
        case Formula::XOR:
        {
            return apply_var(formula.lhs(), var) != apply_var(formula.rhs(), var);
        }
        case Formula::IMPL:
        {
            return !apply_var(formula.lhs(), var) || apply_var(formula.rhs(), var);
        }
        case Formula::EQ:
        {
            return apply_var(formula.lhs(), var) == apply_var(formula.rhs(), var);
        }
        default:
            return formula;
        }
    }

    const int Bdd::root(const Formula &formula)
    {
        switch (formula.kind())
        {
        // should be the leaves in the tree
        case Formula::FALSE:
        case Formula::TRUE:
        {
            return INT_MAX;
        }
        case Formula::VAR:
        {
            return formula.var();
        }
        case Formula::NOT:
        {
            return root(formula.arg());
        }
        case Formula::AND:
        case Formula::OR:
        case Formula::XOR:
        case Formula::IMPL:
        case Formula::EQ:
        {
            return std::min(root(formula.lhs()), root(formula.rhs()));
        }
        default:
            return 0;
        }
    }

    const Node &Bdd::create(const Formula &formula)
    {
        if (formula.kind() == Formula::FALSE)
        {
            return Bdd::zero;
        }
        else if (formula.kind() == Formula::TRUE)
        {
            return Bdd::one;
        }
        else if (formula.kind() == Formula::VAR)
        {
            return createNode(formula.var(), &Bdd::zero, &Bdd::one);
        }

        int var = root(formula);
        if (var == INT_MAX)
        {
            return value(formula) ? Bdd::one : Bdd::zero;
        }

        const Node &low = create(apply_var(formula, Var(var, false)));
        const Node &high = create(apply_var(formula, Var(var, true)));

        if (&low == &high)
        {
            return low;
        }
        else
        {
            return createNode(var, &low, &high);
        }
    }
    const Node &Bdd::createNode(int var, const Node *low, const Node *high)
    {
        auto nodeKey = std::make_tuple(var, low, high);
        if (nodePool.find(nodeKey) != nodePool.end())
        {
            return nodePool[nodeKey];
        }

        Node node(var, low, high);
        nodePool[nodeKey] = node;
        return nodePool[nodeKey];
    }

} // namespace model::bdd
