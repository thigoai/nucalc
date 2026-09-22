#include "../include/bissecao.h"
#include <math.h>

double bissecao(double a, double b, double e, double (*f)(double)) {
  double x = a + ((b - a) / 2);

  while (fabs(f(x)) > e) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = a + ((b - a) / 2);
  }

  return x;
}
