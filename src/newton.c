#include "../include/newton.h"

#include <math.h>



/**
 * @brief Calcula a aproximação numérica da derivada de uma função.
 * 
 * @param f Ponteiro para a função a ser derivada.
 * @param x Ponto no qual a derivada será avaliada.
 * @param h Incremento para o cálculo da aproximação.
 * 
 * @return O valor aproximado da derivada da função no ponto x.
 */
double df_func(double (*f)(double), double x, double h) {
  return (f(x + h) - f(x)) / h;
}

/**
 * @brief Implementa o método de Newton para encontrar raízes de funções.
 * 
 * O método aproxima a raiz utilizando a reta tangente à curva da função no ponto 
 * atual (x), iterando até que o valor absoluto de f(x) seja menor que a tolerância (e).
 * A derivada da função, necessária para o cálculo do passo, é aproximada numericamente.
 * O chute inicial é definido como o ponto médio do intervalo [a, b].
 * 
 * @param a Limite esquerdo do intervalo analisado (usado para o chute inicial).
 * @param b Limite direito do intervalo analisado (usado para o chute inicial).
 * @param e Precisão aceitável.
 * @param f Ponteiro para uma das função a ser analisadas, definidas em 'funcoes.c'.
 * 
 * @return A raiz aproximada da função dentro da precisão 'e'.
 */

double newton(double a, double b, double e, double (*f)(double)) {
  double x = a + ((b - a) / 2); // chute inicial para valor de x.

  // Enquanto o valor do de f(x) for maior que a precisão aceitavel, faça:   
  while (fabs(f(x)) > e) {
    // verifica se o zero da função está entre a e x.
    if (f(a) * f(x) < 0) {
      // se sim, b recebe valor de x. o intervalo passa a ser [a,x]
      b = x;
    } else {
      // senão a recebe o valor de x e o intervalo passa a ser [x, b].
      a = x;
    }

    // x recebe a próxima aproximação.
    x = x - (f(x) / df_func(f, x, e));
  }

  return x; // retorna um x com precisao aceitavel.
}
