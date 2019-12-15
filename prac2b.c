/* OTERO MARTIN JOEL - DNI: 53637165S */
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

		/* Condició de no retorn */
		if (fabs(df(x)) < tol) return 1;

		/* Condicions de retorn */
        if (fabs(next_x-x) < tol || fabs(f(x)) < tol)
        {
            *sol = next_x;
            return 0;
        }

		/* Seguent iteració */
        x = next_x;
    }
	return 1; /* No retorn */
}

int main(void)
{
	/* Inicialització de les dades */
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

	/* Iterem per l'interval [-M, M] amb pas h */
	for (x = -M; x <= M; x += h)
	{
		int s = newton(x, sol, tol, iter);

		if (s == 0) /* Si hi ha solució */
		{
			/* Printem solucions per a <=-h i per a >=h */
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