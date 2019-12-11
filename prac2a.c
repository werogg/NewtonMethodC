/* OTERO MARTIN JOEL - DNI: 53637165S */
#include <stdio.h>
#include <stdlib.h>
#include "prac2funs.h"

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



	printf("S'executara newton amb:\niter = %d\nx = %f\ntol = %f", iter, x, tol);

    newton(x, sol, tol, iter);

    printf("Sol = %f", *sol);

	return 0;


}