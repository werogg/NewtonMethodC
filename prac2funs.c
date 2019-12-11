/* OTERO MARTIN JOEL - DNI: 53637165S */
#include "prac2funs.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void resTinf(int n, double **L, double *b, double *x)
{
	int i, k;

	for (i = 0; i < n; i++)
	{
		x[i] = b[i];
		for (k = 0; k < i ; k++)
		{
			x[i] -= x[k] * L[i][k];
		}
	}
}

void resTsup(int n, double **U, double *b, double *x)
{
	int i, k;

	for (i = n - 1; i >= 0; i--)
	{
		x[i] = b[i];
		for (k = n-1; k > i; k--)
		{
			x[i] -= x[k] * U[i][k];
		}
	}
}

void prodMatVec(int m, int n, double **A, double *x, double *y)
{
	int i, j;


	for (i = 0; i < m; i++)
	{
		y[i] = 0;
		for (j = 0; j < n; j++)
		{
			y[i] += A[i][j] * x[j];
		}
	}
}

double norma2(int n, double *z)
{
	int i;
	double x = 0;
	for (i = n; i > 0; i--)
	{
		x += z[i] * z[i];
	}
	return sqrt(x);
}

void prodMatMat(int m, int n, int p, double **A, double **B, double **C)
{
	int i, j, k;

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < p; j++)
		{
			C[i][j] = 0;
			for (k = 0; k < n; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	
}

double f(double x)
{
	/* PART 1 */
	return x*x + sin(x) - acos(-1);
	/*return 1 - log(x);
	return sqrt(x) - exp(-x);
	return sinh(x) - sin(x);
	/* PART 2 */

    /*
	return x*x - 1
	return x*x*x - x
	return 3*x*x*x - x + 1
	return x*x*x*x + 1
    */

	/*
	int i;
	double n = 1;
	for (i = 1; i <= 6 ; i++)
	{
		n *= (x - (10 * i) / (i + 1));
	}
	return n;
	*/
}

double df(double x) 
{
	return 2*x+cos(x);
	/*
    return 1 - ln(x);
	return 
    */
}

int newton(double x, double *sol, double tol, int iter)
{
	int n;

	double fdf, next_x;

    for (n = 0; n <= iter; iter++)
    {
        fdf = f(x) / df(x);
        next_x = x - fdf;

        if (abs(next_x-x) < tol || abs(f(x)) < tol)
        {
            *sol = next_x;
            return 0;
        }

        x = next_x;
    }
	return 1;
}