#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

#include "interpolacao.h"
#include <stdbool.h>

// Declaração: Os diferentes métodos de resolução de sistema linear
bool gauss(int n, double A[n][n], double B[n], double x[n]);
bool lu(int n, double A[n][n], double B[n], double x[n]);
bool jacobi(int n, double A[n][n], double B[n], double x[n]);
bool seidel(int n, double A[n][n], double B[n], double x[n]);

// Declaração: Função para resolver o sistema linear. Vai usar algum dos métodos acima
void resolver_sistema_linear(int grau, const Ponto pontos[],
                             MetodoSistemaLinear resolver,
                             double coeficientes[]);

// Declaração: Função para interpolar o sistema linear
void interpolacao_sistema_linear(int grau, const Ponto pontos[],
                                 MetodoSistemaLinear resolver,
                                 double coeficientes[]);

// Registro de resolvedores
extern MetodoSistemaLinear metodos_sistema_linear[];
extern const char *nomes_sistema_linear[];
extern const int num_metodos_sistema_linear;

#endif
