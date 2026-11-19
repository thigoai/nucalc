#ifndef METRICA_H
#define METRICA_H

#include "funcoes.h"
#include "interpolacao.h"
#include <stdbool.h>

// Tolerância dos testes
#define TOLERANCIA 1e-8

struct Metricas {
  double tempo;                 // Tempo da interpolação (Segundos)
  double erro;                  // Margem de erro (|P(x_i) - y_i|) 
  bool convergiu;               // Entregou solução? (Sim ou Não)
  bool finish;                  // O erro passou da tolerância? (Sim ou Não)
  int grau;
  double coeficientes[MAX_GRAU + 1];
};

// Roda um método de interpolação
struct Metricas executar_interpolacao(MetodoInterpolacao metodo,
                                      MetodoSistemaLinear resolver, function f,
                                      double a, double b, int grau);

// Exibe as respostas
void imprimir_resposta(double a, double b, int amostras, function f,
                       const struct Metricas *m);

#endif
