#include "funcoes.c"
#include "raizes.c"
#include <stdio.h>

int main() {
  printf("Isolando as raizes...\n");

  function f = get_function(F1);
  function fi = get_fi_function(F1);

  struct Raizes rs = isolar_raizes(-10, 10, 1, f);

  tabelar_valores(-10, 10, 1, f);
  tabelar_raizes(&rs, f, fi, metodo1);

  return 0;
}
