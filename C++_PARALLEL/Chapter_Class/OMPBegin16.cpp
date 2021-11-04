#include "pt4.h"
#include "omp.h"

#include "pt4.h"
#include "omp.h"

double non_parallel(double x, int n)
{
    double res = 0;
    for (int i = 1; i <= n; i++)
    {
        double tmp = 0;
        for (int j = i; j <= 2*n; j++)
        {
            tmp += (j + pow(x + j, 0.25)) / (2 * i * j - 1);
        }
        res += 1 / tmp;
    }
    return res;
}
double parallel(double x, int n)
{
    double res = 0;
    int k = ((3 * n * n )) / 2;
    int k0 = k / 4;
    int k_i[5] = { 0 };
    int C = 0, index = 1;
    for (int i = 1; i <= n; i++)
    {
        C += 2*n - i;
        if (C >= k0 )
        {
            k_i[index++] = i;
            C = 0;
            ShowLine("k = ", k_i[index-1]);
        }
    }
    k_i[index] = n;
#pragma omp parallel num_threads(4) reduction(+:res)
    {
        int num = omp_get_thread_num();
        int num_procs = omp_get_num_procs();
        int num_threads = omp_get_num_threads();
        int count = 0;
        if (num == 0)
        {
            ShowLine("num_procs: ", num_procs);
            ShowLine("num_threads: ", num_threads);
        }
        double time = omp_get_wtime();
        for (int i = k_i[num]+1; i <= k_i[num+1]; i++)
        {
            double tmp = 0;
            for (int j = i; j <= 2*n; j++)
            {
                tmp += (j + pow(x + j, 0.25)) / (2 * i * j - 1);
                count++;
            }
            res += 1 / tmp;
        }
        double p_time = omp_get_wtime() - time;
        Show("thread_num:", num);
        Show("Count:", count);
        ShowLine("Thread time:", p_time);
    }
    return res;
}
void Solve()
{
    Task("OMPBegin16");

    double X;
    int N;
    // non_parallel
    pt >> X >> N;
    double t = omp_get_wtime();
    double res = non_parallel(X, N);
    double np_time = omp_get_wtime() - t;
    ShowLine("Non-parallel time: ", np_time);
    pt << res;

    //prarallel
    pt >> X >> N;
    t = omp_get_wtime();
    res = parallel(X, N);
    double p_time = omp_get_wtime() - t;
    ShowLine("Total parallel time: ", p_time);
    ShowLine("Rate: ", np_time / p_time);
    pt << res;
}