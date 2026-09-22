#ifndef METODOS_H
#define METODOS_H

#include "funcoes.h"

extern const double EPSILON;

typedef double (*MetodoNumerico)(double a, double b, function f, function fi);

double bissecao(double a, double b, function f, function fi);
double falsa_posicao(double a, double b, function f, function f1);
double ponto_fixo(double a, double b, function f, function fi);
double newton(double a, double b, function f, function fi);
double secante(double a, double b, function f, function fi);
// Consiste em inicialmente inicialmente utilizar o método do ponto fixo, apenas
// para reduzir o intervalo Em seguida, utiliza o método da bisseção para uma
// convergência garantida
double metodo1(double a, double b, function f, function fi);

double df_func(double (*f)(double), double x);

extern MetodoNumerico metodos[];
extern const int num_metodos;

#endif
