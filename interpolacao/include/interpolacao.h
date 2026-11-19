#ifndef INTERPOLACAO_H
#define INTERPOLACAO_H

#include "funcoes.h"
#include <stdbool.h>

#define MAX_GRAU 10

typedef struct {
  double x;
  double y;
} Ponto;

// Assinatura: Resolvedor de sistema linear
typedef bool (*MetodoSistemaLinear)(int n, double A[n][n], double B[n], double x[n]);

// Assinatura: Interpolação
typedef void (*MetodoInterpolacao)(int grau, const Ponto pontos[],
                                   MetodoSistemaLinear resolver,  // Ignorado caso seja Diferenças Divididas ou Lagrange
                                   double coeficientes[]);

// Assinatura: Função de pegar dois pontos e retornar intervalos igualmente espaçados entre eles
void gerar_pontos(double a, double b, int grau, function f, Ponto pontos[]);

// Assinatura: Avaliar polinômio. Será utilizado  o método de Horner
double avaliar_polinomio(const double coeficientes[], int grau, double x);

// Registro dos métodos de interpolação
extern MetodoInterpolacao metodos_interpolacao[];
extern const char *nomes_metodos_interpolacao[];
extern const int num_metodos_interpolacao;

#endif
