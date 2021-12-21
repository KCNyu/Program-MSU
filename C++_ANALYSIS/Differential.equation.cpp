#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <vector>
#include <cmath>
#include <GLUT/GLUT.h>
using namespace std;

using vec_d = vector<double>;
using matr_d = vector<vector<double>>;

class Differential_equation
{
private:
	const double a;
	const double b;
	const double c;
	const double step;

	double index;
	matr_d y_predict;
	matr_d f;
	double fn(const size_t n, const size_t i);
	double fn_predict(const size_t n, const size_t i);

	// Spline
	vec_d h, s, F;
	matr_d m;

public:
	Differential_equation(const double a, const double b, const double c, const double step);
	void iterate_f();
	void iterate_y();
	void iterate_y_predict();
	void Solve();
	void Init_Spline(const size_t n);
	double Spline(const size_t n, double p);
	double sz;
	matr_d t;
	matr_d y;
};
Differential_equation::Differential_equation(const double a, const double b, const double c, const double step) : a(a), b(b), c(c), step(step)
{
	sz = 1.0 / step + 1;
	index = 0;
	t.resize(sz);
	y.resize(3);
	y_predict.resize(3);

	f.resize(3);
	for (size_t i = 0; i < 3; i++)
	{
		y[i].resize(sz);
		y_predict[i].resize(sz);
		f[i].resize(4);

		y[i][0] = 1;
	}
	for (size_t i = 0; i < sz; i++)
	{

		t[i].resize(1);
		t[i][0] = i * step;
	}
}
double Differential_equation::fn(const size_t n, const size_t i)
{
	double res = 0;
	switch (n)
	{
	case 1:
		res = y[1][i] - y[2][i];
		break;
	case 2:
		res = y[0][i] + a * y[1][i];
		break;
	case 3:
		res = b + y[2][i] * (y[0][i] - c);
		break;
	}
	return res;
}
double Differential_equation::fn_predict(const size_t n, const size_t i)
{
	double res = 0;
	switch (n)
	{
	case 1:
		res = y_predict[1][i] - y_predict[2][i];
		break;
	case 2:
		res = y_predict[0][i] + a * y_predict[1][i];
		break;
	case 3:
		res = b + y_predict[2][i] * (y_predict[0][i] - c);
		break;
	}
	return res;
}
void Differential_equation::iterate_f()
{
	if (index < 3)
	{
		for (size_t i = 0; i < 3; i++)
		{
			f[i][0] = fn(i, 0);
		}
		return;
	}
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 1; j < 4; j++)
		{
			f[i][j] = f[i][j - 1];
		}
		f[i][0] = fn(i, index);
	}
}
void Differential_equation::iterate_y_predict()
{
	for (size_t i = 0; i < 3; i++)
	{
		y_predict[i][index + 1] = y[i][index] + step * (55 * f[i][0] - 59 * f[i][1] + 37 * f[i][2] - 9 * f[i][3]) / 24.0;
	}
}
void Differential_equation::iterate_y()
{
	for (size_t i = 0; i < 3; i++)
	{
		y[i][index + 1] = y[i][index] + step * (9 * fn_predict(i, index + 1) + 19 * f[i][0] - 5 * f[i][1] + f[i][2]);
	}
}
void Differential_equation::Solve()
{
	while (index < sz - 1)
	{
		iterate_f();
		iterate_y_predict();
		iterate_y();
		index++;
	}
}
void Differential_equation::Init_Spline(const size_t n)
{
	h.resize(sz);
	s.resize(sz);
	F.resize(sz);
	m.resize(sz);
	for (size_t i = 0; i < sz; i++)
	{
		m[i].resize(sz);
	}
	for (size_t i = sz - 1; i > 0; i--)
	{
		F[i] = (y[n][i] - y[n][i - 1]) / (t[i][0] - t[i - 1][0]);
		h[i - 1] = t[i][0] - t[i - 1][0];
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
}
double Differential_equation::Spline(const size_t n, double p)
{
	double res = 0;
	for (size_t i = 0; i < sz - 1; i++)
	{
		if (t[i][0] <= p && p <= t[i + 1][0])
		{
			double a1 = (s[i + 1] - s[i]) / (6 * h[i]);
			double b1 = s[i] / 2;
			double c1 = (y[n][i + 1] - y[n][i]) / h[i] - (2 * h[i] * s[i] + s[i + 1] * h[i]) / 6;
			double d1 = y[n][i];
			res = a1 * pow((p - t[i][0]), 3) + b1 * pow((p - t[i][0]), 2) + c1 * (p - t[i][0]) + d1;
		}
	}
	return res;
}
Differential_equation eq(0.2, 0.2, 2.5, 1e-3);
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
	glColor3f(1, 0, 0);
	eq.Init_Spline(0);
	for (double i = 0; i <= 1; i += 1e-3)
		glVertex2f(i, eq.Spline(0, i) / 10);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	eq.Init_Spline(1);
	for (double i = 0; i <= 1; i += 1e-4)
		glVertex2f(i, eq.Spline(1, i) / 10);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	eq.Init_Spline(2);
	for (double i = 0; i <= 1; i += 1e-4)
		glVertex2f(i, eq.Spline(2, i) / 10);
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (size_t i = 0; i < eq.sz; i++)
		glVertex2f(eq.t[i][0], eq.y[0][i] / 10);
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	for (size_t i = 0; i < eq.sz; i++)
		glVertex2f(eq.t[i][0], eq.y[1][i] / 10);
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0, 0, 1);
	for (size_t i = 0; i < eq.sz; i++)
		glVertex2f(eq.t[i][0], eq.y[2][i] / 10);
	glEnd();

	glFlush();
}
int main(int argc, char *argv[])
{
	eq.Solve();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(1000, 1000);
	glutInitWindowSize(400, 400);
	glutCreateWindow("graph");
	glutDisplayFunc(&Display);
	glutMainLoop();
	return 0;
}
