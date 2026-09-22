#include "../include/falsapos.h"

#include <math.h>

double falsapos(double a, double b, double e, double (*f)(double)) {

  double x = (a * f(b) - b * f(a)) / (f(b) - f(a));

  while (fabs(f(x)) > e) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = (a * f(b) - b * f(a)) / (f(b) - f(a));
  }

  return x;
}
