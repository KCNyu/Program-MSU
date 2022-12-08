#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>
#include "mpi.h"
using namespace std;

#define RANDOM_UPPERBOUND 1000

int procSize, procRank;
double executionTime;
int sortDirection = 0;
MPI_Datatype pointType;

class Point
{
public:
    float coord[2];
    int index;
};

bool operator<(const Point &p1, const Point &p2)
{
    return p1.coord[sortDirection] < p2.coord[sortDirection];
}
bool operator>(const Point &p1, const Point &p2)
{
    return p1.coord[sortDirection] > p2.coord[sortDirection];
}
void commitPointType(MPI_Datatype &pointType)
{
    int block[2] = {2, 1};
    MPI_Datatype types[2] = {MPI_FLOAT, MPI_INT};

    Point dummyPoint;
    MPI_Aint disp[2];
    MPI_Aint baseAddr;

    MPI_Get_address(&dummyPoint, &baseAddr);
    MPI_Get_address(&dummyPoint.coord[0], &disp[0]);
    MPI_Get_address(&dummyPoint.index, &disp[1]);

    disp[0] -= baseAddr;
    disp[1] -= baseAddr;

    MPI_Type_create_struct(2, block, disp, types, &pointType);
    MPI_Type_commit(&pointType);
}
float randomFloat()
{
    return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / RANDOM_UPPERBOUND));
}

class Test
{
private:
    vector<Point> points;

public:
    Test(const vector<Point> &points) : points(points)
    {
    }
    void run()
    {
        for (int i = 1; i < points.size(); i++)
        {
            assert(!(points[i - 1] > points[i]));
        }
        Point p;
        MPI_Status status;
        MPI_Request request;
        if (procRank < procSize - 1)
        {
            MPI_Isend(&points.back(), 1, pointType, procRank + 1, 1,
                      MPI_COMM_WORLD, &request);
        }
        if (procRank > 0)
        {
            MPI_Recv(&p, 1, pointType, procRank - 1, 1, MPI_COMM_WORLD, &status);
            assert(!(p > points.front()));
        }
    }
};

class Task
{
private:
    vector<Point> points;
    int n1, n2;
    int total;

public:
    Task(const int n1, const int n2) : n1(n1), n2(n2), total(n1 * n2)
    {
        if (procSize == 1)
        {
            points = randomPoints(0, total);
        }
        else
        {
            int arrSz = ceil(static_cast<double>(total) / procSize);
            points = randomPoints(procRank * arrSz, arrSz);
        }
    }
    vector<Point> randomPoints(int start, int arrSz)
    {
        srand(time(NULL) + start);
        vector<Point> points;
        points.reserve(arrSz);
        for (int i = start; i < start + arrSz; i++)
        {
            Point p;
            p.coord[0] = randomFloat();
            p.coord[1] = randomFloat();
            p.index = i;
            points.push_back(p);
        }
        return points;
    }
    void serialSort()
    {
        sort(points.begin(), points.end());
    }
    void runSerial()
    {
        double startTime = MPI_Wtime();
        serialSort();
        executionTime = MPI_Wtime() - startTime;

        Test test(points);
        test.run();
    }
    void merger(int leftRank, int rightRank)
    {
        vector<Point> leftPoints, rightPoints;
        if (procRank == leftRank)
        {
            rightPoints.resize(points.size());
            MPI_Sendrecv(&points[0], points.size(), pointType, rightRank, 0,
                         &rightPoints[0], rightPoints.size(), pointType, rightRank, 0,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            leftPoints = points;
        }
        else if (procRank == rightRank)
        {
            leftPoints.resize(points.size());
            MPI_Sendrecv(&points[0], points.size(), pointType, leftRank, 0,
                         &leftPoints[0], leftPoints.size(), pointType, leftRank, 0,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            rightPoints = points;
        }
        else
        {
            return;
        }

        int maxRank = max(leftRank, rightRank);
        int m = points.size();
        vector<Point> temp(m);
        if (procRank != maxRank)
        {
            for (int ia = 0, ib = 0, k = 0; k < m;)
            {
                if (leftPoints[ia] < rightPoints[ib])
                {
                    temp[k++] = leftPoints[ia++];
                }
                else
                {
                    temp[k++] = rightPoints[ib++];
                }
            }
        }
        else
        {
            for (int ia = m - 1, ib = m - 1, k = m - 1; k >= 0;)
            {
                if (leftPoints[ia] > rightPoints[ib])
                {
                    temp[k--] = leftPoints[ia--];
                }
                else
                {
                    temp[k--] = rightPoints[ib--];
                }
            }
        }
        points = temp;
    }
    void B(int first, int step, int count)
    {
        if (count < 2)
        {
            return;
        }
        if (count == 2)
        {
            merger(first, first + step);
            return;
        }
        int count1 = count / 2;
        B(first, step, count1);
        B(first + step * count1, step, count - count1);
        S(first, first + step * count1, step, count1, count - count1);
    }

    void S(size_t startIndex1, size_t startIndex2, size_t step, size_t size1, size_t size2)
    {
        if (size1 * size2 < 1)
        {
            return;
        }
        if (size1 == 1 && size2 == 1)
        {
            merger(startIndex1, startIndex2);
            return;
        }
        size_t oddNum = size1 - size1 / 2;
        size_t evenNum = size2 - size2 / 2;
        S(startIndex1, startIndex2, 2 * step, oddNum, evenNum);
        S(startIndex1 + step, startIndex2 + step, 2 * step, size1 - oddNum, size2 - evenNum);

        for (size_t i = 1; i < size1 - 1; i += 2)
        {
            merger(startIndex1 + i * step, startIndex1 + (i + 1) * step);
        }

        size_t compStartIndex;
        if (size1 % 2 == 0)
        {
            merger(startIndex1 + step * (size1 - 1), startIndex2);
            compStartIndex = 1;
        }
        else
        {
            compStartIndex = 0;
        }
        while (compStartIndex < size2 - 1)
        {
            merger(startIndex2 + compStartIndex * step, startIndex2 + (compStartIndex + 1) * step);
            compStartIndex += 2;
        }
    }
    void parallelSort()
    {
        serialSort();
        B(0, 1, procSize);
    }
    void runParallel()
    {
        commitPointType(pointType);

        double startTime = MPI_Wtime();
        parallelSort();
        double procExecutionTime = MPI_Wtime() - startTime;

        MPI_Reduce(&procExecutionTime, &executionTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

        Test test(points);
        test.run();
        MPI_Type_free(&pointType);
    }
    void run()
    {
        MPI_Barrier(MPI_COMM_WORLD);
        if (procRank == 0)
        {
            cout << "Total points: " << total << endl;
            cout << "Processors: " << procSize << endl;
        }
        if (procSize == 1)
        {
            runSerial();
        }
        else
        {
            runParallel();
        }
        if (procRank == 0)
        {
            cout << "Execution time: " << executionTime << endl;
        }
        MPI_Finalize();
    }
};
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    if (argc < 3)
    {
        if (procRank == 0)
        {
            cout << "Usage: " << argv[0] << " n1 n2 <sortDirection>[=0]" << endl;
        }
        MPI_Finalize();
        return 0;
    }
    if (argc == 4)
    {
        sortDirection = atoi(argv[3]);
    }

    Task task(atoi(argv[1]), atoi(argv[2]));
    task.run();
    return 0;
}
