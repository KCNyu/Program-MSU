#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

using matr_d = vector<vector<double>>;
using vec_d = vector<double>;

inline matr_d dot(const matr_d &m1, const matr_d &m2)
{
	matr_d res(m1.size());
	for (size_t i = 0; i < m1.size(); i++)
	{
		res[i].resize(m2[0].size());
		for (size_t j = 0; j < m2[0].size(); j++)
		{
			double sum = 0;
			for (size_t k = 0; k < m1[0].size(); k++)
			{
				sum += m1[i][k] * m2[k][j];
			}
			res[i][j] = sum;
		}
	}
	return res;
}
inline matr_d dot(const matr_d &m, const double num)
{
	matr_d res(m.size());
	for (size_t i = 0; i < m.size(); i++)
	{
		res[i].resize(m[0].size());
		for (size_t j = 0; j < m[0].size(); j++)
		{
			res[i][j] = m[i][j] * num;
		}
	}
	return res;
}
inline matr_d transpose(const matr_d &m)
{
	matr_d res(m[0].size());
	for (size_t i = 0; i < m.size(); i++)
	{
		for (size_t j = 0; j < m[0].size(); j++)
		{
			res[j].push_back(m[i][j]);
		}
	}
	return res;
}
class matrix_Householder
{
private:
	matr_d matr_A;
	matr_d matr_P;
	matr_d vec_v;
	const int sz;

public:
	matrix_Householder(const int n);
	void householder();
	void print_matr(const char index);
	void print_matr();
	~matrix_Householder();
};

matrix_Householder::matrix_Householder(const int n) : sz(n)
{
	matr_A.resize(sz);
	vec_v.resize(sz);

	for (int i = 0; i < sz; i++)
	{
		matr_A[i].resize(sz);
		vec_v[i].resize(1);
		for (int j = 0; j <= i; j++)
		{
			matr_A[i][j] = j + 1;
		}
		for (int j = i + 1; j < sz; j++)
		{
			matr_A[i][j] = i + 1;
		}
	}
}
void matrix_Householder::householder()
{
	for (int k = 1; k < sz - 1; k++)
	{
		double r = 0;
		for (int l = k; l < sz; l++)
		{
			r += matr_A[k - 1][l] * matr_A[k - 1][l];
		}
		r = sqrt(r);
		if (r * matr_A[k - 1][k] > 0)
		{
			r = -r;
		}
		double h = -1. / (r * r - r * matr_A[k - 1][k]);
		for (int i = 0; i < sz; i++)
		{
			vec_v[i][0] = 0;
		}
		vec_v[k][0] = matr_A[k - 1][k] - r;
		for (int l = k + 2; l < sz + 1; l++)
		{
			vec_v[l - 1][0] = matr_A[k - 1][l - 1];
		}
		matr_P = dot(dot(vec_v, transpose(vec_v)), h);
		for (int l = 1; l < sz + 1; l++)
		{
			matr_P[l - 1][l - 1] += 1;
		}
		matr_A = dot(dot(matr_P, matr_A), matr_P);
	}
}
matrix_Householder::~matrix_Householder()
{
}
void matrix_Householder::print_matr(const char index)
{
	matr_d *matr = nullptr;
	switch (index)
	{
	case 'A':
		matr = &matr_A;
		break;
	case 'P':
		matr = &matr_P;
		break;
	default:
		break;
	}

	string indexline = "=========MATR_";
	indexline += index;
	indexline += "========\n[";

	cout << indexline;
	for (int i = 0; i < matr->size(); i++)
	{
		if (i != 0)
		{
			cout << " ";
		}
		for (int j = 0; j < (*matr)[0].size(); j++)
		{
			cout.width(10);
			cout << fixed << setprecision(3) << (*matr)[i][j] << " ";
		}
		if (i < matr->size() - 1)
		{
			cout << ";" << endl;
		}
		else
		{
			cout << "]" << endl;
		}
	}
}
void matrix_Householder::print_matr()
{
	print_matr('A');
	print_matr('P');
}
void PrintTime(high_resolution_clock::time_point start_time,
	       high_resolution_clock::time_point end_time)
{
	cout << "Time: "
	     << duration_cast<duration<double, milli>>(end_time - start_time).count()
	     << " ms" << endl;
}
void test(const int n, bool print_option)
{
	matrix_Householder m(n);
	if (print_option)
	{
		m.print_matr('A');
	}
	const auto start_time = high_resolution_clock::now();
	m.householder();
	const auto end_time = high_resolution_clock::now();
	if (print_option)
	{
		m.print_matr();
	}
	PrintTime(start_time, end_time);
}
int main(int argc, char const *argv[])
{
	bool print_option = true;
	if (argc == 2)
		print_option = false;
	cout << "Matrix Dim = ";
	int n;
	cin >> n;
	test(n, print_option);
	return 0;
}
