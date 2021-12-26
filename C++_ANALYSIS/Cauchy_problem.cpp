#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <vector>
#include <cmath>
#include <GLUT/GLUT.h>
using namespace std;

using vec_d = vector<double>;
using matr_d = vector<vector<double>>;
#define bound 2
class Cachy_problem
{
	const double f(const double x, const double y);
	const double b(const double x, const double y);
	const double I1, I2;
	const int n1, n2;
	double omega;
	const double eps = 1e-6;
	double b_return = 0;

public:
	Cachy_problem(const double I1, const double I2, const int n1, const int n2);
	matr_d Solve(const double omega, const double b_return);
	size_t Solve_iteration(const double omega, const double b_return);
	double Gold(double b_return, double left, double right);
	size_t iteration = 0;
};
Cachy_problem::Cachy_problem(const double I1, const double I2, const int n1, const int n2) : I1(I1), I2(I2), n1(n1), n2(n2)
{
}
const double Cachy_problem::f(const double x, const double y)
{
	return 1;
}
const double Cachy_problem::b(const double x, const double y)
{
	return b_return;
}
matr_d Cachy_problem::Solve(const double omega, const double b_return)
{
	this->omega = omega;
	this->b_return = b_return;
	iteration = 0;
	double h2 = I1 / n1;
	double h3 = I2 / n2;
	double d = 2. / (h2 * h2) + 2. / (h3 * h3);
	matr_d y(n1 + 1), ff(n1 + 1), bb(n1 + 1);

	for (size_t i = 0; i <= n1; i++)
	{
		y[i].resize(n2 + 1);
		ff[i].resize(n2 + 1);
		bb[i].resize(n2 + 1);
	}
	for (size_t j = 1; j < n2; j++)
	{
		for (size_t i = 1; i < n1; i++)
		{
			ff[i][j] = f(i * h2, j * h3);
			bb[i][j] = b(i * h2, j * h3);
		}
	}
	double res = 0;
	do
	{
		res = 0;
		for (size_t j = 1; j < n2; j++)
		{
			for (size_t i = 1; i < n1; i++)
			{
				double rr = -(y[i - 1][j] - 2. * y[i][j] + y[i + 1][j]) / (h2 * h2) - (y[i][j - 1] - 2. * y[i][j] + y[i][j + 1]) / (h3 * h3) + bb[i][j] * (y[i + 1][j] - y[i - 1][j]) / (2. * h2) - ff[i][j];
				res += rr * rr;
				y[i][j] -= omega * rr / d;
			}
			res *= h2 * h3;
		}
		iteration++;
	} while (sqrt(res) > eps);
	// printf("iteration = %ld\n",iteration);
	return y;
}
size_t Cachy_problem::Solve_iteration(const double omega, const double b_return)
{
	Solve(omega, b_return);
	return iteration;
}
double Cachy_problem::Gold(double b_return, double left, double right)
{
	double epsilon = 1e-7, tau = (sqrt(5) - 1) / 2.0;
	double a_gss = left, b_gss = right, f_lambda = 0, f_mu = 0;
	double lambda = a_gss + (1.0 - tau) * (b_gss - a_gss), mu = a_gss + tau * (b_gss - a_gss);
	f_lambda = Solve_iteration(lambda, b_return);
	f_mu = Solve_iteration(mu, b_return);
	for (int i = 0; fabs(mu - lambda) > epsilon; i++)
	{
		if (f_lambda < f_mu)
		{
			b_gss = mu;
			mu = lambda;
			f_mu = f_lambda;
			lambda = a_gss + (1.0 - tau) * (b_gss - a_gss);
			f_lambda = Solve_iteration(lambda, b_return);
		}
		else
		{
			a_gss = lambda;
			lambda = mu;
			f_lambda = f_mu;
			mu = a_gss + tau * (b_gss - a_gss);
			f_mu = Solve_iteration(mu, b_return);
		}
	}

	return 0.5 * (lambda + mu);
}
Cachy_problem eq(1., 1., 25, 25);
void Display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-bound, 0, 0);
	glVertex3f(bound, 0, 0);
	glVertex3f(0, -500, 0);
	glVertex3f(0, 500, 0);
	glEnd();

#if 1
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	for (double i = 1; i < 2.0; i += 1e-2)
	{
		eq.Solve_iteration(i, 0);
		glVertex2d(i, eq.iteration);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 1);
	for (double i = 1; i < 2.0; i += 1e-2)
	{
		eq.Solve_iteration(i, 10);
		glVertex2d(i, eq.iteration);
	}
	glEnd();
#endif

#if 1
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 1, 0);
	double min_omega_0 = eq.Gold(0, 1, 2);
	printf("min_omega_0 = %lf\n", min_omega_0);
	glVertex2d(min_omega_0, 500);
	glVertex2d(min_omega_0, -500);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 1, 0);
	double min_omega_10 = eq.Gold(10, 1, 2);
	printf("min_omega_10 = %lf\n", min_omega_10);
	glVertex2d(min_omega_10, 500);
	glVertex2d(min_omega_10, -500);
	glEnd();
#endif

	glFlush();
}
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	gluOrtho2D(-bound, bound, -500, 500);
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(1000, 1000);
	glutInitWindowSize(400, 400);
	glutCreateWindow("graph");
	init();
	glutDisplayFunc(&Display);
	glutMainLoop();
	return 0;
}
