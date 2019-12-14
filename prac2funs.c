/* OTERO MARTIN JOEL - DNI: 53637165S */
#include "prac2funs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int ldlt(int n, double **A, double tol)
{
    int k, j, i;

    for (k = 0; k <= n-1; k++)
    {
        for (j = 0; j <= k-1; j++)
        {
            A[k][k] -= (A[k][j]*A[k][j])*A[j][j];
        }

        for (i = k+1; i <= n-1; i++)
        {
            for (j = 0; j <= k-1; j++)
            {
                A[i][k] -= (A[i][j]*A[k][j]*A[j][j]);
            }
            A[i][k] = A[i][k] * (1/A[k][k]);
            A[k][i] = A[i][k];
        }
    }
    
    for (k = 0; k < n; k++)
    {
        if (fabs(A[k][k]) < tol) return 1;
    }

    return 0;
}

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