/* OTERO MARTIN JOEL - DNI: 53637165S */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Seleccionar funció mitjançant comentaris */
double f(double x)
{
	/* PART 1 */
	return x*x + sin(x) - acos(-1);
	/*return 1 - log(x);
	return sqrt(x) - exp(-x);
	return sinh(x) - sin(x);
	*/
}

/* Seleccionar funció derivada mitjançant comentaris */
double df(double x) 
{
	/* PART 1 */
	return 2*x+cos(x);
	/*
    return -1/x;
	return exp(-x) + 1/(2*sqrt(x));
	return cosh(x) - cos(x);
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

		/* Si el valor absolut de la derivada es < que tolerancia no hi ha zero */
		if (fabs(df(x)) < tol) return 1;

		/* Condicions a les que si hi ha zero */
        if (fabs(next_x-x) < tol || fabs(f(x)) < tol)
        {
            *sol = next_x;
            return 0;
        }

		/* Seguent iteració */
        x = next_x;
    }
	return 1; /* Si arribem al final del "for" no hi ha zero */
}

int main(void)
{
	/* Inicialitzem les variables */
	double *sol, x, tol;
	int iter;
    
	sol = (double *)malloc(sizeof(double *));

    if (sol == NULL)
    {
        printf("No hi ha prou memoria\n");
		exit(2);
    }

	/* Demanem les variables per consola */
	printf("Doneu el valor de x\n");
	scanf("%lf", &x);

    printf("Doneu el valor de tolerancia\n");
	scanf("%lf", &tol);

    printf("Doneu la quantitat d'iteracions\n");
	scanf("%d", &iter);


	/* Execució de newton per a uns valors donats */
	printf("S'executara newton amb:\niter = %d\nx = %f\ntol = %f\n", iter, x, tol);

    int s = newton(x, sol, tol, iter);

	if (s == 0)
	{
		printf("Sol = %f", *sol);
	}
	else
	{
		printf("No s'ha trobat una aproximació prou bona del zero.\n");
	}

	return 0;


}