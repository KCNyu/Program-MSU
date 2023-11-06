#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Printer
{
    static vector<pair<string, string>> args;

public:
    Printer() {}
    template <typename T>
    static void print(const char *name, T value)
    {
        cout << setw(12) << name << ": " << setw(12) << setfill(' ') << value << endl;
        
        stringstream stream;
        stream << std::fixed << std::setprecision(8) << value;
        string v = stream.str();
        args.push_back(make_pair(name, v));
    }
    static void json()
    {
        cout << "{";
        for (int i = 0; i < args.size(); i++)
        {
            cout << "\"" << args[i].first << "\": " << args[i].second;
            if (i != args.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
    static void split_line()
    {
        cout << "===============================" << endl;
    }
};

vector<pair<string, string>> Printer::args = {}; // static member initialization
