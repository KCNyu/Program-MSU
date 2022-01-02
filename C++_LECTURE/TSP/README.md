# ***Решение задачи коммивояжера при помощи метода ветвей и границ***

<center><B><font size="6">Вариант А3 Б1 В2</font></B></center>

<center><B><font size="6">Ли Шэнюй</font></B></center>

### 1、Исходная функция плотности вероятности для случайных данных

![](http://latex.codecogs.com/svg.latex?\int_\{-\infty\}^\{+\infty\}\{c*(1+x^4)dx\}=\int_{0}^{1}{c*(1+x^4)dx}=1)

![](http://latex.codecogs.com/svg.latex?\{c}=5/6)




### 2、Данные запусков

| **Номер запуска** | **Время (23)** | **Время (33)** |
| :---------------: | :------------: | :------------: |
|         1         |   3.06541 ms   |   26.9593 ms   |
|         2         |   3.65156 ms   |   48.6972 ms   |
|         3         |   2.66832 ms   |   43.5297 ms   |
|         4         |   6.78412 ms   |   44.7827 ms   |
|         5         |   9.77699 ms   |   24.6574 ms   |
|         6         |   4.44002 ms   |   24.3777 ms   |
|         7         |   9.36337 ms   |   20.4059 ms   |
|         8         |   7.22274 ms   |   45.9999 ms   |
|         9         |   8.77502 ms   |   41.7881 ms   |
|        10         |   8.07504 ms   |   66.3793 ms   |

Среднее время выполнения для размерности 23 получилось ***6.4 ms***, а для размерности 33 получилось ***38.8 ms*** .



### 3、Решение задачи с ограничением времени

|      DIM=23       |           |  0.01T  |       |  0.03T  |       |  0.1T   |       |  0.3T   |       |  0.5T   |       |
| :---------------: | --------- | :-----: | :---: | :-----: | :---: | :-----: | :---: | :-----: | :---: | :-----: | :---: |
| **Номер запуска** | ***опт*** | **псе** | **%** | **псе** | **%** | **псе** | **%** | **псе** | **%** | **псе** | **%** |
|         1         | ***242*** |    ∞    |   0   |   244   | 99.18 |   244   | 99.18 |   244   | 99.18 |   242   |  100  |
|         2         | ***207*** |    ∞    |   0   |   224   | 92.41 |   224   | 92.41 |   219   | 97.76 |   207   |  100  |
|         3         | **201**   |    ∞    |   0   |   209   | 96.17 |   209   | 96.17 |   206   | 98.56 |   201   |  100  |
|         4         | ***226*** |    ∞    |   0   |   237   | 95.35 |   228   | 99.12 |   226   |  100  |   226   |  100  |
|         5         | ***250*** |    ∞    |   0   |   262   | 95.41 |   259   | 96.52 |   258   | 96.89 |   252   | 99.20 |
|         6         | ***205*** |    ∞    |   0   |   207   | 99.03 |   205   |  100  |   205   |  100  |   205   |  100  |
|         7         | ***214*** |    ∞    |   0   |   215   | 99.53 |   215   | 99.53 |   215   | 99.53 |   214   |  100  |
|         8         | **245**   |    ∞    |   0   |   250   | 98.00 |   247   | 99.19 |   247   | 99.19 |   247   | 99.19 |
|         9         | ***287*** |    ∞    |   0   |   293   | 97.95 |   292   | 98.28 |   292   | 98.28 |   292   | 98.28 |
|        10         | ***249*** |    ∞    |   0   |   255   | 97.64 |   255   | 97.64 |   255   | 97.64 |   249   |  100  |

|      DIM=33       |           |  0.01T  |       |  0.03T  |       |  0.1T   |       |  0.3T   |       |  0.5T   |       |
| :---------------: | --------- | :-----: | :---: | :-----: | :---: | :-----: | :---: | :-----: | :---: | :-----: | :---: |
| **Номер запуска** | ***опт*** | **псе** | **%** | **псе** | **%** | **псе** | **%** | **псе** | **%** | **псе** | **%** |
|         1         | ***264*** |    ∞    |   0   |   277   | 95.30 |   276   | 95.65 |   275   | 96.00 |   272   | 97.05 |
|         2         | ***279*** |    ∞    |   0   |    ∞    |   0   |   308   | 90.58 |   299   | 93.31 |   292   | 95.54 |
|         3         | **263**   |    ∞    |   0   |   267   | 98.50 |   265   | 99.24 |   264   | 99.62 |   263   |  100  |
|         4         | ***244*** |    ∞    |   0   |    ∞    |   0   |   244   |  100  |   244   |  100  |   244   |  100  |
|         5         | ***294*** |    ∞    |   0   |    ∞    |   0   |   297   | 98.98 |   294   |  100  |   294   |  100  |
|         6         | ***241*** |    ∞    |   0   |   257   | 99.03 |   257   | 93.77 |   249   | 96.78 |   241   |  100  |
|         7         | ***270*** |    ∞    |   0   |   291   | 92.78 |   273   | 98.90 |   273   | 98.90 |   270   |  100  |
|         8         | **245**   |    ∞    |   0   |   260   | 94.23 |   260   | 94.23 |   246   | 99.59 |   246   | 99.59 |
|         9         | ***257*** |    ∞    |   0   |   258   | 97.95 |   258   | 99.61 |   258   | 99.61 |   257   |  100  |
|        10         | ***277*** |    ∞    |   0   |    ∞    |   0   |   283   | 97.87 |   282   | 98.22 |   279   |  100  |

По таблице несложно обнаружить, что по мере увеличения заказа нам сложно получить высокоэффективное решение на начальном этапе.



### 4、Анализ кода

#### I) Тип использования

```c++
using mat_d = vector<vector<double>>;
using path_t = vector<pair<size_t, size_t>>;
```

#### II) Случайная функция

```cpp
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
```

#### III) Дерево задач

```c++
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
```

#### IV) Минимизация элементов

```c++
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
```

#### V) Найдите кратчайший путь

```c++
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
```

#### VI) Обсудите классификацию левого и правого поддеревьев

```c++
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
```

#### VII) Основное решение проблемы TSP

```c++
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
```

#### VIII) Решать проблему

```c++
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
```

#### VIV) Путь печати и результат вывода

```c++
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
```



### 5、Оценка кода

Дизайн с использованием интеллектуальных указателей в определенной степени облегчает управление памятью и позволяет избежать проблемы утечек памяти. Значительным преимуществом является максимально возможное использование указателей вместо многократного создания объектов, так что вся программа занимает очень мало памяти. С точки зрения разработки алгоритма приоритет отдается левому поддереву (то есть пути), что делает код более эффективным.

