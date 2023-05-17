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

#include <memory>
#include <vector>
#include <unordered_map>
#include <tuple>

#include "formula.h"

using namespace model::logic;

namespace model::bdd
{
  using Var = std::pair<int, bool>;

  struct Node final
  {
    int var;

    const Node *low;
    const Node *high;

    Node() : var(), low(nullptr), high(nullptr) {}

    Node(int var, const Node *low, const Node *high) : var(var), low(low), high(high) {}
  };

  std::ostream &operator<<(std::ostream &out, const Node &node);

  class Bdd final
  {
  public:
    static const Node zero;
    static const Node one;

    // TODO: To be implemented in 'bdd.cpp'.
    const Node &create(const Formula &formula);

  private:
    const bool value(const Formula &formula);
    const Formula &apply_var(const Formula &formula, const Var &var);
    const int root(const Formula &formula);
    const Node &createNode(int var, const Node *low, const Node *high);

    // need by unordered_map
    struct NodeHash
    {
      size_t operator()(const std::tuple<int, const Node *, const Node *> &node) const
      {
        auto [var, low, high] = node;
        std::size_t seed = 0;
        seed ^= std::hash<int>{}(var) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<const Node *>{}(low) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<const Node *>{}(high) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
      }
    };
    std::unordered_map<std::tuple<int, const Node *, const Node *>, Node, NodeHash> nodePool;
  };

} // namespace model::bdd
