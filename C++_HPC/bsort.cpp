#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

class SortedArray
{
public:
    SortedArray(size_t n)
    {
        for (size_t i = 0; i < n; i++)
        {
            arr.push_back(rand() % 10000);
        }
        sort(arr.begin(), arr.end());
    }
    SortedArray(const vector<int> &v) : arr(v) {}
    vector<int> arr;
};

class MergeSortedArrays
{
private:
    SortedArray sortedArray1;
    SortedArray sortedArray2;
    vector<int> mergedArray;
    vector<int> clockCycle;
    size_t compCount = 0;
    vector<pair<size_t, size_t>> tacts;

public:
    MergeSortedArrays(size_t n1, size_t n2) : sortedArray1(n1), sortedArray2(n2)
    {
        mergedArray.resize(n1 + n2);
        mergedArray.assign(sortedArray1.arr.begin(), sortedArray1.arr.end());
        mergedArray.insert(mergedArray.end(), sortedArray2.arr.begin(), sortedArray2.arr.end());
        clockCycle.resize(n1 + n2);
        tacts.reserve(n1 + n2);
    }
    MergeSortedArrays(const vector<int> &v1, const vector<int> &v2) : sortedArray1(v1), sortedArray2(v2)
    {
        mergedArray.resize(v1.size() + v2.size());
        mergedArray.assign(sortedArray1.arr.begin(), sortedArray1.arr.end());
        mergedArray.insert(mergedArray.end(), sortedArray2.arr.begin(), sortedArray2.arr.end());
        clockCycle.resize(v1.size() + v2.size());
        tacts.reserve(v1.size() + v2.size());
    }
    void comparator(const size_t &a, const size_t &b, size_t depth)
    {
        clockCycle[a] = depth;
        clockCycle[b] = depth;
        compCount++;
        tacts.emplace_back(a, b);
        if (mergedArray[a] > mergedArray[b])
        {
            swap(mergedArray[a], mergedArray[b]);
        }
    }
    void merge(size_t startIndex1, size_t startIndex2, size_t step, size_t size1, size_t size2, size_t depth)
    {
        if (size1 * size2 < 1)
        {
            return;
        }
        if (size1 == 1 && size2 == 1)
        {
            comparator(startIndex1, startIndex2, depth);
            return;
        }
        size_t oddNum = size1 - size1 / 2;
        size_t evenNum = size2 - size2 / 2;
        merge(startIndex1, startIndex2, 2 * step, oddNum, evenNum, depth + 1);
        merge(startIndex1 + step, startIndex2 + step, 2 * step, size1 - oddNum, size2 - evenNum, depth + 1);

        for (size_t i = 1; i < size1 - 1; i += 2)
        {
            comparator(startIndex1 + i * step, startIndex1 + (i + 1) * step, depth);
        }

        size_t compStartIndex;
        if (size1 % 2 == 0)
        {
            comparator(startIndex1 + step * (size1 - 1), startIndex2, depth);
            compStartIndex = 1;
        }
        else
        {
            compStartIndex = 0;
        }
        while (compStartIndex < size2 - 1)
        {
            comparator(startIndex2 + compStartIndex * step, startIndex2 + (compStartIndex + 1) * step, depth);
            compStartIndex += 2;
        }
    }
    size_t getSize1()
    {
        return sortedArray1.arr.size();
    }
    size_t getSize2()
    {
        return sortedArray2.arr.size();
    }
    size_t getCompCount()
    {
        return compCount;
    }
    size_t getMaxClockCycle()
    {
        return *max_element(clockCycle.begin(), clockCycle.end());
    }
    vector<pair<size_t, size_t>> getTacts()
    {
        return tacts;
    }
    bool isSorted()
    {
        for (size_t i = 0; i < mergedArray.size() - 1; i++)
        {
            if (mergedArray[i] > mergedArray[i + 1])
            {
                return false;
            }
        }
        return true;
    }
};

class Task
{
private:
    size_t p1;
    size_t p2;
    MergeSortedArrays mergeSortedArrays;

public:
    Task(size_t p1, size_t p2) : mergeSortedArrays(p1, p2)
    {
        mergeSortedArrays.merge(0, p1, 1, p1, p2, 1);
    }
    Task(const vector<int> &v1, const vector<int> &v2) : mergeSortedArrays(v1, v2)
    {
        mergeSortedArrays.merge(0, v1.size(), 1, v1.size(), v2.size(), 1);
    }
    void outputToFile()
    {
        ofstream fout("output.txt");
        fout << mergeSortedArrays.getSize1() << " " << mergeSortedArrays.getSize2() << " " << 0 << endl;
        for (auto &i : mergeSortedArrays.getTacts())
        {
            fout << "  " << i.first << "  " << i.second << endl;
        }
        fout << mergeSortedArrays.getCompCount() << endl;
        fout << mergeSortedArrays.getMaxClockCycle() << endl;
        fout.close();
    }
    bool isSorted()
    {
        return mergeSortedArrays.isSorted();
    }
    bool isCorrect()
    {
        size_t n = mergeSortedArrays.getSize1() + mergeSortedArrays.getSize2();
        double rightTacts = ((log2(n)) * ((log2(n) + 1))) / 2.0;
        return mergeSortedArrays.getMaxClockCycle() <= rightTacts;
    }
};

class Test
{
public:
    void run(size_t n1, size_t n2)
    {
        Task task(n1, n2);
        assert(task.isSorted());
        assert(task.isCorrect());
    }
    void run(const vector<int> &v1, const vector<int> &v2)
    {
        Task task(v1, v2);
        assert(task.isSorted());
        assert(task.isCorrect());
    }
    void fullTest()
    {
        for (size_t fullSize = 1; fullSize <= 24; fullSize++)
        {
            vector<int> full;
            for (size_t cur = 0; cur < fullSize; cur++)
            {
                full.push_back(cur);
            }
            for (size_t i = 0; i < (1 << full.size()); i++)
            {
                vector<int> subset1;
                vector<int> subset2;
                for (size_t j = 0; j < full.size(); j++)
                {
                    if (i & (1 << j))
                    {
                        subset1.push_back(full[j]);
                    }
                    else
                    {
                        subset2.push_back(full[j]);
                    }
                }
                run(subset1, subset2);
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ./a.out <size of array 1> <size of array 2>" << endl;
        return 0;
    }
    size_t size1 = atol(argv[1]);
    size_t size2 = atol(argv[2]);
    Task task(size1, size2);
    task.outputToFile();
    cout << "Running test for " << size1 << " " << size2 << endl;
    Test test;
    test.run(size1, size2);
    cout << "Test passed" << endl;

    cout << "Running test from 0 to 24" << endl;
    test.fullTest();
    cout << "Test passed" << endl;
    return 0;
}
