#include "../include/newton.h"

#include <math.h>

double df_func(double (*f)(double), double x, double h) {
  return (f(x) + f(x + h)) / h;
}

double newton(double a, double b, double e, double (*f)(double)) {
  double x = a + ((b - a) / 2);

  while (fabs(f(x)) > e) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = x - (f(x) / df_func(f, x, e));
  }

  return x;
}
