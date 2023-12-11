#pragma once

#include <tuple>
#include <iostream>
#include <climits>

struct Scale
{

    int x_l, x_r, x_len;
    int y_l, y_r, y_len;
    int z_l, z_r, z_len;
    int size;

    enum class Axis
    {
        X,
        Y,
        Z
    };

    Scale() : x_l(0), x_r(0), y_l(0), x_len(0), y_r(0), y_len(0), z_l(0), z_r(0), z_len(0), size(0) {}
    Scale(int N) : x_l(0), x_r(N), x_len(N + 1), y_l(0), y_r(N), y_len(N + 1), z_l(0), z_r(N), z_len(N + 1), size(x_len * y_len * z_len) {}
    Scale(int x_l, int x_r, int y_l, int y_r, int z_l, int z_r) : x_l(x_l), x_r(x_r), y_l(y_l), y_r(y_r), z_l(z_l), z_r(z_r)
    {
        x_len = x_r - x_l + 1;
        y_len = y_r - y_l + 1;
        z_len = z_r - z_l + 1;
        size = x_len * y_len * z_len;
    }

    std::tuple<int, int, int, int, int, int> unpack() const
    {
        return std::make_tuple(x_l, x_r, y_l, y_r, z_l, z_r);
    }
    inline const bool contains(int i, int j, int k) const
    {
        return i >= x_l && i <= x_r && j >= y_l && j <= y_r && k >= z_l && k <= z_r;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Scale &s)
    {
        os << "x_l: " << s.x_l << " x_r: " << s.x_r << " x_len: " << s.x_len << std::endl;
        os << "y_l: " << s.y_l << " y_r: " << s.y_r << " y_len: " << s.y_len << std::endl;
        os << "z_l: " << s.z_l << " z_r: " << s.z_r << " z_len: " << s.z_len << std::endl;
        os << "size: " << s.size << std::endl;
        return os;
    }

    static std::tuple<int, int, int> split_triplet(int number)
    {
        std::tuple<int, int, int> minSumTriplet;
        int minSum = INT_MAX;

        for (int a = 1; a * a * a <= number; ++a)
        {
            if (number % a == 0)
            {
                for (int b = a; b * b <= number / a; ++b)
                {
                    if ((number / a) % b == 0)
                    {
                        int c = number / (a * b);
                        int sum = a + b + c;
                        if (sum < minSum)
                        {
                            minSum = sum;
                            minSumTriplet = std::make_tuple(a, b, c);
                        }
                    }
                }
            }
        }

        return minSumTriplet;
    }
};

struct Cube
{
    Scale scale;
    double *data;

    Cube() : scale(), data(nullptr) {}
    Cube(int N) : scale(N)
    {
        data = new double[scale.size];
        for (int i = 0; i < scale.size; i++)
        {
            data[i] = 0;
        }
    }
    Cube(Scale scale) : scale(scale)
    {
        data = new double[scale.size];
        for (int i = 0; i < scale.size; i++)
        {
            data[i] = 0;
        }
    }
    Cube(const Cube &c) : scale(c.scale)
    {
        data = new double[scale.size];
        for (int i = 0; i < scale.size; i++)
        {
            data[i] = c.data[i];
        }
    }
    Cube(int x_l, int x_r, int y_l, int y_r, int z_l, int z_r) : scale(x_l, x_r, y_l, y_r, z_l, z_r)
    {
        data = new double[scale.size];
        for (int i = 0; i < scale.size; i++)
        {
            data[i] = 0;
        }
    }
    Cube &operator=(Cube &&c) noexcept
    {
        if (this != &c)
        {
            delete[] data;
            data = std::move(c.data);
            scale = std::move(c.scale);

            c.data = nullptr;
            c.scale = Scale();
        }
        return *this;
    }
    ~Cube()
    {
        delete[] data;
    }
    inline double &operator()(int i, int j, int k) const
    {
        return data[(i - scale.x_l) * scale.y_len * scale.z_len + (j - scale.y_l) * scale.z_len + (k - scale.z_l)];
    }
};