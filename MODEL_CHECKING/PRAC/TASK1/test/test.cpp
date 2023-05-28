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

    automaton.add_state("s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "s13", "s14");

    automaton.set_initial("s1", "s3", "s5", "s7", "s10", "s13");

    automaton.set_final(0, "s1", "s3", "s5", "s7", "s9", "s10", "s12", "s13");

    automaton.add_trans_s("s1", {}, {"s1", "s3", "s10"});
    automaton.add_trans_s("s2", {}, {"s2", "s4", "s9", "s11"});
    automaton.add_trans_s("s3", {}, {"s5", "s7", "s13"});
    automaton.add_trans_s("s4", {}, {"s6", "s8", "s12", "s14"});
    automaton.add_trans_s("s5", {"q"}, {"s1", "s3", "s10"});
    automaton.add_trans_s("s6", {"q"}, {"s2", "s4", "s9", "s11"});
    automaton.add_trans_s("s7", {"q"}, {"s5", "s7", "s13"});
    automaton.add_trans_s("s8", {"q"}, {"s6", "s8", "s12", "s14"});
    automaton.add_trans_s("s9", {"p"}, {"s1", "s2", "s3", "s4", "s9", "s10", "s11"});
    automaton.add_trans_s("s10", {"p"}, {"s5", "s7", "s13"});
    automaton.add_trans_s("s11", {"p"}, {"s6", "s8", "s12", "s14"});
    automaton.add_trans_s("s12", {"p", "q"}, {"s1", "s2", "s3", "s4", "s9", "s10", "s11"});
    automaton.add_trans_s("s13", {"p", "q"}, {"s5", "s7", "s13"});
    automaton.add_trans_s("s14", {"p", "q"}, {"s6", "s8", "s12", "s14"});

    FormulaSpec(formula, automaton);
}
void Test3()
{
    const Formula &formula = G(P("p") >> F(P("q")));
    Automaton automaton;

    automaton.add_state("s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11");

    automaton.set_initial("s1", "s2", "s5", "s8", "s10");

    automaton.set_final(0, "s1", "s3", "s5", "s6", "s7", "s10", "s11");
    automaton.set_final(1, "s1", "s2", "s5", "s7", "s8", "s10");

    automaton.add_trans_s("s1", {}, {"s1"});
    automaton.add_trans_s("s2", {}, {"s2", "s5", "s8", "s10"});
    automaton.add_trans_s("s3", {}, {"s3", "s7"});
    automaton.add_trans_s("s4", {}, {"s4", "s6", "s9", "s11"});
    automaton.add_trans_s("s5", {"q"}, {"s1", "s2", "s5", "s8", "s10"});
    automaton.add_trans_s("s6", {"q"}, {"s3", "s4", "s6", "s7", "s9", "s11"});
    automaton.add_trans_s("s7", {"p"}, {"s1", "s3", "s7"});
    automaton.add_trans_s("s8", {"p"}, {"s2", "s5", "s8", "s10"});
    automaton.add_trans_s("s9", {"p"}, {"s4", "s6", "s9", "s11"});
    automaton.add_trans_s("s10", {"p", "q"}, {"s1", "s2", "s5", "s8", "s10"});
    automaton.add_trans_s("s11", {"p", "q"}, {"s3", "s4", "s6", "s7", "s9", "s11"});

    FormulaSpec(formula, automaton);
}
void Test4()
{
    const Formula &formula = F(G(P("p") >> X(X(P("q")))));
    Automaton automaton;

    automaton.add_state("s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "s13", "s14", "s15", "s16", "s17", "s18", "s19", "s20", "s21", "s22", "s23", "s24", "s25", "s26", "s27", "s28", "s29", "s30", "s31", "s32", "s33", "s34", "s35", "s36", "s37", "s38", "s39", "s40", "s41", "s42", "s43", "s44");

    automaton.set_initial("s1", "s3", "s4", "s6", "s7", "s9", "s10", "s12", "s13", "s15", "s16", "s18", "s19", "s21", "s22", "s24", "s26", "s27", "s29", "s31", "s32", "s34", "s36", "s37", "s39", "s41", "s42", "s44");

    automaton.set_final(0, "s1", "s4", "s7", "s10", "s13", "s16", "s19", "s22", "s25", "s26", "s27", "s30", "s31", "s32", "s35", "s36", "s37", "s40", "s41", "s42");
    automaton.set_final(1, "s1", "s2", "s4", "s5", "s7", "s8", "s10", "s11", "s13", "s14", "s16", "s17", "s19", "s20", "s22", "s23", "s25", "s27", "s28", "s30", "s32", "s33", "s35", "s37", "s38", "s40", "s42", "s43");

    automaton.add_trans_s("s1", {}, {"s1", "s4", "s27"});
    automaton.add_trans_s("s2", {}, {"s2", "s5", "s25", "s28"});
    automaton.add_trans_s("s3", {}, {"s3", "s6", "s26", "s29"});
    automaton.add_trans_s("s4", {}, {"s7", "s10", "s32"});
    automaton.add_trans_s("s5", {}, {"s8", "s11", "s30", "s33"});
    automaton.add_trans_s("s6", {}, {"s9", "s12", "s31", "s34"});
    automaton.add_trans_s("s7", {}, {"s13", "s16", "s37"});
    automaton.add_trans_s("s8", {}, {"s14", "s17", "s35", "s38"});
    automaton.add_trans_s("s9", {}, {"s15", "s18", "s36", "s39"});
    automaton.add_trans_s("s10", {}, {"s19", "s22", "s42"});
    automaton.add_trans_s("s11", {}, {"s20", "s23", "s40", "s43"});
    automaton.add_trans_s("s12", {}, {"s21", "s24", "s41", "s44"});
    automaton.add_trans_s("s13", {"q"}, {"s1", "s4", "s27"});
    automaton.add_trans_s("s14", {"q"}, {"s2", "s5", "s25", "s28"});
    automaton.add_trans_s("s15", {"q"}, {"s3", "s6", "s26", "s29"});
    automaton.add_trans_s("s16", {"q"}, {"s7", "s10", "s32"});
    automaton.add_trans_s("s17", {"q"}, {"s8", "s11", "s30", "s33"});
    automaton.add_trans_s("s18", {"q"}, {"s9", "s12", "s31", "s34"});
    automaton.add_trans_s("s19", {"q"}, {"s13", "s16", "s37"});
    automaton.add_trans_s("s20", {"q"}, {"s14", "s17", "s35", "s38"});
    automaton.add_trans_s("s21", {"q"}, {"s15", "s18", "s36", "s39"});
    automaton.add_trans_s("s22", {"q"}, {"s19", "s22", "s42"});
    automaton.add_trans_s("s23", {"q"}, {"s20", "s23", "s40", "s43"});
    automaton.add_trans_s("s24", {"q"}, {"s21", "s24", "s41", "s44"});
    automaton.add_trans_s("s25", {"p"}, {"s2", "s5", "s25", "s28"});
    automaton.add_trans_s("s26", {"p"}, {"s1", "s3", "s4", "s6", "s26", "s27", "s29"});
    automaton.add_trans_s("s27", {"p"}, {"s7", "s10", "s32"});
    automaton.add_trans_s("s28", {"p"}, {"s8", "s11", "s30", "s33"});
    automaton.add_trans_s("s29", {"p"}, {"s9", "s12", "s31", "s34"});
    automaton.add_trans_s("s30", {"p"}, {"s14", "s17", "s35", "s38"});
    automaton.add_trans_s("s31", {"p"}, {"s13", "s15", "s16", "s18", "s36", "s37", "s39"});
    automaton.add_trans_s("s32", {"p"}, {"s19", "s22", "s42"});
    automaton.add_trans_s("s33", {"p"}, {"s20", "s23", "s40", "s43"});
    automaton.add_trans_s("s34", {"p"}, {"s21", "s24", "s41", "s44"});
    automaton.add_trans_s("s35", {"p", "q"}, {"s2", "s5", "s25", "s28"});
    automaton.add_trans_s("s36", {"p", "q"}, {"s1", "s3", "s4", "s6", "s26", "s27", "s29"});
    automaton.add_trans_s("s37", {"p", "q"}, {"s7", "s10", "s32"});
    automaton.add_trans_s("s38", {"p", "q"}, {"s8", "s11", "s30", "s33"});
    automaton.add_trans_s("s39", {"p", "q"}, {"s9", "s12", "s31", "s34"});
    automaton.add_trans_s("s40", {"p", "q"}, {"s14", "s17", "s35", "s38"});
    automaton.add_trans_s("s41", {"p", "q"}, {"s13", "s15", "s16", "s18", "s36", "s37", "s39"});
    automaton.add_trans_s("s42", {"p", "q"}, {"s19", "s22", "s42"});
    automaton.add_trans_s("s43", {"p", "q"}, {"s20", "s23", "s40", "s43"});
    automaton.add_trans_s("s44", {"p", "q"}, {"s21", "s24", "s41", "s44"});

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
    case 3:
        Test3();
        break;
    case 4:
        Test4();
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
