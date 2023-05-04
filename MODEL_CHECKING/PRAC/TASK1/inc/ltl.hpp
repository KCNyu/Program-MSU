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

#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace model::ltl
{

    class Formula final
    {
    public:
        enum Kind
        {
            ATOM, // Atomic proposition: p
            NOT,  // Negation: ~A
            AND,  // Conjunction: (A1 & A2)
            OR,   // Disjunction: (A1 | A2)
            IMPL, // Implication: (A1 -> A2)
            X,    // NeXt time: X{A}
            G,    // Globally: G{A}
            F,    // In the Future: F{A}
            U,    // Until: (A1 U A2)
            R     // Release: (A1 R A2)
        };

        const Formula &operator!() const;
        const Formula &operator&&(const Formula &rhs) const;
        const Formula &operator||(const Formula &rhs) const;
        const Formula &operator>>(const Formula &rhs) const;
        bool operator==(const Formula &other) const
        {
            if (_kind != other._kind)
            {
                return false;
            }
            if (_prop != other._prop)
            {
                return false;
            }
            if ((_lhs == nullptr) != (other._lhs == nullptr))
            {
                return false;
            }
            if (_lhs != nullptr && !(*_lhs == *other._lhs))
            {
                return false;
            }
            if ((_rhs == nullptr) != (other._rhs == nullptr))
            {
                return false;
            }
            if (_rhs != nullptr && !(*_rhs == *other._rhs))
            {
                return false;
            }
            return true;
        }

        friend const Formula &P(const std::string &prop);
        friend const Formula &X(const Formula &arg);
        friend const Formula &G(const Formula &arg);
        friend const Formula &F(const Formula &arg);
        friend const Formula &U(const Formula &lhs, const Formula &rhs);
        friend const Formula &R(const Formula &lhs, const Formula &rhs);
        friend const Formula &TRUE();

        Kind kind() const { return _kind; }
        std::string prop() const { return _prop; }

        const Formula &arg() const { return *_lhs; }
        const Formula &lhs() const { return *_lhs; }
        const Formula &rhs() const { return *_rhs; }

        size_t hash() const
        {
            std::hash<std::string> string_hasher;
            size_t h = 0;
            h ^= static_cast<size_t>(_kind) << 1;
            h ^= string_hasher(_prop) << 2;
            h ^= std::hash<const Formula *>{}(_lhs) << 3;
            h ^= std::hash<const Formula *>{}(_rhs) << 4;
            return h;
        }

    private:
        Formula(Kind kind, const std::string &prop, const Formula *lhs, const Formula *rhs) : _kind(kind), _prop(prop), _lhs(lhs), _rhs(rhs) {}

        Formula(const std::string &prop) : Formula(ATOM, prop, nullptr, nullptr) {}

        Formula(Kind kind, const Formula *arg) : Formula(kind, "", arg, nullptr) {}

        Formula(Kind kind, const std::string &prop, const Formula *arg) : Formula(kind, prop, arg, nullptr) {}

        Formula(Kind kind, const Formula *lhs, const Formula *rhs) : Formula(kind, "", lhs, rhs) {}

        static const Formula &alloc(const Formula *formula)
        {
            _formulae.push_back(std::unique_ptr<const Formula>(formula));
            return *formula;
        }

        static std::vector<std::unique_ptr<const Formula>> _formulae;

        const Kind _kind;
        const std::string _prop;
        const Formula *_lhs;
        const Formula *_rhs;
    };

    inline const Formula &Formula::operator!() const
    {
        return alloc(new Formula(NOT, this));
    }

    inline const Formula &Formula::operator&&(const Formula &rhs) const
    {
        return alloc(new Formula(AND, this, &rhs));
    }

    inline const Formula &Formula::operator||(const Formula &rhs) const
    {
        return alloc(new Formula(OR, this, &rhs));
    }

    inline const Formula &Formula::operator>>(const Formula &rhs) const
    {
        return alloc(new Formula(IMPL, this, &rhs));
    }

    inline const Formula &P(const std::string &prop)
    {
        return Formula::alloc(new Formula(prop));
    }

    inline const Formula &X(const Formula &arg)
    {
        return Formula::alloc(new Formula(Formula::X, "X(" + arg.prop() + ")", &arg));
    }

    inline const Formula &G(const Formula &arg)
    {
        return Formula::alloc(new Formula(Formula::G, &arg));
    }

    inline const Formula &F(const Formula &arg)
    {
        return Formula::alloc(new Formula(Formula::F, &arg));
    }

    inline const Formula &U(const Formula &lhs, const Formula &rhs)
    {
        return Formula::alloc(new Formula(Formula::U, &lhs, &rhs));
    }

    inline const Formula &R(const Formula &lhs, const Formula &rhs)
    {
        return Formula::alloc(new Formula(Formula::R, &lhs, &rhs));
    }

    inline const Formula &TRUE()
    {
        return Formula::alloc(new Formula("true"));
    }

    std::ostream &operator<<(std::ostream &out, const Formula &formula);

} // namespace model::ltl
namespace std
{
    template <>
    struct hash<model::ltl::Formula>
    {
        size_t operator()(const model::ltl::Formula &formula) const
        {
            return formula.hash();
        }
    };
} // namespace std
