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
#include <map>
#include <set>
#include <vector>

namespace model::fsm
{

    class State final
    {
    public:
        State(const std::string &label) : _label(label) {}

        bool operator==(const State &rhs) const
        {
            return _label == rhs._label;
        }

        std::string label() const { return _label; }

    private:
        const std::string _label;
    };

    class Transition final
    {
    public:
        Transition(const State &source, const std::set<std::string> &symbol, const State &target) : _source(source), _target(target), _symbol(symbol) {}

        bool operator==(const Transition &rhs) const
        {
            return _source == rhs._source && _symbol == rhs._symbol && _target == rhs._target;
        }

        const State &source() const { return _source; }
        const State &target() const { return _target; }
        const std::set<std::string> &symbol() const { return _symbol; }

    private:
        const State &_source;
        const State &_target;
        std::set<std::string> _symbol;
    };

    class Automaton final
    {
        friend std::ostream &operator<<(std::ostream &out, const Automaton &automaton);

    public:
        Automaton() {}

        template <typename... StateLabels>
        void add_state(StateLabels &&...state_labels);
        template <typename... StateLabels>
        void set_initial(StateLabels &&...state_labels);
        template <typename... StateLabels>
        void set_final(unsigned final_set_index, StateLabels &&...state_labels);

        void add_trans(
            const std::string &source,
            const std::set<std::string> &symbol,
            const std::string &target);

        void add_trans_s(const std::string &source,
                         const std::set<std::string> &symbol,
                         const std::vector<std::string> &targets);

        //@TODO: implement actual automaton equivalence checking (not just comparing the states)
        bool operator==(const Automaton &rhs) const
        {
            return _states == rhs._states && _initial_states == rhs._initial_states && _final_states == rhs._final_states && _transitions == rhs._transitions;
        }

    private:
        std::map<std::string, State> _states;
        std::set<std::string> _initial_states;
        std::map<unsigned, std::set<std::string>> _final_states;
        std::map<std::string, std::vector<Transition>> _transitions;
    };

    template <typename... StateLabels>
    void Automaton::add_state(StateLabels &&...state_labels)
    {
        auto add_state = [this](const std::string &state_label)
        {
            State state(state_label);
            _states.insert({state_label, state});
        };
        (add_state(std::forward<StateLabels>(state_labels)), ...);
    }
    template <typename... StateLabels>
    void Automaton::set_initial(StateLabels &&...state_labels)
    {
        auto set_initial = [this](const std::string &state_label)
        {
            State state(state_label);
            _initial_states.insert(state_label);
        };
        (set_initial(std::forward<StateLabels>(state_labels)), ...);
    }

    template <typename... StateLabels>
    void Automaton::set_final(unsigned final_set_index, StateLabels &&...state_labels)
    {
        auto set_final = [this, &final_set_index](const std::string &state_label)
        {
            _final_states[final_set_index].insert(state_label);
        };
        (set_final(std::forward<StateLabels>(state_labels)), ...);
    }

    inline void Automaton::add_trans(
        const std::string &source,
        const std::set<std::string> &symbol,
        const std::string &target)
    {

        auto s = _states.find(source);
        auto t = _states.find(target);

        Transition trans(s->second, symbol, t->second);
        _transitions[source].push_back(trans);
    }

    inline void Automaton::add_trans_s(const std::string &source,
                                       const std::set<std::string> &symbol,
                                       const std::vector<std::string> &targets)
    {
        for (const auto &target : targets)
        {
            add_trans(source, symbol, target);
        }
    }
} // namespace model::fsm
