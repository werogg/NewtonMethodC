/* OTERO MARTIN JOEL - DNI: 53637165S */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double f(double x)
{
	/* PART 1 */
	return x*x + sin(x) - acos(-1);
	/*return 1 - log(x);
	return sqrt(x) - exp(-x);
	return sinh(x) - sin(x);
	*/
}

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

        if (abs(next_x-x) < tol || abs(f(x)) < tol)
        {
            *sol = next_x;
            return 0;
        }

        x = next_x;
    }
	return 1;
}

int main(void)
{
	double *sol, x, tol;
	int iter;
    
	sol = (double *)malloc(sizeof(double *));

    if (sol == NULL)
    {
        printf("No hi ha prou memoria\n");
		exit(2);
    }

	printf("Doneu el valor de x\n");
	scanf("%lf", &x);

    printf("Doneu el valor de tolerancia\n");
	scanf("%lf", &tol);

    printf("Doneu la quantitat d'iteracions\n");
	scanf("%d", &iter);



	printf("S'executara newton amb:\niter = %d\nx = %f\ntol = %f\n", iter, x, tol);

    newton(x, sol, tol, iter);

    printf("Sol = %f", *sol);

	return 0;


}