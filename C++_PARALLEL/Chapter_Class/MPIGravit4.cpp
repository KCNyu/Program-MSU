#include "pt4.h"
#include "mpi.h"
#include <cmath>

#define gravity 10 // гравитационная постоянная
#define dt 0.1     // шаг по времени
#define N 800      // количество частиц
#define fmax 1     // максимальное значение силы

int k;             // количество процессов
int r;             // ранг текущего процесса
int Niter;         // число итераций

struct Particle
{
	double x, y, vx, vy;
};

struct Force
{
	double x, y;
};

Particle p[N];
Force f[N];
double m[N];

void Init()
{
	for (int i = 0; i < N; i++)
	{
		p[i].x = 20 * (i / 20 - 20) + 10;
		p[i].y = 20 * (i % 20 - 10) + 10;
		p[i].vx = p[i].y / 15;
		p[i].vy = -p[i].x / 50;

		m[i] = 100 + i % 100;

		f[i].x = 0;
		f[i].y = 0;
	}
}

// Реализация непараллельного алгоритма

void CalcForces2()
{
	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++)
		{
			double dx = p[j].x - p[i].x, dy = p[j].y - p[i].y,
				r_2 = 1 / (dx * dx + dy * dy),
				r_1 = sqrt(r_2),
				fabs = gravity * m[i] * m[j] * r_2;
			if (fabs > fmax) fabs = fmax;
			f[i].x += dx = fabs * dx * r_1;
			f[i].y += dy = fabs * dy * r_1;
			f[j].x -= dx;
			f[j].y -= dy;
		}
}

void MoveParticlesAndFreeForces()
{
	for (int i = 0; i < N; i++)
	{
		double dvx = f[i].x * dt / m[i],
			dvy = f[i].y * dt / m[i];
		p[i].x += (p[i].vx + dvx / 2) * dt;
		p[i].y += (p[i].vy + dvy / 2) * dt;
		p[i].vx += dvx;
		p[i].vy += dvy;
		f[i].x = 0;
		f[i].y = 0;
	}
}

void NonParallelCalc(int n)
{
	Init();
	for (int i = 0; i < n; i++) 
	{
		CalcForces2();
		MoveParticlesAndFreeForces();
	}
}

// Конец реализации непараллельного алгоритма

// Реализация параллельного алгоритма,
// основанного на методе конвейера с разбиением на обратные полосы

// Конец реализации параллельного алгоритма
constexpr int Wproc = 8;
constexpr int blockSize = N / Wproc;
Particle p_p[blockSize];
Force p_f[blockSize];
double p_m[blockSize];
int p_c = 0;
MPI_Datatype MPI_PARTICLE, MPI_FORCE;
int Nthr = 8;

void MPICreateType()
{
	MPI_Type_contiguous(4, MPI_DOUBLE, &MPI_PARTICLE);
	MPI_Type_commit(&MPI_PARTICLE);
	MPI_Type_contiguous(2, MPI_DOUBLE, &MPI_FORCE);
	MPI_Type_commit(&MPI_FORCE);
}
void ParallelInit()
{
	MPICreateType();
	for (int i = 0; i < blockSize; i++)
	{
		int p_i;
		if (i % 2 == 0)
		{
			// p_i = r + i / 2 * Wproc * 2;
			p_i = r + i * Wproc;
		}
		else
		{
			// p_i = -r + (i + 1) / 2 * Wproc * 2 - 1;
			p_i = -r + (i + 1) * Wproc - 1;
		}
		p_p[i].x = 20 * (p_i / 20 - 20) + 10;
		p_p[i].y = 20 * (p_i % 20 - 10) + 10;
		p_p[i].vx = p_p[i].y / 15;
		p_p[i].vy = -p_p[i].x / 50;

		p_m[i] = 100 + p_i % 100;

		p_f[i].x = 0;
		p_f[i].y = 0;

	}
}

Particle buf_p[blockSize];
Force buf_f[blockSize];
double buf_m[blockSize];


void InitBuf()
{
	for (int i = 0; i < blockSize; i++)
	{
		buf_p[i] = p_p[i];
		buf_f[i] = p_f[i];
		buf_m[i] = p_m[i];
	}
}
void ExchangeData()
{
	int dest = (r + 1) % Wproc, source = (r - 1 + Wproc) % Wproc;
	MPI_Sendrecv_replace(buf_p, blockSize, MPI_PARTICLE, dest, 0, source, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Sendrecv_replace(buf_f, blockSize, MPI_FORCE, dest, 0, source, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Sendrecv_replace(buf_m, blockSize, MPI_DOUBLE, dest, 0, source, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
}
int Judge1(int a, int b)
{
	return (r + Wproc - b) % Wproc + Wproc * a;
}
int Judge2(int a, int b)
{
	return -(r + Wproc - b) % Wproc + Wproc * a;
}
void CalcForcesPar()
{
	InitBuf();
	for (int i = 0; i < blockSize - 1; i++)
	{
		for (int j = i + 1; j < blockSize; j++)
		{
			//p_c++;
			double dx = p_p[j].x - p_p[i].x, dy = p_p[j].y - p_p[i].y,
				r_2 = 1 / (dx * dx + dy * dy),
				r_1 = sqrt(r_2),
				fabs = gravity * p_m[i] * p_m[j] * r_2;
			if (fabs > fmax) fabs = fmax;
			p_f[i].x += dx = fabs * dx * r_1;
			p_f[i].y += dy = fabs * dy * r_1;
			p_f[j].x -= dx;
			p_f[j].y -= dy;
		}
	}
	ExchangeData();
	for (int i = 1; i < Wproc; i++)
	{
		for (int j = 0; j < blockSize; j += 2)
		{
			for (int k = 0; k < blockSize; k++)
			{
				if (Judge1(j, 0) <= Judge1(k, i)) break;
				else
				{

					p_c++;
					double dx = p_p[k].x - buf_p[j].x, dy = p_p[k].y - buf_p[j].y,
						r_2 = 1 / (dx * dx + dy * dy),
						r_1 = sqrt(r_2),
						fabs = gravity * p_m[k] * buf_m[j] * r_2;
					if (fabs > fmax)
						fabs = fmax;

					buf_f[j].x += dx = fabs * dx * r_1;
					buf_f[j].y += dy = fabs * dy * r_1;

					p_f[k].x -= dx;
					p_f[k].y -= dy;
				}
			}
		}
		for (int j = 1; j < blockSize; j += 2)
		{
			for (int k = 0; k < blockSize; k++)
			{
				if (Judge2(j, 0) <= Judge2(k, i)) break;
				else
				{
					p_c++;
					double dx = p_p[k].x - buf_p[j].x, dy = p_p[k].y - buf_p[j].y,
						r_2 = 1 / (dx * dx + dy * dy),
						r_1 = sqrt(r_2),
						fabs = gravity * p_m[k] * buf_m[j] * r_2;
					if (fabs > fmax)
						fabs = fmax;

					buf_f[j].x += dx = fabs * dx * r_1;
					buf_f[j].y += dy = fabs * dy * r_1;

					p_f[k].x -= dx;
					p_f[k].y -= dy;
				}
			}
		}
		ExchangeData();
	}
}
void MoveParticlesAndFreeForcesPar()
{
	for (int i = 0; i < blockSize; i++)
	{
		double dvx = (p_f[i].x + buf_f[i].x) * dt / p_m[i],
			dvy = (p_f[i].y + buf_f[i].y) * dt / buf_m[i];
		p_p[i].x += (p_p[i].vx + dvx / 2) * dt;
		p_p[i].y += (p_p[i].vy + dvy / 2) * dt;
		p_p[i].vx += dvx;
		p_p[i].vy += dvy;
		p_f[i].x = 0;
		p_f[i].y = 0;
	}
}
void ParallelCalc(int n)
{
	ParallelInit();
	for (int i = 0; i < n; i++)
	{
		CalcForcesPar();
		MoveParticlesAndFreeForcesPar();
	}
}
void Solve()
{
	Task("MPIGravit4");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	k = size;
	r = rank;
	if (r == 0)
	{
		pt >> Niter;
		// Тестирование непараллельного алгоритма:

		ShowLine("НЕПАРАЛЛЕЛЬНЫЙ АЛГОРИТМ");
		NonParallelCalc(1);

		ShowLine("После одной итерации");
		SetPrecision(12);
		Show("    Координаты точки 0:   ", p[0].x, 17);
		ShowLine(p[0].y, 17);
		Show("    Координаты точки 799: ", p[799].x, 17);
		ShowLine(p[799].y, 17);

		double t = MPI_Wtime();
		NonParallelCalc(Niter);
		t = MPI_Wtime() - t;

		ShowLine("После требуемого числа итераций");
		Show("    Координаты точки 0:   ", p[0].x, 17);
		ShowLine(p[0].y, 17);
		Show("    Координаты точки 799: ", p[799].x, 17);
		ShowLine(p[799].y, 17);

		SetPrecision(2);
		ShowLine("Время работы непараллельного алгоритма: ", t * 1000);
	}
	MPI_Bcast(&Niter, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// Тестирование параллельного алгоритма:

	// После одной итерации
	ParallelCalc(1);
	if (r == 0)
	{
		pt << p_p[0].x << p_p[0].y;
		pt << p_p[blockSize - 1].x << p_p[blockSize - 1].y;
	}

	// После требуемого числа итераций
	double t = MPI_Wtime();
	ParallelCalc(Niter);
	t = MPI_Wtime() - t;
	Show("Time = ", t);
	Show("PairsCount = ", p_c);
	if (r == 0)
	{
		pt << p_p[0].x << p_p[0].y;
		pt << p_p[blockSize - 1].x << p_p[blockSize - 1].y;
	}

}
