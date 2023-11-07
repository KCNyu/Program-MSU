#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
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
    static void open_csv()
    {
        analytical.open("analytical.csv", ios::out | ios::trunc);
        numerical.open("numerical.csv", ios::out | ios::trunc);
        error.open("error.csv", ios::out | ios::trunc);

        analytical << "i,j,k,value" << endl;
        numerical << "i,j,k,value" << endl;
        error << "i,j,k,value" << endl;
    }
    static void save_csv(const char *filename, double i, double j, double k, double value)
    {
        if (strcmp(filename, "analytical") == 0)
        {
            analytical << std::fixed << std::setprecision(8) << i << "," << j << "," << k << "," << value << endl;
        }
        else if (strcmp(filename, "numerical") == 0)
        {
            numerical << std::fixed << std::setprecision(8) << i << "," << j << "," << k << "," << value << endl;
        }
        else if (strcmp(filename, "error") == 0)
        {
            error << std::fixed << std::setprecision(8) << i << "," << j << "," << k << "," << value << endl;
        }
    }
    static void close_csv()
    {
        analytical.close();
        numerical.close();
        error.close();
    }
    static bool verbose;
    static fstream analytical;
    static fstream numerical;
    static fstream error;
};

vector<pair<string, string>> Printer::args = {}; // static member initialization
bool Printer::verbose = false;
fstream Printer::analytical("analytical.csv");
fstream Printer::numerical("numerical.csv");
fstream Printer::error("error.csv");
