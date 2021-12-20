#define GL_SILENCE_DEPRECATION

#include <cmath>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <functional>
#include <chrono>
#include <GLUT/GLUT.h>
#include <iomanip>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

using vec_d = vector<double>;
using matr_d = vector<vector<double>>;

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
matr_d inverse(const matr_d &m)
{
	const double EPS = 1e-20;
	matr_d tmp = m;
	size_t sz = tmp.size();
	matr_d res;
	res.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		res[i].resize(sz);
		res[i][i] = 1;
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
						swap(res[i], res[m]);
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
				res[j][k] -= res[i][k] * temp;
			}
		}
	}
	for (int i = 0; i < sz; i++)
	{
		double first = tmp[i][i];
		for (int j = 0; j < sz; j++)
		{
			tmp[i][j] /= first;
			res[i][j] /= first;
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
				res[j][k] -= res[i][k] * temp;
			}
		}
	}
	return res;
}

class Integral_equation
{
private:
	double a;
	double b;
	static double K(double x, double s);
	double f(double x);
	double G(double x, double s);

	matr_d A;
	matr_d A_temp;
	matr_d B;
	const double step = 1e-2;
	double alpha;

public:
	Integral_equation(const double a, const double b);
	double Solve(double alpha);
	double Gold(double left, double right);
	void Print();
	void Print(const char index);
	double Spline(double x);
	matr_d x;
	matr_d y;
	int sz;
	~Integral_equation() {}
};
Integral_equation::Integral_equation(const double a, const double b) : a(a),
								       b(b)
{
	sz = (b - a) / step + 1;
	A.resize(sz);
	B.resize(sz);
	A_temp.resize(sz);

	x.resize(sz);

	for (size_t i = 0; i < sz; i++)
	{
		A[i].resize(sz);
		A_temp[i].resize(sz);
		B[i].resize(1);
	}
	for (size_t i = 0; i < sz; i++)
	{
		x[i].resize(1);
		x[i][0] = a + step * i;
	}
}
double Integral_equation::K(double x, double s)
{
	double miu = 0.2;
	return miu / (pow(miu, 2) + pow(x - s, 2));
}
double Integral_equation::G(double x1, double s)
{
	double res = 0;
	for (size_t i = 0; i < sz; i++)
	{
		res += K(x[i][0], x1) * K(x[i][0], s) * step;
	}
	return res;
}
double Integral_equation::f(double x)
{
	return cos(M_PI * x);
}
double Integral_equation::Solve(double alpha)
{
	this->alpha = alpha;
	double eps = 0;

	for (size_t i = 0; i < sz; i++)
	{
		B[i][0] = 0;
		for (size_t j = 0; j < sz; j++)
		{
			B[i][0] += step * K(x[j][0], x[i][0]) * f(x[j][0]);
		}
	}

	for (size_t i = 0; i < sz; i++)
	{
		for (size_t j = 0; j < sz; j++)
		{
			if (i == j)
			{
				A[i][j] = alpha + step * G(x[i][0], x[j][0]);
			}
			else
			{
				A[i][j] = step * G(x[i][0], x[j][0]);
			}
			A_temp[i][j] = step * K(x[i][0], x[j][0]);
		}
	}

	y = dot(inverse(A), B);
	matr_d f1 = dot(A_temp, y);
	matr_d _f(sz);
	for (size_t i = 0; i < sz; i++)
	{
		_f[i].resize(1);
		for (size_t j = 0; j < sz; j++)
		{
			_f[i][0] += step * K(x[j][0], x[i][0]) * f1[j][0];
		}
	}
	matr_d Ay = dot(A, y);
	for (size_t i = 0; i < sz; i++)
	{
		eps += pow(Ay[i][0] - _f[i][0], 2);
	}
	eps = sqrt(eps);
	return eps;
}
double Integral_equation::Gold(double left, double right)
{
	double epsilon = 1e-7, f_min, tau = (sqrt(5) - 1) / 2.0;
	double a_gss = left, b_gss = right, f_lambda = 0, f_mu = 0;
	double lambda = a_gss + (1.0 - tau) * (b_gss - a_gss), mu = a_gss + tau * (b_gss - a_gss);
	f_lambda = Solve(lambda);
	f_mu = Solve(mu);
	for (int i = 0; fabs(mu - lambda) > epsilon; i++)
	{
		if (f_lambda < f_mu)
		{
			b_gss = mu;
			mu = lambda;
			f_mu = f_lambda;
			lambda = a_gss + (1.0 - tau) * (b_gss - a_gss);
			f_lambda = Solve(lambda);
		}
		else
		{
			a_gss = lambda;
			lambda = mu;
			f_lambda = f_mu;
			mu = a_gss + tau * (b_gss - a_gss);
			f_mu = Solve(mu);
		}
	}
	f_min = Solve(0.5 * (lambda + mu));

	cout << "alpha = " << alpha << endl;
	cout << "eps = " << f_min << endl;
	return f_min;
}
double Integral_equation::Spline(double p)
{
	vec_d h(sz), s(sz), F(sz);
	matr_d m(sz);
	for (size_t i = 0; i < sz; i++)
	{
		m[i].resize(sz);
	}
	for (size_t i = sz - 1; i > 0; i--)
	{
		F[i] = (y[i][0] - y[i - 1][0]) / (x[i][0] - x[i - 1][0]);
		h[i - 1] = x[i][0] - x[i - 1][0];
	}
	for (size_t i = 1; i < sz - 1; i++)
	{
		m[i][i] = 2 * (h[i - 1] + h[i]);
		if (i != 1)
		{
			m[i][i - 1] = h[i - 1];
			m[i - 1][i] = h[i - 1];
		}
		m[i][sz - 1] = 6 * (F[i + 1] - F[i]);
	}

	for (size_t i = 1; i < sz - 2; i++)
	{
		double temp = (m[i + 1][i] / m[i][i]);
		for (size_t j = 1; j <= sz - 1; j++)
			m[i + 1][j] -= temp * m[i][j];
	}

	for (size_t i = sz - 2; i > 0; i--)
	{
		double sum = 0;
		for (size_t j = i; j <= sz - 2; j++)
			sum += m[i][j] * s[j];
		s[i] = (m[i][sz - 1] - sum) / m[i][i];
	}
	double res = 0;
	for (size_t i = 0; i < sz - 1; i++)
	{
		if (x[i][0] <= p && p <= x[i + 1][0])
		{
			double a1 = (s[i + 1] - s[i]) / (6 * h[i]);
			double b1 = s[i] / 2;
			double c1 = (y[i + 1][0] - y[i][0]) / h[i] - (2 * h[i] * s[i] + s[i + 1] * h[i]) / 6;
			double d1 = y[i][0];
			res = a1 * pow((p - x[i][0]), 3) + b1 * pow((p - x[i][0]), 2) + c1 * (p - x[i][0]) + d1;
		}
	}
	return res;
}
void Integral_equation::Print(const char index)
{
	matr_d *matr = nullptr;
	switch (index)
	{
	case 'A':
		matr = &A;
		break;
	case 'B':
		matr = &B;
		break;
	case 'y':
		matr = &y;
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
			cout << fixed << setprecision(6) << (*matr)[i][j] << " ";
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

void Integral_equation::Print()
{
	Print('A');
	Print('B');
	Print('y');
}

Integral_equation eq(-1, 1);

void Display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 1, 0);
	for (double i = -1; i <= 1; i += 1e-3)
		glVertex2f(i, eq.Spline(i) / 10);
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (size_t i = 0; i < eq.sz; i++)
		glVertex2f(eq.x[i][0], eq.y[i][0] / 10);
	glEnd();

	glFlush();
}
void PrintTime(high_resolution_clock::time_point start_time,
	       high_resolution_clock::time_point end_time)
{
	cout << "Time: "
	     << duration_cast<duration<double, milli>>(end_time - start_time).count()
	     << " ms" << endl;
}
int main(int argc, char *argv[])
{
	const auto start_time = high_resolution_clock::now();
	eq.Gold(0, 1);
	// eq.Print();
	const auto end_time = high_resolution_clock::now();
	PrintTime(start_time, end_time);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(1000, 1000);
	glutInitWindowSize(400, 400);
	glutCreateWindow("graph");
	glutDisplayFunc(&Display);
	glutMainLoop();

	return 0;
}
