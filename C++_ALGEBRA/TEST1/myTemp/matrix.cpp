/*================================================================
 * Filename:matrix.cpp
 * Author: KCN_yu
 * Createtime:Wed 16 Jun 2021 08:31:20 PM CST
 ================================================================*/

#include <chrono>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

template <typename T> class Matrix_LU {
    private:
        vector<vector<T>> data;
        vector<vector<T>> l_data;
        vector<vector<T>> u_data;
        vector<int> p_data;
        vector<T> b_data;
        vector<T> x_data;
        vector<T> y_data;
        int row, col;
        const double eps = 0.00001;

    public:
        Matrix_LU(const char *filename);
        void InitData();
        void PrintData();
        void WriteFile(string name, string index);
        void WriteFile(string index);
        void DecompLU();
        void DecompLUP();
        bool DetectLU();
        void ReadBvec(const char *filename);
        void ReadBvecPlus(const char *filename);
        void SolveSystem(const char *filename);
};
template <typename T> void Matrix_LU<T>::InitData() {
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
}
template <typename T> Matrix_LU<T>::Matrix_LU(const char *filename) {

    ifstream matrix(filename);
    if (!matrix.is_open()) {
        cerr << "open failed" << endl;
        exit(1);
    }

    string temp;
    vector<T> row_data;

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

    InitData();
    matrix.close();
}
template <> Matrix_LU<complex<double>>::Matrix_LU(const char *filename) {
    ifstream matrix(filename);
    if (!matrix.is_open()) {
        cerr << "open failed" << endl;
        exit(1);
    }

    string temp;
    vector<complex<double>> row_data;

    while (matrix >> temp) {

        char back = temp.back();
        ssize_t pos_left = temp.find('[');
        ssize_t pos_right = temp.find(']');

        if (pos_right != string::npos) {
            if (temp[pos_right + 1] == ',') {
                row_data.push_back(atof(temp.substr(0, pos_right).c_str()));
                data.emplace_back(row_data);
                row_data.clear();
                if (pos_left != string::npos) {
                    int cow_index = 0;
                    int col_index = 0;
                    data[cow_index][col_index++].imag(
                            atof(temp.substr(pos_left + 1).c_str()));
                    while (matrix >> temp) {
                        if (isdigit(temp.back())) {
                            data[cow_index][col_index++].imag(atof(temp.c_str()));
                        } else if (temp.back() == ';') {
                            temp.pop_back();
                            if (temp.back() == ')') {
                                pos_right = temp.find(']');
                                data[cow_index][col_index++].imag(
                                        atof(temp.substr(0, pos_right).c_str()));
                                continue;
                            }
                            data[cow_index++][col_index].imag(atof(temp.c_str()));
                            col_index = 0;
                        }
                    }
                }
            }
        } else if (pos_left != string::npos) {
            row_data.push_back(atof(temp.substr(pos_left + 1).c_str()));
        } else if (back == ';') {
            temp.pop_back();
            row_data.push_back(atof(temp.c_str()));
            data.emplace_back(row_data);
            row_data.clear();
            matrix >> temp;
            row_data.push_back(atof(temp.c_str()));
        }
    }

    InitData();
    matrix.close();
}
template <typename T> void Matrix_LU<T>::ReadBvec(const char *filename) {
    string temp;
    ifstream vec(filename);
    if (!vec.is_open()) {
        cerr << "open failed" << endl;
        exit(1);
    }
    while (vec >> temp) {
        char front = temp.front();
        char back = temp.back();
        if (front == '[') {
            temp.erase(temp.begin());
            temp.pop_back();
            b_data.push_back(atof(temp.c_str()));
        } else if (back == ';') {
            temp.pop_back();
            if (temp.back() == ']') {
                temp.pop_back();
            }
            b_data.push_back(atof(temp.c_str()));
        }
    }
}
template <typename T> void Matrix_LU<T>::ReadBvecPlus(const char *filename) {
    string temp;
    ifstream vec(filename);
    if (!vec.is_open()) {
        cerr << "open failed" << endl;
        exit(1);
    }
    while (vec >> temp) {
        char front = temp.front();
        char back = temp.back();
        if (front == '[') {
            temp.erase(temp.begin());
            temp.pop_back();
        }
        if (back == ';') {
            temp.pop_back();
            if (temp.back() == ']') {
                temp.pop_back();
            }
        }
        ssize_t pos = temp.find(';');
        ssize_t size = temp.size();
        temp += ";";
        while (pos != string::npos) {
            b_data.push_back(atof(temp.substr(0, pos).c_str()));
            temp = temp.substr(pos + 1, size);
            pos = temp.find(';');
        }
    }
}
template <typename T> void Matrix_LU<T>::PrintData() {
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
    cout << "============B-VECTOR============" << endl;
    for (auto &elem : b_data) {
        cout.width(5);
        cout << elem << endl;
    }
    cout << "============X-VECTOR============" << endl;
    for (auto &elem : x_data) {
        cout.width(5);
        cout << elem << endl;
    }
    cout << "============Y-VECTOR============" << endl;
    for (auto &elem : y_data) {
        cout.width(5);
        cout << elem << endl;
    }
}
template <typename T> void Matrix_LU<T>::WriteFile(string name, string index) {
    ofstream mat;
    string prefix = name + " = ...\n  [";
    string suffix = ";\n   ";
    int n = row, i, j;
    if (name == "L") {
        string filename = name + "mat" + index + ".m";
        mat.open(filename, ios::out);
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
        string filename = name + "mat" + index + ".m";
        mat.open(filename, ios::out);
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
        string filename = name + "mat" + index + ".m";
        mat.open(filename, ios::out);
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
    } else if (name == "X") {
        string filename = name + "vec" + index + ".m";
        mat.open(filename, ios::out);
        mat << "x = [";
        for (i = 0; i < n - 1; i++) {
            mat << x_data[i] << "; ";
        }
        mat << x_data[i] << "];";
    }
}
template <>
void Matrix_LU<complex<double>>::WriteFile(string name, string index) {
    ofstream mat;
    string prefix = name + " = complex([";
    string suffix = "]);";
    int n = row, i, j;
    string filename = name + "mat" + index + ".m";
    mat.open(filename, ios::out);
    if (name == "L") {
        mat << prefix;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n - 1; j++) {
                mat << l_data[i][j].real() << " ";
            }
            if (i < n - 1) {
                mat << l_data[i][j].real() << ";\n   ";
            } else {
                mat << l_data[i][j].real();
            }
        }
        mat << "],[";
        for (i = 0; i < n; i++) {
            for (j = 0; j < n - 1; j++) {
                mat << l_data[i][j].imag() << " ";
            }
            if (i < n - 1) {
                mat << l_data[i][j].imag() << ";\n   ";
            } else {
                mat << l_data[i][j].imag();
            }
        }
        mat << suffix;
    } else if (name == "U") {
        mat << prefix;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n - 1; j++) {
                mat << u_data[i][j].real() << " ";
            }
            if (i < n - 1) {
                mat << u_data[i][j].real() << ";\n   ";
            } else {
                mat << u_data[i][j].real();
            }
        }
        mat << "],[";
        for (i = 0; i < n; i++) {
            for (j = 0; j < n - 1; j++) {
                mat << u_data[i][j].imag() << " ";
            }
            if (i < n - 1) {
                mat << u_data[i][j].imag() << ";\n   ";
            } else {
                mat << u_data[i][j].imag();
            }
        }
        mat << suffix;
    } else if (name == "P") {
        prefix = name + " = ...\n  [";
        suffix = ";\n   ";
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
template <typename T> void Matrix_LU<T>::WriteFile(string index) {
    WriteFile("L", index);
    WriteFile("U", index);
    if (atoi(index.c_str()) <= 2) {
        WriteFile("P", index);
    } else {
        WriteFile("X", index);
    }
}
template <typename T> void Matrix_LU<T>::DecompLU() {
    if (row != col) {
        cerr << "Is not a square Matrix!" << endl;
        exit(1);
    }
    int n = row;

    for (int i = 0; i < n; i++) {
        l_data[i][i] = 1;
    }
    // init L matrix diag and P matrix P[i] that's where 1 is

    u_data.assign(data.begin(), data.end());

    // i -- the index of row
    for (int i = 0; i < n - 1; i++) {
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
template <typename T> void Matrix_LU<T>::DecompLUP() {
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
                max_elem = fabs(u_data[j][i]);
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
template <typename T> void Matrix_LU<T>::SolveSystem(const char *filename) {

    if (filename[4] == '4') {
        ReadBvecPlus(filename);
    } else {
        ReadBvec(filename);
    }

    int n = row;
    double sum;

    x_data.resize(n);
    y_data.resize(n);

    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < i; j++) {
            sum += l_data[i][j] * y_data[j];
        }
        y_data[i] = b_data[i] - sum;
    }
    for (int i = n - 1; i >= 0; i--) {
        sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += u_data[i][j] * x_data[j];
        }
        x_data[i] = (y_data[i] - sum) / u_data[i][i];
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
    char index = filename[4];
    if (index == '1') {
        Matrix_LU<double> m(filename);
        m.DecompLUP();
        m.WriteFile("1");
    } else if (index == '2') {
        Matrix_LU<complex<double>> m(filename);
        m.DecompLUP();
        m.WriteFile("2");
    } else if (index == '3') {
        Matrix_LU<double> m(filename);
        m.DecompLU();
        m.SolveSystem("bvec3.m");
        m.WriteFile("3");
    } else if (index == '4') {
        Matrix_LU<double> m(filename);
        m.DecompLU();
        m.SolveSystem("bvec4.m");
        m.WriteFile("4");
    }

    const auto end_time = high_resolution_clock::now();
    PrintTime(start_time, end_time);
}
int main() {
    make_lu("Amat1.m");
    make_lu("Amat2.m");
    make_lu("Amat3.m");
    make_lu("Amat4.m");
}
