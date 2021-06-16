/*================================================================
 * Filename:matrix.cpp
 * Author: KCN_yu
 * Createtime:Wed 16 Jun 2021 08:31:20 PM CST
 ================================================================*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

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
        double SumLrkUki(int r, int i);
        double SumLikUkr(int r, int i);
};
Matrix_LU::Matrix_LU(const char *filename) {

    ifstream matrix(filename);
    if (!matrix.is_open()) {
        cerr << "open failed" << endl;
        exit(0);
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
            exit(0);
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
}
void Matrix_LU::WriteFile(string name) {
    ofstream mat;
    string prefix = name + " = ...\n  [";
    string suffix = ";\n   ";
    int n = row, i, j;
    if(name == "L"){
        mat.open("Lmat1_temp.m",ios::out);
        mat << prefix;
        for(i = 0; i < n; i++){
            for(j = 0; j < n-1; j++){
                mat << l_data[i][j] << " ";
            }
            mat << l_data[i][j];
            if(i < n-1){
                mat << suffix;
            }
            else{
                mat << "];";
            }
        }
    }
    else if(name == "U"){
        mat.open("Umat1_temp.m",ios::out);
        mat << prefix;
        for(i = 0; i < n; i++){
            for(j = 0; j < n-1; j++){
                mat << u_data[i][j] << " ";
            }
            mat << u_data[i][j];
            if(i < n-1){
                mat << suffix;
            }
            else{
                mat << "];";
            }
        }
    }
}
void Matrix_LU::WriteFile(){
    WriteFile("L");
    WriteFile("U");
}
double Matrix_LU::SumLrkUki(int r, int i) {
    double re = 0.0;
    for (int k = 0; k < r; k++) {
        re += l_data[r][k] * u_data[k][i];
    }
    return re;
}
double Matrix_LU::SumLikUkr(int r, int i) {
    double re = 0.0;
    for (int k = 0; k < r; k++) {
        re += l_data[i][k] * u_data[k][r];
    }
    return re;
}
void Matrix_LU::DecompLU() {
    if (row != col) {
        cerr << "Is not a square Matrix!" << endl;
        exit(0);
    }
    int n = row;
    /*
    for (int i = 0; i < n; i++){
        l_data[i][i] = 1;
        p_data.push_back(i);
    }
    for(int j = 0; j < n-1; j++){
        double max_elem = fabs(data[j][j]);
        int max_j = j;
        for(int m = j+1; m < n; m++){
            if(max_elem < fabs(data[m][j])){
                max_elem = data[m][j];
                max_j = j;
            }
        }
        cout << "j = " << j << endl;
        cout << "max_j = " << max_j << endl;
        swap(data[j],data[max_j]);
        swap(l_data[j],l_data[max_j]);
        swap(u_data[j],u_data[max_j]);
        swap(p_data[j],p_data[max_j]);
        for(int i = j+1; i < n; i++){
            if(fabs(data[j][j]) < eps){
                cerr << "The matrix is not strict regular!" << endl;
                exit(0);
            }
            l_data[i][j] = data[i][j]/data[j][j];
            for(int k = j; k < n; k++){
                data[i][k] -= l_data[i][j]*data[j][k];
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            u_data[i][j] = data[i][j];
        }
    }
    // l diag = 1;
    */

    for (int i = 0; i < n; i++) { // 第一步，计算L的第一列和U的第一行：U1i=A1i,Li1=Ai1/U11
        u_data[0][i] = data[0][i];
        l_data[i][0] = data[i][0] / u_data[0][0];
    }
    //计算U的第r行，L的第r列元素
    // uri=ari-Σ(k=1->r-1)lrkuki    (i=r,r+1,...,n)
    // lir=air-Σ(k=1->r-1)likukr    (i=r+1,r+2,...,n且r≠n)
    for (int r = 1; r < n; r++) {
        for (int i = r; i < n; i++) {
            u_data[r][i] = data[r][i] - SumLrkUki(r, i);
            if (i == r)
                l_data[r][r] = 1;
            else if (r == n)
                l_data[n][n] = 1;
            else{
                if(fabs(u_data[r][r]) < eps){
                    cerr << "The matrix is not strict regular!" << endl;
                    exit(0);
                }
                l_data[i][r] = (data[i][r] - SumLikUkr(r, i)) / u_data[r][r];
            }
        }
    }
}
int main() {
    Matrix_LU t("Amat1_temp.m");
    t.DecompLU();
    t.PrintData();
    t.WriteFile();
}
