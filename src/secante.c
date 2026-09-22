#include "../include/secante.h"
#include <math.h>

/**
 * @brief Implementa o método da Secante para encontrar raízes de funções.
 * 
 * O método é uma variação do método de Newton. Em vez de calcular a derivada 
 * numericamente, ele aproxima a inclinação da reta traçando uma secante entre 
 * as duas últimas aproximações (a e b). O ponto de interseção dessa reta com o 
 * eixo x torna-se a nova aproximação. O processo se repete até que o valor da 
 * função atinja a tolerância (e).
 *  *
 * @param a Primeira aproximação inicial.
 * @param b Segunda aproximação inicial.
 * @param e Precisão aceitável.
 * @param f Ponteiro para a função a ser derivada.
 * 
 * @return A raiz aproximada da função dentro da precisão 'e'.
 */
double secante(double a, double b, double e, double (*f)(double)) {
  double x2;

  // Enquanto o valor do de f(x) for maior que a precisão aceitavel, faça:   
  while (fabs(f(b)) > e) {

    // este método não verifica sinais opostos.
    x2 = b - (f(b) * (b - a)) / (f(b) - f(a));

    a = b;
    b = x2;
  }

  return b;
}
