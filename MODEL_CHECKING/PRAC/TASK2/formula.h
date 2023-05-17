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

namespace model::logic
{

  class Formula final
  {
  public:
    enum Kind
    {
      FALSE, // Constant false
      TRUE,  // Constant true
      VAR,   // Boolean variable: x[i]
      NOT,   // Negation: ~A
      AND,   // Conjunction: (A1 & A2)
      OR,    // Disjunction: (A1 | A2)
      XOR,   // Exclusive OR: (A1 ^ A2)
      IMPL,  // Implication: (A1 -> A2)
      EQ     // Equivalence: (A1 <-> A2)
    };

    static const Formula F;
    static const Formula T;

    const Formula &operator!() const;
    const Formula &operator&&(const Formula &rhs) const;
    const Formula &operator||(const Formula &rhs) const;
    const Formula &operator>>(const Formula &rhs) const;
    const Formula &operator==(const Formula &rhs) const;
    const Formula &operator!=(const Formula &rhs) const;

    friend const Formula &x(int i);

    Kind kind() const { return _kind; }
    int var() const { return _var; }

    const Formula &arg() const { return *_lhs; }
    const Formula &lhs() const { return *_lhs; }
    const Formula &rhs() const { return *_rhs; }

  private:
    Formula(Kind kind, int var, const Formula *lhs, const Formula *rhs) : _kind(kind), _var(var), _lhs(lhs), _rhs(rhs) {}

    Formula(int var) : Formula(VAR, var, nullptr, nullptr) {}

    Formula(Kind kind) : Formula(kind, -1, nullptr, nullptr) {}

    Formula(Kind kind, const Formula *arg) : Formula(kind, -1, arg, nullptr) {}

    Formula(Kind kind, const Formula *lhs, const Formula *rhs) : Formula(kind, -1, lhs, rhs) {}

    static const Formula &alloc(const Formula *formula)
    {
      _formulae.push_back(std::unique_ptr<const Formula>(formula));
      return *formula;
    }

    static std::vector<std::unique_ptr<const Formula>> _formulae;

    const Kind _kind;
    const int _var;
    const Formula *_lhs;
    const Formula *_rhs;
  };

  extern const Formula F;
  extern const Formula T;

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

  inline const Formula &Formula::operator==(const Formula &rhs) const
  {
    return alloc(new Formula(EQ, this, &rhs));
  }

  inline const Formula &Formula::operator!=(const Formula &rhs) const
  {
    return alloc(new Formula(XOR, this, &rhs));
  }

  inline const Formula &x(int var)
  {
    return Formula::alloc(new Formula(var));
  }

  std::ostream &operator<<(std::ostream &out, const Formula &formula);

} // namespace model::logic
