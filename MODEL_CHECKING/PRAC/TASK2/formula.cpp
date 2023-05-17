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

#include "formula.h"

namespace model::logic
{

  const Formula Formula::F(Formula::FALSE);
  const Formula Formula::T(Formula::TRUE);

  const Formula F = Formula::F;
  const Formula T = Formula::T;

  std::vector<std::unique_ptr<const Formula>> Formula::_formulae;

  std::ostream &operator<<(std::ostream &out, const Formula &formula)
  {
    switch (formula.kind())
    {
    case Formula::FALSE:
      return out << "false";
    case Formula::TRUE:
      return out << "true";
    case Formula::VAR:
      return out << "x" << formula.var();
    case Formula::NOT:
      return out << "!(" << formula.arg() << ")";
    case Formula::AND:
      return out << "(" << formula.lhs() << ") && (" << formula.rhs() << ")";
    case Formula::OR:
      return out << "(" << formula.lhs() << ") || (" << formula.rhs() << ")";
    case Formula::XOR:
      return out << "(" << formula.lhs() << ") != (" << formula.rhs() << ")";
    case Formula::IMPL:
      return out << "(" << formula.lhs() << ") -> (" << formula.rhs() << ")";
    case Formula::EQ:
      return out << "(" << formula.lhs() << ") == (" << formula.rhs() << ")";
    }

    return out;
  }

} // namespace model::logic
