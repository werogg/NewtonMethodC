/* OTERO MARTIN JOEL - DNI: 53637165S */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double f(double x)
{
	/* PART 2 */

	return x*x - 1;
    /*
	
	b) return pow(x, 3) - x
	c) return 3*pow(x, 3) - x + 1
	d) return pow(x, 4) + 1
	e) return 1000000/7 + (126*(pow(x,6) - 5553*(pow(x,5) + 101410*(pow(x,4) - 981775*(pow(x, 3)) + 5311000*(pow(x, 2)) - 15210000*x))/126
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
	return 2*x;

	/*
	
	b) return 3*pow(x, 2) - 1
	c) return 9*pow(x, 2) - 1
	d) return 4*pow(x, 3)
	e) return 1/126 * (756*pow(x, 5) - 27765*pow(x, 4) + 405640*pow(x, 3) - 2945325*pow(x, 2) + 10622000*x - 15210000)
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

int main(void)
{
	double *sol, x, tol, M, m, h;
	int iter;
    
	m = pow(10, 3);

	sol = (double *)malloc(sizeof(double *));

    if (sol == NULL)
    {
        printf("No hi ha prou memoria\n");
		exit(2);
    }

	printf("Doneu el valor de M\n");
	scanf("%lf", &M);

    printf("Doneu el valor de tolerancia\n");
	scanf("%lf", &tol);

    printf("Doneu la quantitat d'iteracions\n");
	scanf("%d", &iter);

	h = 2*M/m;

	for (x = -M; x <= M; x += h)
	{
		int s = newton(x, sol, tol, iter);

		if (s == 0)
		{
			if (x <= -h)
			{
				printf("x <= -h\n");
				printf("x = %f existent a [%f, %f]\n", x, -M, -h);
				printf("Sol = %f\n", *sol);
			}
			else if (x >= h)
			{
				printf("x >= h\n");
				printf("x = %f existent a [%f, %f]\n", x, h, M);
				printf("Sol = %f\n", *sol);
			}
		} else
		{
			printf("No s'ha trobat una aproximació prou bona del zero a:\n");
			printf("x = %f existent a [%f, %f]\n", x, -M, -h);
		}
		
	}

	return 0;


}