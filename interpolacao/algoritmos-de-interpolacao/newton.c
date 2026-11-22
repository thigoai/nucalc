#include "../include/newton.h"
#include <math.h>

/**
 * @brief Tabela de diferenças divididas de Newton.
 * Monta a tabela e devolve os coeficientes que são a diagonal principal da tabela.
 *
 * @param grau Grau do polinômio
 * @param pontos Pontos tabelados (x_i, y_i)
 * @param coeficientes Vetor que recebe os grau + 1 coeficientes das diferenças divididas
 */
void diferencas_divididas(int grau, const Ponto pontos[],
                          double coeficientes[]) {
  int n = grau + 1;
  double tabela[MAX_GRAU + 1][MAX_GRAU + 1];

  // Primeira coluna: os próprios y_i
  for (int i = 0; i < n; i++) {
    tabela[i][0] = pontos[i].y;
  }

  // Colunas seguintes: diferenças divididas de ordem crescente
  for (int j = 1; j < n; j++) {
    for (int i = j; i < n; i++) {
      tabela[i][j] = (tabela[i][j - 1] - tabela[i - 1][j - 1]) /
                     (pontos[i].x - pontos[i - j].x);
    }
  }

  // Os coeficientes de Newton são a diagonal principal
  for (int k = 0; k < n; k++) {
    coeficientes[k] = tabela[k][k];
  }
}

/**
 * @brief Converte a forma de Newton para a forma monomial para poder avaliar
 *
 */
static void para_forma_monomial(int grau, const Ponto pontos[],
                                const double b[], double coeficientes[]) {
  for (int k = 0; k <= grau; k++) {
    coeficientes[k] = 0.0;
  }
  coeficientes[0] = b[0];

  // Guarda os coeficientes
  double termo[MAX_GRAU + 1];
  for (int k = 0; k <= grau; k++) {
    termo[k] = 0.0;
  }
  termo[0] = 1.0;

  for (int k = 0; k < grau; k++) {
    for (int p = k + 1; p >= 1; p--) {
      termo[p] = termo[p - 1] - pontos[k].x * termo[p];
    }
    termo[0] = -pontos[k].x * termo[0];

    for (int p = 0; p <= k + 1; p++) {
      coeficientes[p] += b[k + 1] * termo[p];
    }
  }
}

/**
 * @brief Método de interpolação de Newton (diferenças divididas)
 *
 * @param grau Grau do polinômio
 * @param pontos Pontos tabelados
 * @param resolver Resolvedor de sistema linear (ignorado neste método)
 * @param coeficientes Vetor que recebe os coeficientes monomiais de P(x)
 */
void interpolacao_diferencas_divididas(int grau, const Ponto pontos[],
                                       MetodoSistemaLinear resolver,
                                       double coeficientes[]) {
  (void)resolver;

  double b[MAX_GRAU + 1];
  diferencas_divididas(grau, pontos, b);
  para_forma_monomial(grau, pontos, b, coeficientes);
}
