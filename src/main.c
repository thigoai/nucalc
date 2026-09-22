#include "bissecao.c"
#include "funcoes.c"
#include "raizes.c"
#include <stdio.h>

int main() {
  printf("Isolando as raizes...\n");

  function_type f = get_function(F1);
  function_type fi = get_fi_function(F1);

  double lower = 0;
  double upper = 5;
  printf("lower: %f, upper: %f\n", lower, upper);
  double k = bissecao(lower, upper, 1e-3, f);

  return 0;
}
