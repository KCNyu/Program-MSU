/*================================================================
 * Filename:QRmatrix.cpp
 * Author: KCN_yu
 * Createtime:Tue 06 Jul 2021 11:54:55 PM CST
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

template <typename T> class Matrix_QR{
    private:
        vector<vector<T>> data;
        int row, col;

    public:
        Matrix_QR(const char *filename);
        Matrix_QR(int row, int col);
        void InitData();
        void ReadBvec(const char *filename, vector<T>& b_data);
        Matrix_QR<T>& Transpose();
        int GetMethod(const char *filename);
        Matrix_QR<T> H(const Matrix_QR<T>& M);
        double SquareNorm();
};
template <typename T>
Matrix_QR<T>::Matrix_QR(int row, int col){
    this->row = row;
    this->col = col;
    data.resize(row);
    for (auto &r : data) {
        r.resize(col);
    }
}
template <typename T> void ReadFile(const char *filename, vector<vector<T>>& data){
    ifstream matrix(filename);
    if (!matrix.is_open()) {
        cerr << "open failed" << endl;
        exit(1);
    }

    string temp;
    vector<T> row_data;
    getline(matrix,temp);

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
    matrix.close();
}
template <> void ReadFile(const char *filename, vector<vector<complex<double>>>& data){
    ifstream matrix(filename);
    if (!matrix.is_open()) {
        cerr << "open failed" << endl;
        exit(1);
    }

    string temp;
    vector<complex<double>> row_data;
    getline(matrix,temp);

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
    matrix.close();
}
template <typename T> void Matrix_QR<T>::InitData() {
    for(auto &r : data){
        for(auto elem: r){
            cout << elem << " ";
        }
        cout << endl;
    }
    row = data.size();
    for (auto &r : data) {
        if (r.size() != row) {
            cerr << "row != col failed" << endl;
            exit(1);
        }
    }
    col = data.back().size();
}
template <typename T> Matrix_QR<T>::Matrix_QR(const char *filename) {
    ReadFile(filename,data);
    InitData();
}
template <typename T> void Matrix_QR<T>::ReadBvec(const char *filename, vector<T>& b_data) {
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
template <typename T> int Matrix_QR<T>::GetMethod(const char* filename){
    ifstream mat;
    mat.open(filename);
    string tmp;
    getline(mat,tmp);
    int pos = tmp.find("=")+1;
    mat.close();
    return tmp[pos]-'0';
}
template <typename T>  Matrix_QR<T>& Matrix_QR<T>::Transpose(){
    Matrix_QR<T> temp = *this;
    data.clear();
    row = temp.col;
    col = temp.row;
    for (int i = 0;i < row;i++) {
        vector<T> vec;
        for (int j = 0;j < col;j++) {
            vec.push_back(temp.data[j][i]);
        }
        data.push_back(vec);
    }
    return *this;
}
template <typename T> Matrix_QR<T> Matrix_QR<T>::H(const Matrix_QR<T>& M){
    Matrix_QR<complex<double> > res(M.row,M.col);
    for (int i = 0;i < M.row;i++) {
        for (int j = 0;j < M.col;j++) {
            res.data[i][j] = conj(M.data[i][j]);
        }
    }
    res.Transpose();
    return res;
}
template <typename T> double Matrix_QR<T>::SquareNorm(){
    double res = 0;
    for (int i = 0;i < row;i++) {
        for (int j = 0;j < col;j++) {
            res += norm(data[i][j]);
        }
    }
    return res;
}
template <typename T>
double alpha(const Matrix_QR<T>& A) {
    double norm = sqrt(SquareNorm());
    return A.M[0][0] > 0 ? -norm : norm;
}
template <>
complex<double> alpha(const matrix<complex<double> >& A) {
    double norm = sqrt(squareOfNorm2(A));
    double x = A.M[0][0].real(),y = A.M[0][0].imag();
    double z = mold(A.M[0][0]);
    if (z == complex<double>(0,0)) {
        return norm;
    }
    return complex<double>(norm * (x/z),norm * (y/z));
}
int main()
{
    Matrix_QR<complex<double>> M("Amat6.m");
    cout << M.SquareNorm() << endl;
}
