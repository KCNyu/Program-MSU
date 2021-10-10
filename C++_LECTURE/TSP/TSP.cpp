#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <fstream>
#include <chrono>
#include <map>
#include <memory>

#define MAX_DIST 100
#define INF 32767

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;
using mat_d = vector<vector<double>>;
using path_t = vector<pair<size_t, size_t>>;

double F(double x)
{
    return (5 / 6.0) * (1 + pow(x, 4));
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
        if (u2 <= (3 / 5.0) * F(u1))
            return u1;
    }
}
/*===============================================================*/

// Task tree node represents each reduction matrix
class TaskTree
{
private:
    double bound;
    int index_row, index_col;

public:
    mat_d mat;
    path_t path;
    TaskTree(const mat_d &m, const path_t &p = {}, const double b = 0);
    void PrintMat();
    void ReduceMinElem();
    void FindMinPath();
    bool PathCompleted() { return path.size() == mat.size(); }
    double GetBound() { return bound; }
    int GetRowIndex() { return index_row; }
    int GetColIndex() { return index_col; }
};
TaskTree::TaskTree(const mat_d &m, const path_t &p, const double b)
{
    mat = m;
    path = p;
    bound = b;
    ReduceMinElem();
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
// Minimum statute
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
    FindMinPath();
}
// Find the shortest path possible
void TaskTree::FindMinPath()
{
    index_row = -1;
    index_col = -1;
    double max_sum = -1;
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
    path.push_back(make_pair(index_row, index_col));
}
// Subtree containing the selected path
shared_ptr<TaskTree> SetLeft(const mat_d &m, const path_t &path, const double bound, const int index_row, const int index_col)
{
    mat_d mat = m;
    map<size_t, size_t> pathTest;
    for (size_t i = 0; i < path.size() - 1; i++)
    {
        pathTest[path[i].first] = path[i].second;
    }
    size_t pos = index_col;
    while (pathTest.find(pos) != pathTest.end())
    {
        pos = pathTest[pos];
        if (pos == index_row)
        {
            return nullptr;
        }
    }
    for (size_t i = 0; i < mat.size(); i++)
    {
        mat[index_row][i] = INF;
        mat[i][index_col] = INF;
    }
    mat[index_col][index_row] = INF;

    return make_shared<TaskTree>(mat, path, bound);
}
// Does not contain the subtree of the selected path
shared_ptr<TaskTree> SetRight(const mat_d &m, const path_t &p, const double bound, const int index_row, const int index_col)
{
    mat_d mat = m;
    mat[index_row][index_col] = INF;

    path_t path = p;
    path.pop_back();
    return make_shared<TaskTree>(mat, path, bound);
}
// Problem-solving tree
class Task
{
private:
    map<size_t, size_t> bestpath;
    list<shared_ptr<TaskTree>> tour;
    mat_d origin_mat;
    double best;
    shared_ptr<TaskTree> root;

public:
    Task(const size_t size, double (*pf)() = GetRnd);
    Task(const char *filename, const size_t size);
    void RunTask();
    void PrintPath();
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
    root = make_shared<TaskTree>(origin_mat);
    best = INF;
}
// Get the problem matrix from the file
// for running the demo
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
    root = make_shared<TaskTree>(origin_mat);
    best = INF;
}
// Eliminate according to the lower bound
void Task::RunTask()
{
    tour.push_front(root);
    // root->PrintMat();
    while (tour.size() != 0)
    {
        shared_ptr<TaskTree> head = tour.front();
        tour.pop_front();
        if (head->GetBound() > best)
        {
            continue;
        }
        if (head->PathCompleted())
        {
            best = head->GetBound();
            bestpath.clear();
            for (size_t i = 0; i < origin_mat.size(); i++)
            {
                bestpath[head->path[i].first] = head->path[i].second;
            }
            continue;
        }
        if (head->GetRowIndex() == -1 && head->GetColIndex() == -1)
        {
            continue;
        }
        shared_ptr<TaskTree> left = SetLeft(head->mat, head->path, head->GetBound(), head->GetRowIndex(), head->GetColIndex());
        shared_ptr<TaskTree> right = SetRight(head->mat, head->path, head->GetBound(), head->GetRowIndex(), head->GetColIndex());
        if (left != nullptr)
        {
            if (left->path.size() < origin_mat.size())
            {
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
#if 0
                cout << "bound: " << tour.front()->GetBound() << endl;
                head->PrintMat();
#endif
            }
            else
            {
                tour.push_front(left);
            }
        }
        else
        {
            tour.push_front(right);
        }
    }
    PrintPath();
}
void Task::PrintPath()
{
    cout << "Best path: 1 => ";
    size_t begin = 0;
    while (bestpath[begin] != 0)
    {
        cout << bestpath[begin] + 1 << " => ";
        begin = bestpath[begin];
    }
    cout << "1" << endl;
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
    const size_t nDim1 = 6, nDim2 = 33;
#if 0
    Task t1("input.txt", nDim1);
    t1.RunTask();
#endif
#if 1
    Task t2(nDim2);
    t2.RunTask();
#endif
    const auto end_time = high_resolution_clock::now();
    PrintTime(start_time, end_time);
}