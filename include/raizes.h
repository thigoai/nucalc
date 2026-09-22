#include "funcoes.h"
#ifndef RAIZES_H
#define RAIZES_H

struct Raizes {
  double *arr;
  int size;
};

struct Raizes isolar_raizes(double a, double b, double h, function_type f);
void tabelar_raizes(double a, double b, double h, function_type f);

#endif
