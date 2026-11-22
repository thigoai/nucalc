#ifndef NEWTON_H
#define NEWTON_H

#include "interpolacao.h"

// Declaração: Tabela de diferenças divididas (coeficientes de Newton)
void diferencas_divididas(int grau, const Ponto pontos[],
                          double coeficientes[]);

// Declaração: Função de interpolação por diferenças divididas
void interpolacao_diferencas_divididas(int grau, const Ponto pontos[],
                                       MetodoSistemaLinear resolver,
                                       double coeficientes[]);

#endif
