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

#include "translator.hpp"

using namespace model::ltl;
using namespace model::fsm;
using namespace model::translator;

// ANSI escape codes for colors
const char *RED = "\033[31m";
const char *GREEN = "\033[32m";
const char *BROWN = "\033[33m";
const char *MAGENTA = "\033[36m";
const char *RESET = "\033[0m";

void FormulaSpec(const Formula &formula, const Automaton &expectedAutomaton)
{
    const Automaton actualAutomaton = Translator().translate(formula);
    if (actualAutomaton != expectedAutomaton)
    {
        std::cout << MAGENTA << "Formula: " << RESET << std::endl;
        std::cout << BROWN << formula << RESET << std::endl
                  << std::endl;
        std::cout << MAGENTA << "Expected automaton: " << RESET << std::endl;
        std::cout << GREEN << expectedAutomaton << RESET << std::endl
                  << std::endl;
        std::cout << MAGENTA << "Actual automaton: " << RESET << std::endl;
        std::cout << RED << actualAutomaton << RESET << std::endl
                  << std::endl;
    }
    else
    {
        std::cout << MAGENTA << "Formula: " << RESET << std::endl;
        std::cout << BROWN << formula << RESET << std::endl
                  << std::endl;
        std::cout << MAGENTA << "Automaton: " << RESET << std::endl;
        std::cout << GREEN << actualAutomaton << RESET << std::endl
                  << std::endl;
        std::cout << GREEN << "Test passed!" << RESET << std::endl;
    }
}

void Test1()
{
    // from 07-ltl-to-buchi-automaton.pdf:16
    const Formula &formula = U(P("p") || P("q"), P("p") && P("q"));
    Automaton automaton;
    automaton.add_states({"s0", "s1", "s2", "s3", "s4", "s5", "s6"});

    automaton.set_initial("s0");

    automaton.set_finals({"s1", "s2", "s4", "s6"}, 0);

    automaton.add_trans_s("s1", {}, {"s1", "s2", "s3", "s4", "s5", "s6"});
    automaton.add_trans_s("s2", {"q"}, {"s1", "s2", "s4"});
    automaton.add_trans_s("s3", {"q"}, {"s3", "s5", "s6"});
    automaton.add_trans_s("s4", {"p"}, {"s1", "s2", "s4"});
    automaton.add_trans_s("s5", {"p"}, {"s3", "s5", "s6"});
    automaton.add_trans_s("s6", {"p", "q"}, {"s1", "s2", "s3", "s4", "s5", "s6"});

    FormulaSpec(formula, automaton);
}
void Test2()
{
    const Formula &formula = G(P("p") >> X(P("q")));
    Automaton automaton;

    FormulaSpec(formula, automaton);
}
void RunTests(const char *TestName)
{
    switch (atoi(TestName))
    {
    case 1:
        Test1();
        break;
    case 2:
        Test2();
        break;
    default:
        std::cout << "No such test" << std::endl;
        break;
    }
}
int main(const int argc, const char **argv)
{
    if (argc == 2)
    {
        RunTests(argv[1]);
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <test_name>" << std::endl;
    }
    return 0;
}
