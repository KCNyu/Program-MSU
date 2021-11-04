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
        for (int j = i; j <= n; j++)
        {
            tmp += (j + log(1 + x + j)) / (2 * i * j - 1);
        }
        res += 1 / tmp;
    }
    return res;
}
double parallel(double x, int n)
{
    double res = 0;
    int k = n - floor(n / pow(2, 0.5));
    //ShowLine("k = ", k);
#pragma omp parallel num_threads(2) reduction(+:res)
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
        int bound = k;
        if (num == 1) bound = n;
        for (int i = num*k+1; i <= bound; i++)
        {
            double tmp = 0;
            for (int j = i; j <= n; j++)
            {
                tmp += (j + log(1 + x + j)) / (2 * i * j - 1);
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
    Task("OMPBegin11");

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
