#include "../include/funcoes.h"
#include <math.h>

double f1(double x) {
  return 2 * pow(x, 4) + 4 * pow(x, 3) + 3 * pow(x, 2) - 10 * x - 15;
}

double f2(double x) {
  return pow(x, 5) - 2 * pow(x, 4) - 9 * pow(x, 3) + 22 * pow(x, 2) + 4 * x -
         24;
}

double f3(double x) {
  return 5 * pow(x, 3) + pow(x, 2) - exp(1 - 2 * x) + cos(x) + 20;
}

double f4(double x) { return sin(x) * x + 4; }

double fi1(double x) {
  return (2 * pow(x, 4) + 4 * pow(x, 3) + 3 * pow(x, 2) - 15) / 10.0;
}

double fi2(double x) { return x - 0.02 * f2(x); }

double fi3(double x) { return x - 0.01 * f3(x); }

double fi4(double x) { return x - 0.1 * f4(x); }

function get_function(Funcao i) {
  switch (i) {
  case F1:
    return f1;
  case F2:
    return f2;
  case F3:
    return f3;
  case F4:
    return f4;
  }
}

function get_fi_function(Funcao i) {
  switch (i) {
  case F1:
    return fi1;
  case F2:
    return fi2;
  case F3:
    return fi3;
  case F4:
    return fi4;
  }
}

const Funcao funcoes[] = {F1, F2, F3, F4};
const int num_funcoes = 4;
