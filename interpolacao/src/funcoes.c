#include "../include/funcoes.h"
#include <math.h>
#include <stddef.h>

// f1(x) = e^x  
double f1(double x) { return exp(x); }

// f2(x) = 1 / (1 + 25x^2)
double f2(double x) { return 1 / (1 + (25 * pow(x, 2))); }

double fi1(double x) { return exp(x) / 10.0; }

double fi2(double x) { return (1 / (1 + (25 * pow(x, 2)))) / 10.0; }

function get_function(Funcao i) {
  switch (i) {
  case F1:
    return f1;
  case F2:
    return f2;
  }
  return NULL;
}

function get_fi_function(Funcao i) {
  switch (i) {
  case F1:
    return fi1;
  case F2:
    return fi2;
  }
  return NULL;
}

const Funcao funcoes[] = {F1, F2};
const int num_funcoes = 2;
