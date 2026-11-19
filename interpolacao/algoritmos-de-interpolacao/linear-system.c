#include "../include/linear_system.h"

#include <math.h>
#include <stdbool.h>

#define PIVO_MINIMO 1e-14
#define TOLERANCIA_ITER 1e-12
#define MAX_ITERACOES 200000

/**
 * @brief Eliminacao de Gauss com pivoteamento parcial
 *
 * @param n Dimensao do sistema
 * @param A Matriz dos coeficientes 
 * @param B Termos independentes
 * @param x Vetor que recebe a solucao
 * @return false se o sistema for singular; true caso contrario
 */
bool gauss(int n, double A[n][n], double B[n], double x[n]) {
  for (int k = 0; k < n; k++) {
    // Pivô = Linha de maior módulo na coluna k 
    int pivo = k;
    for (int i = k + 1; i < n; i++) {
      if (fabs(A[i][k]) > fabs(A[pivo][k])) {
        pivo = i;
      }
    }

    if (fabs(A[pivo][k]) < PIVO_MINIMO) {
      return false;
    }

    // Linha pivo <-> Linha atual (Troca)
    if (pivo != k) {
      for (int j = 0; j < n; j++) {
        double tmp = A[k][j];
        A[k][j] = A[pivo][j];
        A[pivo][j] = tmp;
      }
      double tmp = B[k];
      B[k] = B[pivo];
      B[pivo] = tmp;
    }

    // Elimina abaixo do pivô
    for (int i = k + 1; i < n; i++) {
      double fator = A[i][k] / A[k][k];
      for (int j = k; j < n; j++) {
        A[i][j] -= fator * A[k][j];
      }
      B[i] -= fator * B[k];
    }
  }

  // Substitui regressivamente
  for (int i = n - 1; i >= 0; i--) {
    double soma = B[i];
    for (int j = i + 1; j < n; j++) {
      soma -= A[i][j] * x[j];
    }
    x[i] = soma / A[i][i];
  }

  return true;
}

/**
 * @brief Fatoracao LU com pivoteamento parcial (PA = LU) | Resolve Ly = Pb e depois Ux = y
 *
 * @param n Dimensao do sistema
 * @param A Matriz dos coeficientes (L e U)
 * @param B Termos independentes
 * @param x Vetor que recebe a solucao
 * @return false se o sistema for singular; true caso contrario
 */
bool lu(int n, double A[n][n], double B[n], double x[n]) {
  int perm[n];
  for (int i = 0; i < n; i++) {
    perm[i] = i;
  }

  // Fatoracao: PA = LU
  for (int k = 0; k < n; k++) {
    int pivo = k;
    for (int i = k + 1; i < n; i++) {
      if (fabs(A[i][k]) > fabs(A[pivo][k])) {
        pivo = i;
      }
    }

    if (fabs(A[pivo][k]) < PIVO_MINIMO) {
      return false;
    }

    if (pivo != k) {
      for (int j = 0; j < n; j++) {
        double tmp = A[k][j];
        A[k][j] = A[pivo][j];
        A[pivo][j] = tmp;
      }
      int tmp = perm[k];
      perm[k] = perm[pivo];
      perm[pivo] = tmp;
    }

    for (int i = k + 1; i < n; i++) {
      A[i][k] /= A[k][k];
      for (int j = k + 1; j < n; j++) {
        A[i][j] -= A[i][k] * A[k][j];
      }
    }
  }

  // Substituição: Ly = Pb
  double y[n];
  for (int i = 0; i < n; i++) {
    y[i] = B[perm[i]];
    for (int j = 0; j < i; j++) {
      y[i] -= A[i][j] * y[j];
    }
  }

  // Substituindo regressivamente
  for (int i = n - 1; i >= 0; i--) {
    x[i] = y[i];
    for (int j = i + 1; j < n; j++) {
      x[i] -= A[i][j] * x[j];
    }
    x[i] /= A[i][i];
  }

  return true;
}

/**
 * @brief Gauss-Jacobi
 */
bool jacobi(int n, double A[n][n], double B[n], double x[n]) {
  double x_velho[n];
  for (int i = 0; i < n; i++) {
    x_velho[i] = 0.0;
  }

  for (int iter = 0; iter < MAX_ITERACOES; iter++) {
    double delta = 0.0;

    for (int i = 0; i < n; i++) {
      double soma = B[i];
      for (int j = 0; j < n; j++) {
        if (j != i) {
          soma -= A[i][j] * x_velho[j];
        }
      }

      x[i] = soma / A[i][i];
      delta = fmax(delta, fabs(x[i] - x_velho[i]));

      if (!isfinite(x[i])) {
        return false;
      }
    }

    for (int i = 0; i < n; i++) {
      x_velho[i] = x[i];
    }

    if (delta <= TOLERANCIA_ITER) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Gauss-Seidel
 */
bool seidel(int n, double A[n][n], double B[n], double x[n]) {
  for (int i = 0; i < n; i++) {
    x[i] = 0.0;
  }

  for (int iter = 0; iter < MAX_ITERACOES; iter++) {
    double delta = 0.0;

    for (int i = 0; i < n; i++) {
      double soma = B[i];
      for (int j = 0; j < n; j++) {
        if (j != i) {
          soma -= A[i][j] * x[j];
        }
      }

      double novo = soma / A[i][i];
      delta = fmax(delta, fabs(novo - x[i]));
      x[i] = novo;

      if (!isfinite(x[i])) {
        return false;
      }
    }

    if (delta <= TOLERANCIA_ITER) {
      return true;
    }
  }

  return false;
}

// ============================================================================================
// MONTAGEM DO SISTEMA E METODO DE INTERPOLACAO
// ============================================================================================ 

/**
 * @brief Monta o sistema de Vandermonde e entrega ao resolvedor escolhido.
 *
 * Cada ponto i gera a linha: a0 + a1*x_i + a2*x_i^2 + ... = y_i.
 * As potencias sao calculadas por multiplicacoes sucessivas, que sao mais
 * precisas e mais rapidas que pow() nesse caso.
 */
void resolver_sistema_linear(int grau, const Ponto pontos[],
                             MetodoSistemaLinear resolver,
                             double coeficientes[]) {
  int n = grau + 1;
  double A[n][n];
  double B[n];

  for (int i = 0; i < n; i++) {
    B[i] = pontos[i].y;
    A[i][0] = 1.0;
    for (int j = 1; j < n; j++) {
      A[i][j] = A[i][j - 1] * pontos[i].x;
    }
  }

  /* Se o resolvedor falhar, deixa NAN para o teste reprovar. */
  if (!resolver(n, A, B, coeficientes)) {
    for (int i = 0; i < n; i++) {
      coeficientes[i] = NAN;
    }
  }
}

void interpolacao_sistema_linear(int grau, const Ponto pontos[],
                                 MetodoSistemaLinear resolver,
                                 double coeficientes[]) {
  resolver_sistema_linear(grau, pontos, resolver, coeficientes);
}

MetodoSistemaLinear metodos_sistema_linear[] = {gauss, lu, jacobi, seidel};
const char *nomes_sistema_linear[] = {"Gauss (pivo parcial)",
                                      "LU (pivo parcial)", "Gauss-Jacobi",
                                      "Gauss-Seidel"};
const int num_metodos_sistema_linear =
    sizeof(metodos_sistema_linear) / sizeof(metodos_sistema_linear[0]);
