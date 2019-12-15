/* OTERO MARTIN JOEL - DNI: 53637165S */
#include "prac2funs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void F(double *x, double *f)
{
	/* Funcions Sistema A */
	f[0] = x[0] + x[1] + x[2] - 1;
	f[1] = x[1] + x[2];
	f[2] = pow(x[0], 2) + 0.75*x[1];

	/* Funcions Sistema B
	f[0] = pow(x[0], 2) + pow(x[1], 2) + pow(x[2], 2) - 1;
	f[1] = (1 / 4) * pow((x[0] - x[1]), 2) + pow((x[0] + x[1]), 2) + pow(x[2], 2) - 1;
	f[2] = pow((x[0] - x[1]), 2) + pow((x[0] + x[1]), 2) + (1 / 4) * pow(x[2], 2) -1;
	*/
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

	/* Derivades Parcials Sistema B
	for (i = 0; i < 3; i++)
		df[0][i] = 2 * x[i];
	df[1][0] = (5 * x[0] + 3 * x[1]) / 2;
	df[1][1] = (3 * x[0] + 5 * x[1]) / 2;
	df[1][2] = 2 * x[2];
	for (i = 0; i < 2; i++)
		df[2][i] = 4 * x[i];

	df[2][2] = (2 * x[2]) / 7;
	*/
}

int newton3(double *x, double *sol, double tol, int iter)
{
	/* Inicialitzem les variables */
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

	/* Fem la transposada de dF */
	for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            dFtv[j][i] = dFv[i][j];

	/* Fem les operacions per tenir un sistema de matrius simetriques */
	prodMatMat(3, 3, 3, dFtv, dFv, dFtvdFv);
	prodMatVec(3, 3, dFtv, Fv, dFtvFv);

	/* Descomposem la matriu LDLt */
	no_possible = ldlt(3, dFtvdFv, tol);

	/* Continuem amb el programa si ha estat posible descomposar la matriu en LDLt*/
	if (no_possible == 1) {
		printf("No ha estat possible descomposar la matriu en LDL^t amb la donada tolerancia\n");
	}
	else
	{
		/* Resolem el sistema matricial amb els mètodes de la pràctica 1 */

		resTinf(3, dFtvdFv, dFtvFv, dx);

		for (i=0; i<3; i++) {
            y[i] = dx[i]/dFtvdFv[i][i];
        }

        resTsup(3, dFtvdFv, y, dx);

		/* Fem newton amb les xs inicials i el resultat del sistema anterior */
		for (n = 0; n <= iter; iter++)
		{
			for (i = 0; i < 3; i++)
				next_x[i] = x[i] - dx[i];

			for (i = 0; i < 3; i++)
				cond1[i] = next_x[i] - x[i];

			norma_cond1 = norma2(3, cond1);
			norma_cond2 = norma2(3, Fv);

			/* Condicions de retorn */
			if (fabs(norma_cond1) < tol || fabs(norma_cond2) < tol)
			{
				int j;
				for (j = 0; j < 3; j++) {
					sol[j] = next_x[j];
				}

				return 0;
			}

			/* Seguent iteracio */
			x = next_x;
		}
		return 1; /* No retorn */
	}
	return 1; /* No retorn */
}

int main(void)
{
	/* Inicialitzem les variables */
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

	/* Demanem les dades per consola */
    printf("Doneu el valor de tolerancia\n");
	scanf("%lf", &tol);

    printf("Doneu la quantitat màxima d'iteracions\n");
	scanf("%d", &iter);

	printf("Doneu el Cub en format [Qi, Qf]\n");
	scanf("%lf", &Qi);
	scanf("%lf", &Qf);

	/* Generem 100 condicions inicials per al cub Q */
	for (i = 0; i < 100; i++)
    {
		srand48(i);
		Q[i][0] = (drand48() - 0.5) * 2.0;
		srand48(i+1);
		Q[i][1] = (drand48() - 0.5) * 2.0;
		srand48(i+2);
		Q[i][2] = (drand48() - 0.5) * 2.0;
	}

	/* Fem newton3 per a cadascuna d'aquestes 100 condicions*/
	for  (i = 0; i < 100; i++)
	{
		if (!newton3(Q[i], sol, tol, iter))
		{

			printf("Aproximació a x = (%f, %f, %f)\n", Q[i][0], Q[i][1], Q[i][2]);
			printf("x = %f\n", sol[0]);
			printf("y = %f\n", sol[1]);
			printf("z = %f\n", sol[2]);
		}
		else
		{
			printf("No s'ha trobat una aproximació prou bona del zero.\n");
		}
	}

	/* Alliberem la memoria reservada */
	for (i = 0; i < 100; i++)
	{
		free(Q[i]);
	}

	free(Q);
	free(sol);

	return 0;

}