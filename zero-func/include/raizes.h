#include "funcoes.h"
#include "metodos.h"
#ifndef RAIZES_H
#define RAIZES_H

struct Raizes {
  double *arr;
  int size;
};

struct Raizes isolar_raizes(double a, double b, double h, function f);

void tabelar_valores(double a, double b, double h, function f);
void tabelar_raizes(struct Raizes *r, function f, function fi,
                    MetodoNumerico metodo);

#endif
