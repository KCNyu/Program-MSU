#pragma once

#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

class Parser
{
    double L;
    double T;
    int N;
    int K;
    int steps;

    int opt;

public:
    Parser(int argc, char **argv)
    {
        L = M_PI;
        T = 1.0;
        N = 128;
        K = 1000;
        steps = 20;

        parse(argc, argv);
    }
    void parse(int argc, char **argv)
    {
        while ((opt = getopt(argc, argv, "L:T:N:K:S")) != -1)
        {
            switch (opt)
            {
            case 'L':
                L = std::stod(optarg);
                break;
            case 'T':
                T = std::stod(optarg);
                break;
            case 'N':
                N = std::stoi(optarg);
                break;
            case 'K':
                K = std::stoi(optarg);
                break;
            case 'S':
                steps = std::stoi(optarg);
                break;
            case '?':
                std::cout << "Unknown option '-" << static_cast<char>(optopt) << "'\n";
                break;
            }
        }
    }

    double getL() const { return L; }
    double getT() const { return T; }
    int getN() const { return N; }
    int getK() const { return K; }
    int getSteps() const { return steps; }
};