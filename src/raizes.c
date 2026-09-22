#include "../include/raizes.h"
#include <stdio.h>
#include <stdlib.h>

struct Raizes isolar_raizes(double a, double b, double h, function_type f) {

  double *raizes = malloc(sizeof(double) * 100);
  int size = 0;
  double curr = a;

  while (curr < b) {
    if (f(curr) * f(curr + h) < 0) {
      raizes[size] = curr;
      raizes[size + 1] = curr + h;
      size += 2;
    }

    curr += h;
  }

  struct Raizes r;
  r.arr = raizes;
  r.size = size;

  return r;
}

void tabelar_raizes(double a, double b, double h, function_type f) {

  printf("---------------------------------\n");
  printf("| %-13s | %-13s |\n", "x", "f(x), fi_func");
  printf("---------------------------------\n");

  double curr = a;

  while (curr <= b) {
    printf("| %-13.4f | %-13.4f |\n", curr, f(curr));
    curr += h;
  }

  printf("---------------------------------\n");
}
