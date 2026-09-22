#include "../include/raizes.h"
#include "bissecao.c"
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

void tabelar_valores(double a, double b, double h, function_type f) {
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

void tabelar_raizes(struct Raizes *r, function_type f, double epsilon) {
  printf("---------------------------------\n");
  printf("| %-13s | %-13s | %-13s |\n", "a", "b", "raiz");
  printf("---------------------------------\n");
  for (int i = 0; i < r->size; i += 2) {
    double a = r->arr[i];
    double b = r->arr[i + 1];
    double raiz = bissecao(r->arr[i], r->arr[i + 1], epsilon, f);

    printf("| %-13lf | %-13lf | %-13lf |\n", a, b, raiz);
  }
  printf("---------------------------------\n");
}
