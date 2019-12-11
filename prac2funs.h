#ifndef PRAC2FUNS
#define PRAC2FUNS

void resTinf(int n, double **L, double *b, double *x);
void resTsup(int n, double **U, double *b, double *x);
void prodMatVec(int m, int n, double **A, double *x, double *y);
double norma2(int n, double *z);
void prodMatMat(int m, int n, int p, double **A, double **B, double **C);
int newton(double x, double *sol, double tol, int iter);

#endif