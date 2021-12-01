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
	vec_d vec_f;
	vec_d vec_w;
	vec_d vec_w_temp;
	vec_d vec_r;
	vec_d vec_r_temp;
	vec_d vec_x;
	vec_d vec_x_temp;
	double tau;
	double tau_temp;
	const int sz;
	int iteration = 0;
	double alpha = 1;

public:
	matrix_iteration(const int n);
	void init_matr_B();
	void iterate_vec_r();
	void iterate_vec_w();
	void iterate_vec_x();
	void iterate_tau();
	void iterate_alpha();
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
	vec_x_temp.resize(sz);
	vec_r.resize(sz);
	vec_r_temp.resize(sz);
	vec_w.resize(sz);
	vec_w_temp.resize(sz);

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
	vec_d *vec = nullptr;
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
	matr_d *matr = nullptr;
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
	print_vec('f');
	print_vec('w');
	print_vec('r');
	print_vec('x');
}
void matrix_iteration::init_matr_B()
{
	matr_B.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		matr_B[i].resize(sz);
		matr_B[i][i] = 1;
	}
}
void matrix_iteration::iterate_vec_r()
{
	for (int i = 0; i < sz; i++)
	{
		vec_r_temp[i] = vec_r[i];
	}
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
		vec_w_temp[i] = vec_w[i];
	}
	for (int i = 0; i < sz; i++)
	{
		vec_w[i] = 0;
		for (int j = 0; j < sz; j++)
		{
			vec_w[i] += matr_B[i][j] * vec_r[j];
		}
	}
}
void matrix_iteration::iterate_vec_x()
{
	vec_d temp = vec_x;
	vec_d b_ta(sz);
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			b_ta[i] += alpha*(matr_B[i][j]-tau*matr_A[i][j])*vec_x[j];
		}
	}
	for (int i = 0; i < sz; i++)
	{
		vec_x[i] = b_ta[i]+(1-alpha)*vec_x_temp[i]+alpha*tau*vec_f[i];
		vec_x_temp[i] = temp[i];
	}
}
void matrix_iteration::iterate_tau()
{
	tau_temp = tau;
	vec_d Aw(sz);
	double a = 0, b = 0;
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			Aw[i] += matr_A[i][j] * vec_w[j];
		}
		a += vec_w[i] * vec_r[i];
		b += Aw[i] * vec_w[i];
	}
	tau = a / b;
}
void matrix_iteration::iterate_alpha()
{
	vec_d Aw(sz);
	double a = 0, b = 0;
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			Aw[i] += matr_A[i][j] * vec_w_temp[j];
		}
		a += vec_w[i] * vec_r[i];
		b += Aw[i] * vec_r_temp[i];
	}
	alpha = 1./(1-tau_temp/tau*a/b/alpha);
}
void matrix_iteration::iterate(const double eps)
{
	init_matr_B();
	double mis;
	do
	{
		iterate_vec_r();
		iterate_vec_w();
		iterate_tau();
		iterate_vec_x();
		if (iteration >= 1) iterate_alpha();
		mis = 0;
		for (int i = 0; i < sz; i++)
		{
			double tmp = fabs(vec_x[i] - 1);
			mis += pow(tmp, 2);
		}
		mis = pow(mis, 0.5);
		iteration++;
	} while (iteration < 5000);
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
	m.iterate(mis);
	const auto end_time = high_resolution_clock::now();
	if (option_print)
		m.print();
	cout << "iteration = " << m.get_iteration() << endl;
	PrintTime(start_time, end_time);
}
int main(int argc, char const *argv[])
{
	test(10, 1.783, 0.01, true);
	// w ≈ 1.783
	return 0;
}