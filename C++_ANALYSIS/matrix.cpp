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

template <typename T>
class Matrix_LU
{
private:
    vector<vector<T>> data;
    vector<vector<T>> l_data;
    vector<vector<T>> u_data;
    vector<vector<int>> p_data;
    vector<T> b_data;
    vector<T> x_data;
    vector<T> y_data;
    int row, col;
    const double eps = 0.0000001;

public:
    Matrix_LU(const vector<vector<T>> &data, const vector<vector<T>> &b_data);
    Matrix_LU(const int n);
    void InitData();
    void PrintData();
    void DecompLU();
    void DecompLUP();
    void SolveSystem();
};
template <typename T>
void Matrix_LU<T>::InitData()
{
    row = data.size();
    for (auto &r : data)
    {
        if (r.size() != row)
        {
            cerr << "row != col failed" << endl;
            exit(1);
        }
    }
    col = data.back().size();
}
template <typename T>
Matrix_LU<T>::Matrix_LU(const vector<vector<T>> &data, const vector<vector<T>> &b_data)
{
    this->data = data;
    this->b_data = b_data;
}
template <typename T>
Matrix_LU<T>::Matrix_LU(const int n)
{
    data.resize(n);
    for (int i = 0; i < n; i++)
    {
        data[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                data[i][j] = 2;
            else if (i == j - 1 || i == j + 1)
                data[i][j] = -1;
        }
    }
    InitData();
    b_data.resize(n);
    double h = 1.0 / (n + 1.0);
    for (int i = 0; i < n; i++)
    {
        b_data[i] = 2.0 * h * h;
    }
}
template <typename T>
void Matrix_LU<T>::PrintData()
{
    /*
       cout << "============A-MATRIX============" << endl;
       for (auto &row : data)
       {
       for (auto &elem : row)
       {
       cout.width(5);
       cout << elem << " ";
       }
       cout << endl;
       }
       cout << "============L-MATRIX============" << endl;
       for (auto &row : l_data)
       {
       for (auto &elem : row)
       {
       cout.width(5);
       cout << elem << " ";
       }
       cout << endl;
       }
       cout << "============U-MATRIX============" << endl;
       for (auto &row : u_data)
       {
       for (auto &elem : row)
       {
       cout.width(5);
       cout << elem << " ";
       }
       cout << endl;
       }
       cout << "============P-MATRIX============" << endl;
       for (int i = 0; i < row; i++)
       {
       for (int j = 0; j < col; j++)
       {
       cout.width(5);
       cout << p_data[i][j] << " ";
       }
       cout << endl;
       }
       cout << "============B-VECTOR============" << endl;
       for (auto &elem : b_data)
       {
       cout.width(5);
       cout << elem << endl;
       }
     */
    int n = row;
    double x_eps = 0;
    double h = 1.0 / (n + 1.0);
    cout << "============X-VECTOR============" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout.width(5);
        cout << x_data[i - 1] << endl;
        double y = i * h * (1.0 - i * h);
        // cout << "y = " << y << endl;
        x_eps += pow(fabs(x_data[i - 1] - y), 2);
    }
    x_eps = pow(x_eps, 0.5);
    cout << "============EPS===============" << endl;
    cout << "eps = " << x_eps << endl;
    /*
       cout << "============Y-VECTOR============" << endl;
       for (auto &elem : y_data)
       {
       cout.width(5);
       cout << elem << endl;
       }
     */
    cout << "============DET===============" << endl;
    double det = 1;
    for (int i = 0; i < row; i++)
        det *= u_data[i][i];
    cout << "det = " << det << endl;
}
template <typename T>
void Matrix_LU<T>::DecompLU()
{
    if (row != col)
    {
        cerr << "Is not a square Matrix!" << endl;
        exit(1);
    }
    l_data.resize(row);
    u_data.resize(row);
    for (auto &r : l_data)
    {
        r.resize(col);
    }
    for (auto &c : u_data)
    {
        c.resize(col);
    }
    int n = row;

    for (int i = 0; i < n; i++)
    {
        l_data[i][i] = 1;
    }
    // init L matrix diag and P matrix P[i] that's where 1 is

    u_data.assign(data.begin(), data.end());

    // i -- the index of row
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(u_data[i][i]) < eps)
            {
                cerr << "The matrix is not strict regular!1" << endl;
                exit(1);
            }
            l_data[j][i] = u_data[j][i] / u_data[i][i];
            for (int k = i; k < n; k++)
            {
                u_data[j][k] -= l_data[j][i] * u_data[i][k];
            }
        }
    }
}
template <typename T>
void Matrix_LU<T>::DecompLUP()
{
    if (row != col)
    {
        cerr << "Is not a square Matrix!" << endl;
        exit(1);
    }

    l_data.resize(row);
    u_data.resize(row);
    p_data.resize(row);
    for (auto &r : l_data)
    {
        r.resize(col);
    }
    for (auto &c : u_data)
    {
        c.resize(col);
    }
    for (auto &p : p_data)
    {
        p.resize(col);
    }

    int n = row;

    for (int i = 0; i < n; i++)
    {
        l_data[i][i] = 1;
        p_data[i][i] = 1;
    }
    // init L matrix diag and P matrix P[i] that's where 1 is

    u_data.assign(data.begin(), data.end());

    // i -- the index of row
    for (int i = 0; i < n - 1; i++)
    {
        double max_elem = fabs(u_data[i][i]);
        // find max elem for each man elem in diag
        int max_i = i;
        // save the max index
        for (int j = i + 1; j < n; j++)
        {
            if (max_elem < fabs(u_data[j][i]))
            {
                max_elem = fabs(u_data[j][i]);
                max_i = j;
            }
        }
        // find max in every row at lower triangle

        swap(u_data[i], u_data[max_i]);
        swap(p_data[i], p_data[max_i]);
        // swap the row

        for (int j = i + 1; j < n; j++)
        {
            if (fabs(u_data[i][i]) < eps)
            {
                cerr << "The matrix is not strict regular!2" << endl;
                exit(1);
            }
            l_data[j][i] = u_data[j][i] / u_data[i][i];
            for (int k = i; k < n; k++)
            {
                u_data[j][k] -= l_data[j][i] * u_data[i][k];
            }
        }
    }
}
template <typename T>
void Matrix_LU<T>::SolveSystem()
{
    int n = row;
    double sum;

    x_data.resize(n);
    y_data.resize(n);

    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int j = 0; j < i; j++)
        {
            sum += l_data[i][j] * y_data[j];
        }
        y_data[i] = b_data[i] - sum;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum += u_data[i][j] * x_data[j];
        }
        x_data[i] = (y_data[i] - sum) / u_data[i][i];
    }
}
void PrintTime(high_resolution_clock::time_point start_time,
               high_resolution_clock::time_point end_time)
{
    cout << "Time: "
         << duration_cast<duration<double, milli>>(end_time - start_time).count()
         << " ms" << endl;
}
void test(const int n)
{
    const auto start_time = high_resolution_clock::now();
    Matrix_LU<double> m(n);
    m.DecompLUP();
    m.SolveSystem();
    const auto end_time = high_resolution_clock::now();
    m.PrintData();
    PrintTime(start_time, end_time);
}
int main()
{
    test(1000);
}