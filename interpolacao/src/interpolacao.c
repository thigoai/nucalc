#include "../include/interpolacao.h"
#include "../include/lagrange.h"
#include "../include/linear_system.h"
#include "../include/newton.h"
#include <math.h>

// Pega dois pontos e gera os intervalos espaçados igualmente entre eles 
void gerar_pontos(double a, double b, int grau, function f, Ponto pontos[]) {
  int quantidade_pontos = grau + 1;
  double passo = (b - a) / grau;

  for (int i = 0; i < quantidade_pontos; i++) {
    pontos[i].x = a + (i * passo);
    pontos[i].y = f(pontos[i].x);
  }
}

// Método de Horner
double avaliar_polinomio(const double coeficientes[], int grau, double x) {
  double resultado = coeficientes[grau];

  for (int k = grau - 1; k >= 0; k--) {
    resultado = resultado * x + coeficientes[k];
  }

  return resultado;
}

// Os diferentes métodos implementados 
MetodoInterpolacao metodos_interpolacao[] = {
    interpolacao_sistema_linear,
    interpolacao_lagrange,
    interpolacao_diferencas_divididas,
};

const char *nomes_metodos_interpolacao[] = {
    "Sistema Linear",
    "Lagrange",
    "Diferencas divididas",
};

const int num_metodos_interpolacao =
    sizeof(metodos_interpolacao) / sizeof(metodos_interpolacao[0]);
