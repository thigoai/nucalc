#include "../include/pontofixo.h"

#include <math.h>

/**
 * @brief Implementa o método do Ponto Fixo para encontrar raízes de funções.
 * 
 * O método aproxima a raiz utilizando o Teorema do Ponto Fixo, onde cada
 * raiz aproximada é calculada a função fi até que o valor absoluto 
 * da função no ponto médio seja menor que a tolerância (e).
 * Pressupõe que a raiz está contida no intervalo, ou seja, f(a) e f(b) possuem sinais opostos.
 * 
 * @param a Limite esquerdo do intervalo analisado.
 * @param b Limite direito do intervalo analisado.
 * @param e Precisão aceitável.
 * @param f Ponteiro para uma das função a ser analisadas, definidas em 'funcoes.c'.
 * 
 * @return A raiz aproximada da função dentro da precisão 'e'.
 */

double pontofixo(double a, double b, double e, double (*f)(double),
                 double (*fi)(double)) {
  double x = fi((b - a) / 2); // chute inicial para valor de x.

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
    x = fi(x);
  }

  return x; // retorna um x com precisao aceitavel.
}
