#include "../include/bissecao.h"
#include <math.h>


/**
 * @brief Implementa o método da Bissecção para encontrar raízes de funções.
 * 
 * O método divide o intervalo [a, b] ao meio iterativamente até que 
 * o valor absoluto da função no ponto médio seja menor que a tolerância (e).
 * 
 * @param a Limite esquerdo do intervalo analisado.
 * @param b Limite direito do intervalo analisado.
 * @param e Precisão aceitável.
 * @param f Ponteiro para uma das função a ser analisadas, definidas em 'funcoes.c'.
 * 
 * @return A raiz aproximada da função dentro da precisão 'e'.
 */

double bissecao(double a, double b, double e, double (*f)(double)) {
  double x = a + ((b - a) / 2); // O meio do intervalo inicial é atribuido a x.

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

    // x recebe o meio do novo intervalo.
    x = a + ((b - a) / 2);
  }

  return x; // retorna um x com precisao aceitavel.
}
