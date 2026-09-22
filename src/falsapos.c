#include "../include/falsapos.h"

#include <math.h>

/**
 * @brief Implementa o método da Falsa Posição para encontrar raízes de funções.
 * 
 * O método aproxima a raiz utilizando a reta secante, analisando o ponto em que ela corta o eixo x 
 * iterando até que o valor absoluto de f(x) seja menor que a tolerância (e).
 * 
 * @param a Limite esquerdo do intervalo analisado.
 * @param b Limite direito do intervalo analisado.
 * @param e Precisão aceitável.
 * @param f Ponteiro para uma das função a ser analisadas, definidas em 'funcoes.c'.
 * 
 * @return A raiz aproximada da função dentro da precisão 'e'.
 */
double falsapos(double a, double b, double e, double (*f)(double)) {

  double x = (a * f(b) - b * f(a)) / (f(b) - f(a)); // chute inicial para valor de x.

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
    x = (a * f(b) - b * f(a)) / (f(b) - f(a));
  }

  return x;
}
