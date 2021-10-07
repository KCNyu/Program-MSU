/*================================================================
* Filename:main.cpp
* Author: KCN_yu
* Createtime:Wed 06 Oct 2021 01:43:05 PM CST
================================================================*/

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <fstream>
#include <chrono>
#include <unistd.h>

#define MAX_DIST 100
#define INF 32767

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;
using mat_d = vector<vector<double>>;

double F(double x)
{
    return (5 / 6) * (1 + pow(x, 4));
}
// use Acceptance-Rejection Method
// max from 0 to 1 in function F is 5/3
double GetRnd()
{
    double u1, u2;
    while (true)
    {
        u1 = rand() % MAX_DIST;
        u2 = rand() % MAX_DIST;
        if (u2 <= (3 / 5) * F(u1))
            return u1;
    }
}
/*===============================================================*/

class TaskTree
{
private:
    mat_d mat;
    double bound;
    TaskTree *leftTaskTree;
    TaskTree *rightTaskTree;

public:
    size_t index_row, index_col;
    TaskTree(const mat_d &m, const double b = 0);
    void PrintMat();
    void ReduceMinElem();
    void SetBranch();
    void RunTask();
    bool PathCompleted();
    TaskTree *GetLeft() { return leftTaskTree; }
    TaskTree *GetRight() { return rightTaskTree; }
    double GetBound() { return bound; }
    ~TaskTree() { delete leftTaskTree; delete rightTaskTree; }
};
TaskTree::TaskTree(const mat_d &m, const double b)
{
    for (auto iter : m)
    {
        mat.push_back(iter);
    }
    leftTaskTree = nullptr;
    rightTaskTree = nullptr;
    bound = b;
}
void TaskTree::PrintMat()
{

    for (auto iter_v : mat)
    {
        for (auto iter : iter_v)
        {
            cout.width(5);
            if (iter == INF)
                cout << "INF"
                     << " ";
            else
                cout << iter << " ";
        }
        cout << endl;
    }
}
void TaskTree::ReduceMinElem()
{
    for (size_t i = 0; i < mat.size(); i++)
    {
        double minelem_row = INF;
        for (size_t j = 0; j < mat.size(); j++)
        {
            if (minelem_row > mat[i][j])
            {
                minelem_row = mat[i][j];
            }
        }
        for (size_t j = 0; j < mat.size(); j++)
        {
            if (mat[i][j] != INF)
            {
                mat[i][j] -= minelem_row;
            }
        }
        if (minelem_row != INF)
            bound += minelem_row;
    }
    for (size_t i = 0; i < mat.size(); i++)
    {
        double minelem_col = INF;
        for (size_t j = 0; j < mat.size(); j++)
        {
            if (minelem_col > mat[j][i])
            {
                minelem_col = mat[j][i];
            }
        }
        for (size_t j = 0; j < mat.size(); j++)
        {
            if (mat[j][i] != INF)
            {
                mat[j][i] -= minelem_col;
            }
        }
        if (minelem_col != INF)
            bound += minelem_col;
    }
}
void TaskTree::SetBranch()
{
    double max_sum = 0;
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < mat.size(); j++)
        {
            if (mat[i][j] == 0)
            {
                double min_row = INF, min_col = INF;
                for (size_t k = 0; k < mat.size(); k++)
                {
                    if (k != j && mat[i][k] < min_row)
                        min_row = mat[i][k];
                    if (k != i && mat[k][j] < min_col)
                        min_col = mat[k][j];
                }
                double max_sum_tmp = min_row + min_col;
                if (max_sum_tmp > max_sum)
                {
                    index_row = i;
                    index_col = j;
                    max_sum = max_sum_tmp;
                }
            }
        }
    }
    double tmp = mat[index_row][index_col];
    mat[index_row][index_col] = INF;
    rightTaskTree = new TaskTree(mat, bound);

    mat[index_row][index_col] = tmp;
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < mat.size(); j++)
        {
            if (i == index_row || j == index_col)
                mat[i][j] = INF;
        }
    }
    mat[index_col][index_row] = INF;
    leftTaskTree = new TaskTree(mat, bound);
}
void TaskTree::RunTask()
{
    ReduceMinElem();
    SetBranch();
}
bool TaskTree::PathCompleted()
{
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < mat.size(); j++)
        {
            if (mat[i][j] != INF && mat[i][j] != 0)
                return false;
        }
    }
    //cout << "OK" << endl;
    return true;
}
class Task
{
private:
    //map<size_t, size_t> path;
    list<TaskTree *> tour;
    mat_d origin_mat;
    double best;

public:
    Task(const size_t size, double (*pf)() = GetRnd);
    Task(const char *filename, const size_t size);
    void RunTask();
    TaskTree *root;
};
Task::Task(const size_t size, double (*pf)())
{
    for (size_t i = 0; i < size; i++)
    {
        vector<double> tmp;
        tmp.resize(size);
        for (size_t j = 0; j < size; j++)
        {
            if (i != j)
                tmp[j] = pf();
            else
                tmp[j] = INF;
        }
        origin_mat.push_back(tmp);
    }
    root = new TaskTree(origin_mat);
    best = INF;
}
Task::Task(const char *filename, const size_t size)
{
    ifstream matrix(filename);
    if (!matrix.is_open())
    {
        cerr << "open failed" << endl;
        exit(1);
    }
    string temp;
    vector<double> row_data;
    size_t i = 0;
    while (matrix >> temp)
    {
        row_data.push_back(atof(temp.c_str()));
        i++;
        if (i == size)
        {
            origin_mat.push_back(row_data);
            row_data.clear();
            i = 0;
        }
    }
    matrix.close();
    root = new TaskTree(origin_mat);
    best = INF;
}
void Task::RunTask()
{
    tour.push_front(root);
    while (tour.size() != 0)
    {
        TaskTree *head = tour.front();
        tour.pop_front();
        if (head->PathCompleted())
        {
            if (head->GetBound() < best)
            {
                best = head->GetBound();
            }
            for (auto iter = tour.begin(); iter != tour.end();)
            {
                if ((*iter)->GetBound() >= best)
                {
                    delete (*iter);
                    iter = tour.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
            continue;
        }
        head->RunTask();
        TaskTree *left = head->GetLeft();
        TaskTree *right = head->GetRight();
        left->ReduceMinElem();
        right->ReduceMinElem();
        if (left->GetBound() < right->GetBound())
        {
            tour.push_front(right);
            tour.push_front(left);
        }
        else
        {
            tour.push_front(left);
            tour.push_front(right);
        }
        //sleep(1);
        //cout << "bound: " << tour.front()->GetBound() << endl;
        //head->PrintMat();
    }
    cout << "best tour: " << best << endl;
}
void PrintTime(high_resolution_clock::time_point start_time,
               high_resolution_clock::time_point end_time)
{
    cout << "Time: "
         << duration_cast<duration<double, milli>>(end_time - start_time).count()
         << " ms" << endl;
}
int main()
{
    const auto start_time = high_resolution_clock::now();
    srand(time(NULL));
    const size_t nDim1 = 6, nDim2 = 23;
    //Task t1("input.txt", nDim1);
    Task t1(nDim2);
    t1.RunTask();
    const auto end_time = high_resolution_clock::now();
    PrintTime(start_time, end_time);
}
