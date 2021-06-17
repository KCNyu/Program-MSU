/*================================================================
 * Filename:matrix.cpp
 * Author: KCN_yu
 * Createtime:Wed 16 Jun 2021 08:31:20 PM CST
 ================================================================*/

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

class Matrix_LU {
    private:
        vector<vector<double>> data;
        vector<vector<double>> l_data;
        vector<vector<double>> u_data;
        vector<int> p_data;
        int row, col;
        const double eps = 0.00001;

    public:
        Matrix_LU(const char *filename);
        void PrintData();
        void WriteFile(string name);
        void WriteFile();
        void DecompLU();
};
Matrix_LU::Matrix_LU(const char *filename) {

    ifstream matrix(filename);
    if (!matrix.is_open()) {
        cerr << "open failed" << endl;
        exit(1);
    }

    string temp;
    vector<double> row_data;

    while (matrix >> temp) {
        char front = temp.front();
        char back = temp.back();
        if (front == '[') {
            temp.erase(temp.begin());
            row_data.push_back(atof(temp.c_str()));
        } else if (isdigit(back)) {
            row_data.push_back(atof(temp.c_str()));
        } else if (back == ';') {
            temp.pop_back();
            if (temp.back() == ']') {
                temp.pop_back();
            }
            row_data.push_back(atof(temp.c_str()));
            data.emplace_back(row_data);
            row_data.clear();
        }
    }
    row = data.size();
    for (auto &r : data) {
        if (r.size() != row) {
            cerr << "row != col failed" << endl;
            exit(1);
        }
    }
    col = data.back().size();

    l_data.resize(row);
    u_data.resize(row);
    for (auto &r : l_data) {
        r.resize(col);
    }
    for (auto &c : u_data) {
        c.resize(col);
    }

    matrix.close();
}
void Matrix_LU::PrintData() {
    cout << "============A-MATRIX============" << endl;
    for (auto &row : data) {
        for (auto &elem : row) {
            cout.width(5);
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << "============L-MATRIX============" << endl;
    for (auto &row : l_data) {
        for (auto &elem : row) {
            cout.width(5);
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << "============U-MATRIX============" << endl;
    for (auto &row : u_data) {
        for (auto &elem : row) {
            cout.width(5);
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << "============P-MATRIX============" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout.width(5);
            cout << (j == p_data[i] ? 1 : 0) << " ";
        }
        cout << endl;
    }
}
void Matrix_LU::WriteFile(string name) {
    ofstream mat;
    string prefix = name + " = ...\n  [";
    string suffix = ";\n   ";
    int n = row, i, j;
    if (name == "L") {
        mat.open("Lmat1_temp.m", ios::out);
        mat << prefix;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n - 1; j++) {
                mat << l_data[i][j] << " ";
            }
            mat << l_data[i][j];
            if (i < n - 1) {
                mat << suffix;
            } else {
                mat << "];";
            }
        }
    } else if (name == "U") {
        mat.open("Umat1_temp.m", ios::out);
        mat << prefix;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n - 1; j++) {
                mat << u_data[i][j] << " ";
            }
            mat << u_data[i][j];
            if (i < n - 1) {
                mat << suffix;
            } else {
                mat << "];";
            }
        }
    } else if (name == "P") {
        mat.open("Pmat1_temp.m", ios::out);
        mat << prefix;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n - 1; j++) {
                mat << (j == p_data[i] ? 1 : 0) << " ";
            }
            mat << (j == p_data[i] ? 1 : 0);
            if (i < n - 1) {
                mat << suffix;
            } else {
                mat << "];";
            }
        }
    }
}
void Matrix_LU::WriteFile() {
    WriteFile("L");
    WriteFile("U");
    WriteFile("P");
}
void Matrix_LU::DecompLU() {
    if (row != col) {
        cerr << "Is not a square Matrix!" << endl;
        exit(1);
    }
    int n = row;

    for (int i = 0; i < n; i++) {
        l_data[i][i] = 1;
        p_data.push_back(i);
    }
    // init L matrix diag and P matrix P[i] that's where 1 is

    u_data.assign(data.begin(), data.end());

    // i -- the index of row
    for (int i = 0; i < n - 1; i++) {
        double max_elem = fabs(u_data[i][i]);
        // find max elem for each man elem in diag
        int max_i = i;
        // save the max index
        for (int j = i + 1; j < n; j++) {
            if (max_elem < fabs(u_data[j][i])) {
                max_elem = u_data[j][i];
                max_i = j;
            }
        }
        // find max in every row at lower triangle

        swap(u_data[i], u_data[max_i]);
        swap(p_data[i], p_data[max_i]);
        // swap the row

        for (int j = i + 1; j < n; j++) {
            if (fabs(u_data[i][i]) < eps) {
                cerr << "The matrix is not strict regular!" << endl;
                exit(1);
            }
            l_data[j][i] = u_data[j][i] / u_data[i][i];
            for (int k = i; k < n; k++) {
                u_data[j][k] -= l_data[j][i] * u_data[i][k];
            }
        }
    }
}
void PrintTime(high_resolution_clock::time_point start_time,
        high_resolution_clock::time_point end_time) {
    cout << "Time: "
        << duration_cast<duration<double, milli>>(end_time - start_time).count()
        << " ms" << endl;
}
void make_lu(const char *filename) {
    const auto start_time = high_resolution_clock::now();
    Matrix_LU m(filename);
    m.DecompLU();
    m.PrintData();
    m.WriteFile();
    const auto end_time = high_resolution_clock::now();
    PrintTime(start_time, end_time);
}
int main()
{
    make_lu("Amat1.m");
}
