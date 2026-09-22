#ifndef METODOS_H
#define METODOS_H

#include "funcoes.h"

extern const double EPSILON;

typedef struct {
  int iteracoes;
  double raiz;
} RetornoMetodo;

typedef RetornoMetodo (*MetodoNumerico)(double a, double b, function f,
                                        function fi);

RetornoMetodo bissecao(double a, double b, function f, function fi);
RetornoMetodo falsa_posicao(double a, double b, function f, function f1);
RetornoMetodo ponto_fixo(double a, double b, function f, function fi);
RetornoMetodo newton(double a, double b, function f, function fi);
RetornoMetodo secante(double a, double b, function f, function fi);
// Consiste em inicialmente inicialmente utilizar o método do ponto fixo, apenas
// para reduzir o intervalo Em seguida, utiliza o método da bisseção para uma
// convergência garantida
RetornoMetodo metodo1(double a, double b, function f, function fi);

double df(double (*f)(double), double x);

extern MetodoNumerico metodos[];
extern const int num_metodos;

#endif
