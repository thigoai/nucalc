#include "../include/pontofixo.h"

#include <math.h>

double pontofixo(double a, double b, double e, double (*f)(double),
                 double (*fi)(double)) {
  double x = fi((b - a) / 2);

  while (fabs(f(x)) > e) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = fi(x);
  }

  return x;
}
