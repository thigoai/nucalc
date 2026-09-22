#ifndef NEWTON_H
#define NEWTON_H

double df_func(double (*f)(double), double x, double h);
double newton(double a, double b, double e, double (*f)(double));

#endif
