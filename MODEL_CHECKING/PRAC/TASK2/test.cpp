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

#include <cassert>
#include <iostream>

#include "bdd.h"
#include "formula.h"

using namespace model::bdd;
using namespace model::logic;

const std::string RESET = "\033[0m";
const std::string MAGENTA = "\033[36m";
const std::string BROWN = "\033[33m";

void Test(const Formula &formula1, const Formula &formula2, Bdd &bdd)
{
  std::cout << BROWN << formula1 << RESET << std::endl;
  std::cout << BROWN << formula2 << RESET << std::endl;

  const Node &root1 = bdd.create(formula1);
  std::cout << MAGENTA << root1 << RESET << std::endl;
  const Node &root2 = bdd.create(formula2);
  std::cout << MAGENTA << root2 << RESET << std::endl;
  assert(&root1 == &root2);
}

int main()
{
  Bdd bdd;

  Test((x(0) >> x(1)), (!x(1) >> !x(0)), bdd);
  Test((x(0) >> x(1)) == (!x(1) >> !x(0)), T, bdd);

  return 0;
}