/* OTERO MARTIN JOEL - DNI: 53637165S */
#include "prac2funs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Funcions PART 2 */
double f(double x)
{
	return x*x - 1;
	
    /*
	a)
	b) return pow(x, 3) - x;
	c) return 3*pow(x, 3) - x + 1;
	d) return pow(x, 4) + 1;
	e) return 1000000/7 + (126*(pow(x,6)) - 5553*(pow(x,5)) + 101410*(pow(x,4)) - 981775*(pow(x, 3)) + 5311000*(pow(x, 2)) - 15210000*x) / 126;
	f) return 7/1000000 + (18000000*(pow(x,6)) - 15210000*(pow(x,5)) + 5311000*(pow(x,4)) - 981775*(pow(x,3)) + 101410*(pow(x,2)) - 5553*x) / 18000000;
    */
}

/* Funcions derivades PART 2 */
double df(double x) 
{
	return 2*x;

	/*
	a)
	b) return 3*pow(x, 2) - 1;
	c) return 9*pow(x, 2) - 1;
	d) return 4*pow(x, 3);
	e) return 1/126 * (756*pow(x, 5) - 27765*pow(x, 4) + 405640*pow(x, 3) - 2945325*pow(x, 2) + 10622000*x - 15210000);
	f) return 1/18000000 * (108000000*pow(x,5) - 76050000*pow(x,4) + 21244000*pow(x,3) - 2945325*pow(x,2) + 202820*x - 5553);
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

		if (abs(df(x)) < tol) return 1;

        if (abs(next_x-x) < tol || abs(f(x)) < tol)
        {
            *sol = next_x;
            return 0;
        }

        x = next_x;
    }
	return 1;
}

void F(double *x, double *f)
{
	/* Funcions Sistema A */
	f[0] = x[0] + x[1] + x[2] - 1;
	f[1] = x[1] + x[2];
	f[2] = pow(x[0], 2) + 0.75*x[1];
}

void dF(double *x, double **df)
{
	int i;

	/* Derivades Parcials Sistema A */
	for (i = 0; i < 3; i++)
		df[0][i] = 1;
	for (i = 1; i < 3; i++)
		df[1][i] = 1;
	df[1][0] = 0;
	df[2][0] = 2*x[0];
	df[2][1] = 0.75;
	df[2][2] = 0;
}

int newton3(double *x, double *sol, double tol, int iter)
{
	double **dFtv, **dFv, **dFtvdFv, *Fv, *dFtvFv, *dx, *y, *next_x, *cond1, norma_cond1, norma_cond2;
	int i, j, n, no_possible;

	dFtv = (double **)malloc(3 * sizeof(double *));
    dFv = (double **)malloc(3 * sizeof(double *));
    dFtvdFv = (double **)malloc(3 * sizeof(double *));

	for (i = 0; i < 3; i++)
    {
        dFtv[i] = (double *)malloc(3 * sizeof(double));
        dFv[i] = (double *)malloc(3 * sizeof(double));
		dFtvdFv[i] = (double *)malloc(3 * sizeof(double));
	}

	Fv = (double *)malloc(3 * sizeof(double));
    dFtvFv = (double *)malloc(3 * sizeof(double));
    dx = (double *)malloc(3 * sizeof(double));
    y = (double *)malloc(3 * sizeof(double));
	next_x = (double *)malloc(3 * sizeof(double));
	cond1 = (double *)malloc(3 * sizeof(double));

	dF(x, dFv);
	F(x, Fv);

	for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            dFtv[j][i] = dFv[i][j];

	prodMatMat(3, 3, 3, dFtv, dFv, dFtvdFv);
	prodMatVec(3, 3, dFtv, Fv, dFtvFv);

	no_possible = ldlt(3, dFtvdFv, tol);

	if (no_possible == 1) {
		printf("No ha estat possible descomposar la matriu A en LDL^t amb la donada tolerancia\n");
	}
	else
	{
		resTinf(3, dFtvdFv, dFtvFv, dx);

		for (i=0; i<3; i++) {
            y[i] = dx[i]/dFtvdFv[i][i];
        }

        resTsup(3, dFtvdFv, y, dx);

        printf("Vector Dx:\n");
	    for (i = 0; i < 3; i++)
		    printf(" %16.7e\n", dx[i]);


		for (n = 0; n <= iter; iter++)
		{
			for (i = 0; i < 3; i++)
				next_x[i] = x[i] - dx[i];

			for (i = 0; i < 3; i++)
				cond1[i] = next_x[i] - x[i];

			norma_cond1 = norma2(3, cond1);
			norma_cond2 = norma2(3, Fv);

			if (fabs(norma_cond1) < tol || fabs(norma_cond2) < tol)
			{
				*sol = *next_x;
				return 0;
			}

			x = next_x;
		}
		return 1;
	}
	return 1;
}

int main(void)
{
	double *sol, **Q, tol, Qi, Qf;
	int iter, i;

	sol = (double *)malloc(3 * sizeof(double *));
	Q = (double **)malloc(100 * sizeof(double *));

	for (i = 0; i < 100; i++)
    {
        Q[i] = (double *)malloc(3 * sizeof(double));
	}

    if (sol == NULL)
    {
        printf("No hi ha prou memoria\n");
		exit(2);
    }

    printf("Doneu el valor de tolerancia\n");
	scanf("%lf", &tol);

    printf("Doneu la quantitat màxima d'iteracions\n");
	scanf("%d", &iter);

	printf("Doneu el Cub en format [Qi, Qf]\n");
	scanf("%lf", &Qi);
	scanf("%lf", &Qf);

	for (i = 0; i < 100; i++)
    {
		srand48(i);
		Q[i][0] = (drand48() - 0.5) * 2.0;
		srand48(i+1);
		Q[i][1] = (drand48() - 0.5) * 2.0;
		srand48(i+2);
		Q[i][2] = (drand48() - 0.5) * 2.0;
	}

	for  (i = 0; i < 100; i++)
	{
		if (!newton3(Q[i], sol, tol, iter))
		{
			int i;
			for (i = 0; i < 3; i++)
				printf("x[%d] = %f\n", i, sol[i]);
		}
		else
		{
			printf("No s'ha trobat una aproximació prou bona del zero.\n");
		}
	}

	return 0;

}