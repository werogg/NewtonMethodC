/* OTERO MARTIN JOEL - DNI: 53637165S */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double f(double x)
{
	/* PART 2 */

    /*
	return x*x - 1
	return pow(x, 3) - x
	return 3*pow(x, 3) - x + 1
	return pow(x, 4) + 1
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

	/*
	 int i;
	 double n = 1;
	 for (i = 1; i <= 6; i++) {
		 n*= (x - (i + 1)/(10*i));
	 }
	 */
}

double df(double x) 
{
	/* PART 2 */

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
	double *sol, x, tol, M, m, h, *I;
	int iter;
    
	sol = (double *)malloc(sizeof(double *));

    if (sol == NULL)
    {
        printf("No hi ha prou memoria\n");
		exit(2);
    }

	printf("Doneu el valor de M\n");
	scanf("%lf", &M);

	printf("Doneu el valor de h\n");
	scanf("%lf", &h);

    printf("Doneu el valor de tolerancia\n");
	scanf("%lf", &tol);

    printf("Doneu la quantitat d'iteracions\n");
	scanf("%d", &iter);

	x = -M;
	h = 2*M/m

	printf("S'executara newton amb:\niter = %d\nx = %f\ntol = %f\n", iter, x, tol);

    newton(x, sol, tol, iter);

    printf("Sol = %f", *sol);

	return 0;


}