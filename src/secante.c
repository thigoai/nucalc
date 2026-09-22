#include "../include/secante.h"
#include <math.h>

double secante(double a, double b, double e, double (*f)(double)) {
  double x2;

  while (fabs(f(b)) > e) {
    x2 = b - (f(b) * (b - a)) / (f(b) - f(a));

    a = b;
    b = x2;
  }

  return b;
}
