#include "../include/nossos_metodos.h"

#include <math.h>

// Consiste em inicialmente utilizar o método do ponto fixo por alguams
// iterações para reduzir o intervalo Em seguida, utiliza-se o método da
// bisseção para uma convergência garantida até o epsilon
double metodo1(double a, double b, double e, double (*f)(double),
               double (*fi)(double)) {

  // Método do ponto fixo com 3 iterações
  // O que reduz o intervalo em 87,5%
  for (int i = 0; i < 3; i++) {
    double meio = a + (b - a) / 2.0f;
    double candidato = fi(meio);

    // O método do ponto fixo tem o problema de que pode escapar
    // Aqui a gente verifica se ainda está no intervalo
    // Ou seja, se mudou de sinal
    int dentro_do_intervalo = (candidato > a) && (candidato < b);
    int preserva_sinal = (f(a) * f(candidato) < 0) || (f(candidato) * f(b) < 0);

    double x;
    // Aqui o código tenta fazer dois chutes. O padrão é utilizar o método do
    // ponto fixo (um chute) Mas se der errado, ele faz o chute com o método da
    // bisseção (exata metade)
    if (dentro_do_intervalo && preserva_sinal) {
      x = candidato;
    } else {
      x = meio;
    }

    // A partir daqui é apenas o algoritmo do ponto fixo, visto em sala
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    if (fabs(f(x)) <= e) {
      return x;
    }
  }

  // Aqui é apenas o algoritmo da bisseção, visto em sala
  double x = a + (b - a) / 2.0f;

  while (fabs(f(x)) > e) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = a + (b - a) / 2.0f;
  }

  return x;
}
