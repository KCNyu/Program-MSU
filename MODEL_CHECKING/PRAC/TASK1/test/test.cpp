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

class ColoredStream
{
public:
    ColoredStream(const char *color, std::ostream &stream = std::cout)
        : _color(color), _stream(stream) {}

    template <typename T>
    friend ColoredStream &operator<<(ColoredStream &cs, const T &obj)
    {
        cs._stream << cs._color << obj << RESET << std::endl;
        return cs;
    }

private:
    const char *_color;
    std::ostream &_stream;
};

// Helper instances for colored output
ColoredStream info(MAGENTA);
ColoredStream text(BROWN);
ColoredStream success(GREEN);
ColoredStream error(RED);
void FormulaSpec(const Formula &formula, const Automaton &expectedAutomaton)
{
    const Automaton actualAutomaton = Translator().translate(formula);
    if (actualAutomaton == expectedAutomaton)
    {
        info << "Formula:";
        text << formula;
        info << "Automaton:";
        success << actualAutomaton;
        info << "Test result:";
        success << "Test passed!";
    }
    else
    {
        info << "Formula:";
        text << formula;
        info << "Expected automaton:";
        success << expectedAutomaton;
        info << "Actual automaton:";
        error << actualAutomaton;
        info << "Test result:";
        error << "Test failed!";
    }
}

void Test1()
{
    // from 07-ltl-to-buchi-automaton.pdf:16
    const Formula &formula = U(P("p") || P("q"), P("p") && P("q"));
    Automaton automaton;
    automaton.add_state("s1", "s2", "s3", "s4", "s5", "s6");

    automaton.set_initial("s3", "s5", "s6");

    automaton.set_final(0, "s1", "s2", "s4", "s6");

    automaton.add_trans_s("s1", {}, {"s1", "s2", "s3", "s4", "s5", "s6"});
    automaton.add_trans_s("s2", {"p"}, {"s1", "s2", "s4"});
    automaton.add_trans_s("s3", {"p"}, {"s3", "s5", "s6"});
    automaton.add_trans_s("s4", {"q"}, {"s1", "s2", "s4"});
    automaton.add_trans_s("s5", {"q"}, {"s3", "s5", "s6"});
    automaton.add_trans_s("s6", {"p", "q"}, {"s1", "s2", "s3", "s4", "s5", "s6"});

    FormulaSpec(formula, automaton);
}
void Test2()
{
    const Formula &formula = G(P("p") >> X(P("q")));
    Automaton automaton;

    automaton.add_state("s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "s13", "s14");

    automaton.set_initial("s1", "s4", "s6", "s8", "s11", "s13");

    automaton.set_final(0, "s1", "s3", "s4", "s6", "s8", "s10", "s11", "s13");

    automaton.add_trans_s("s1", {}, {"s1", "s4", "s6"});
    automaton.add_trans_s("s2", {}, {"s2", "s3", "s5", "s7"});
    automaton.add_trans_s("s3", {"p"}, {"s1", "s2", "s3", "s4", "s5", "s6", "s7"});
    automaton.add_trans_s("s4", {}, {"s8", "s11", "s13"});
    automaton.add_trans_s("s5", {}, {"s9", "s10", "s12", "s14"});
    automaton.add_trans_s("s6", {"p"}, {"s8", "s11", "s13"});
    automaton.add_trans_s("s7", {"p"}, {"s9", "s10", "s12", "s14"});
    automaton.add_trans_s("s8", {"q"}, {"s1","s4","s6"});
    automaton.add_trans_s("s9", {"q"}, {"s2","s3","s5","s7"});
    automaton.add_trans_s("s10", {"p","q"}, {"s1","s2","s3","s4","s5","s6","s7"});
    automaton.add_trans_s("s11", {"q"}, {"s8","s11","s13"});
    automaton.add_trans_s("s12", {"q"}, {"s9","s10","s12","s14"});
    automaton.add_trans_s("s13", {"p","q"}, {"s8","s11","s13"});
    automaton.add_trans_s("s14", {"p","q"}, {"s9","s10","s12","s14"});

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
