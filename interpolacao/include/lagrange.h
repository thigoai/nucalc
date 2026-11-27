#ifndef LAGRANGE_H
#define LAGRANGE_H

#include "interpolacao.h"

/**
 * @brief Calcula os coeficientes monomiais do polinômio de base de Lagrange L_i(x).
 *
 * Constrói o polinômio L_i(x) = prod_{j != i} (x - x_j) / (x_i - x_j), que vale 1
 * em x = x_i e 0 nos demais pontos tabelados x_j, expandindo o numerador para a
 * forma monomial e dividindo cada coeficiente pelo denominador acumulado.
 *
 * @param grau Grau do polinômio interpolador (n >= 0).
 * @param i Índice do ponto de referência x_i (0 <= i <= grau).
 * @param pontos Vetor de entrada com grau + 1 pontos tabelados (x_k, y_k).
 * @param base Vetor de saída (tamanho grau + 1) que recebe os coeficientes
 * monomiais de L_i(x), do termo independente (base[0]) até x^grau.
 * 
 * @return true se o polinômio de base foi calculado com sucesso;
 *         false se o denominador for próximo de zero (pontos com x repetido).
 */
bool calcular_l_i(int grau, int i, const Ponto pontos[], long double base[]);


/**
 * @brief Método que implementa método de interpolação
 * polinomial de Lagrange.
 * 
 * Calcula os polinomios de bade l_i(x), expande cada um
 * para forma nomial e acumula P(x) = sum(y_i * l_i(x)) 
 * no vetor de coeficientes.
 * 
 * @param grau Grau do polinomio interpolador (n).
 * @param pontos Vetor de pontos (x_i, y_i)
 * @param coeficientes zVetor para guardar coeficientes monomiais de P(x).
*/


void interpolacao_lagrange(int grau, const Ponto pontos[],
                                       MetodoSistemaLinear resolver,
                                       double coeficientes[]);

#endif

