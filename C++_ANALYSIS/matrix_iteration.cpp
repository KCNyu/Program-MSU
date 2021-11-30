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

class matrix_iteration
{
private:
	matr_d matr_A;
	matr_d matr_A1;
	matr_d matr_A2;
	matr_d matr_B;
	matr_d matr_inverse_B;
	matr_d matr_inverse_B_A;
	vec_d vec_f;
	vec_d vec_w;
	vec_d vec_r;
	vec_d vec_x;
	double tau;
	const int sz;
	int iteration = 0;

public:
	matrix_iteration(const int n);
	void init_matr_B(const double w);
	void init_matr_inverse_B();
	void init_matr_inverse_B_A();
	void iterate_vec_r();
	void iterate_vec_w();
	void iterate_vec_x();
	void iterate_tau();
	void iterate(const double eps);
	void print_matr(const char index);
	void print_vec(const char index);
	void print();
	const int get_iteration() { return iteration; }
	~matrix_iteration();
};

matrix_iteration::matrix_iteration(const int n) : sz(n)
{
	matr_A.resize(sz);
	matr_A1.resize(sz);
	matr_A2.resize(sz);
	vec_f.resize(sz);
	vec_x.resize(sz);
	vec_r.resize(sz);
	vec_w.resize(sz);

	for (int i = 1; i <= sz; i++)
	{
		double fi = 0;
		matr_A[i - 1].resize(sz);
		matr_A1[i - 1].resize(sz);
		matr_A2[i - 1].resize(sz);

		for (int j = 1; j < i; j++)
		{
			matr_A[i - 1][j - 1] = 1. / (i + j - 1);
			matr_A1[i - 1][j - 1] = matr_A[i - 1][j - 1];

			fi += matr_A[i - 1][j - 1];
		}

		matr_A[i - 1][i - 1] = 1. / (i + i - 1);
		matr_A1[i - 1][i - 1] = matr_A[i - 1][i - 1] * 0.5;
		matr_A2[i - 1][i - 1] = matr_A1[i - 1][i - 1];

		fi += matr_A[i - 1][i - 1];

		for (int j = i + 1; j <= sz; j++)
		{
			matr_A[i - 1][j - 1] = 1. / (i + j - 1);
			matr_A2[i - 1][j - 1] = matr_A[i - 1][j - 1];

			fi += matr_A[i - 1][j - 1];
		}

		vec_f[i - 1] = fi;
		vec_x[i - 1] = 1. / 2;
	}
}
void matrix_iteration::print_vec(const char index)
{
	vec_d *vec;
	switch (index)
	{
	case 'f':
		vec = &vec_f;
		break;
	case 'w':
		vec = &vec_w;
		break;
	case 'r':
		vec = &vec_r;
		break;
	case 'x':
		vec = &vec_x;
		break;
	default:
		break;
	}

	string indexline = "=========VEC_";
	indexline += index;
	indexline += "========";

	cout << indexline << endl;
	for (auto elem : *vec)
	{
		cout.width(10);
		cout << fixed << setprecision(3) << elem << endl;
	}
}
void matrix_iteration::print_matr(const char index)
{
	matr_d *matr;
	switch (index)
	{
	case 'A':
		matr = &matr_A;
		break;
	case '1':
		matr = &matr_A1;
		break;
	case '2':
		matr = &matr_A2;
		break;
	case 'B':
		matr = &matr_B;
		break;
	case 'b':
		matr = &matr_inverse_B;
		break;
	case 'a':
		matr = &matr_inverse_B_A;
	default:
		break;
	}

	string indexline = "=========MATR_";
	indexline += index;
	indexline += "========";

	cout << indexline << endl;
	for (auto row : *matr)
	{
		for (auto elem : row)
		{
			cout.width(10);
			cout << fixed << setprecision(3) << elem << " ";
		}
		cout << endl;
	}
}
void matrix_iteration::print()
{
	print_matr('A');
	print_matr('1');
	print_matr('2');
	print_matr('B');
	print_matr('b');
	print_matr('a');
	print_vec('f');
	print_vec('w');
	print_vec('r');
	print_vec('x');
}
void matrix_iteration::init_matr_B(const double w)
{
	matr_d matr_t1(sz);
	matr_d matr_t2(sz);

	for (int i = 0; i < sz; i++)
	{
		matr_t1[i].resize(sz);
		matr_t2[i].resize(sz);
		for (int j = 0; j < sz; j++)
		{
			matr_t1[i][j] = w * matr_A1[i][j];
			matr_t2[i][j] = w * matr_A2[i][j];
			if (i == j)
			{
				matr_t1[i][j] += 1;
				matr_t2[i][j] += 1;
			}
		}
	}

	matr_B.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		matr_B[i].resize(sz);
		for (int j = 0; j < sz; j++)
		{
			for (int k = 0; k < sz; k++)
				matr_B[i][j] += matr_t1[i][k] * matr_t2[k][j];
		}
	}
}
void matrix_iteration::init_matr_inverse_B()
{
	const double EPS = 0.0000000001;
	matr_d tmp = matr_B;
	matr_inverse_B.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		matr_inverse_B[i].resize(sz);
		matr_inverse_B[i][i] = 1;
	}
	for (int i = 0; i < sz - 1; i++)
	{
		for (int j = i + 1; j < sz; j++)
		{
			if (tmp[i][i] < EPS && tmp[i][i] > -1 * EPS)
			{
				bool flag = true;
				for (int m = i + 1; m < sz; m++)
				{
					if (tmp[m][i] < EPS && tmp[m][i] > -1 * EPS)
						continue;
					else
					{
						swap(tmp[i], tmp[m]);
						swap(matr_inverse_B[i], matr_inverse_B[m]);
						flag = false;
					}
				}
				if (flag)
					throw "Doesn't have result!\n";
			}
			double temp = tmp[j][i] / tmp[i][i];
			for (int k = 0; k < sz; k++)
			{
				tmp[j][k] -= tmp[i][k] * temp;
				matr_inverse_B[j][k] -= matr_inverse_B[i][k] * temp;
			}
		}
	}
	for (int i = 0; i < sz; i++)
	{
		double first = tmp[i][i];
		for (int j = 0; j < sz; j++)
		{
			tmp[i][j] /= first;
			matr_inverse_B[i][j] /= first;
		}
	}
	for (int i = sz - 1; i > 0; i--)
	{
		for (int j = 0; j <= i - 1; j++)
		{
			double temp = tmp[j][i] / tmp[i][i];
			for (int k = 0; k < sz; k++)
			{
				tmp[j][k] -= tmp[i][k] * temp;
				matr_inverse_B[j][k] -= matr_inverse_B[i][k] * temp;
			}
		}
	}
}
void matrix_iteration::init_matr_inverse_B_A()
{
	matr_inverse_B_A.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		matr_inverse_B_A[i].resize(sz);
		for (int j = 0; j < sz; j++)
		{
			for (int k = 0; k < sz; k++)
				matr_inverse_B_A[i][j] += matr_inverse_B[i][k] * matr_A[k][j];
		}
	}
}
void matrix_iteration::iterate_vec_r()
{
	for (int i = 0; i < sz; i++)
	{
		vec_r[i] = 0;
		for (int j = 0; j < sz; j++)
		{
			vec_r[i] += matr_A[i][j] * vec_x[j];
		}
		vec_r[i] -= vec_f[i];
	}
}
void matrix_iteration::iterate_vec_w()
{
	for (int i = 0; i < sz; i++)
	{
		vec_w[i] = 0;
		for (int j = 0; j < sz; j++)
		{
			vec_w[i] += matr_inverse_B[i][j] * vec_r[j];
		}
	}
}
void matrix_iteration::iterate_vec_x()
{
	for (int i = 0; i < sz; i++)
	{
		vec_x[i] -= tau * vec_w[i];
	}
}
void matrix_iteration::iterate_tau()
{
	vec_d Aw(sz);
	vec_d BAw(sz);
	double a = 0, b = 0;
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			Aw[i] += matr_A[i][j] * vec_w[j];
			BAw[i] += matr_inverse_B_A[i][j] * vec_w[j];
		}
		a += Aw[i] * vec_w[i];
		b += BAw[i] * Aw[i];
	}
	tau = a / b;
}
void matrix_iteration::iterate(const double eps)
{
	init_matr_inverse_B();
	init_matr_inverse_B_A();

	double mis;
	do
	{
		iterate_vec_r();
		iterate_vec_w();
		iterate_tau();
		iterate_vec_x();
		mis = 0;
		for (int i = 0; i < sz; i++)
		{
			double tmp = fabs(vec_x[i] - 1);
			mis += pow(tmp, 2);
		}
		mis = pow(mis, 0.5);
		iteration++;
	} while (mis >= eps);
}
matrix_iteration::~matrix_iteration()
{
}
void PrintTime(high_resolution_clock::time_point start_time,
	       high_resolution_clock::time_point end_time)
{
	cout << "Time: "
	     << duration_cast<duration<double, milli>>(end_time - start_time).count()
	     << " ms" << endl;
}
void test(const int n, const double w, const double mis, bool option_print)
{
	const auto start_time = high_resolution_clock::now();
	matrix_iteration m(n);
	m.init_matr_B(w);
	m.iterate(mis);
	const auto end_time = high_resolution_clock::now();
	if (option_print)
		m.print();
	cout << "iteration = " << m.get_iteration() << endl;
	PrintTime(start_time, end_time);
}
int main(int argc, char const *argv[])
{
	test(100, 1.783, 0.01, false);
	// w ≈ 1.783
	return 0;
}