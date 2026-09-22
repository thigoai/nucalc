#include "../include/metodos.h"

#include <math.h>

const double EPSILON = 1e-6;

double bissecao(double a, double b, function f, function fi) {
  double x = a + ((b - a) / 2);

  while (fabs(f(x)) > EPSILON) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = a + ((b - a) / 2);
  }

  return x;
}

double falsa_posicao(double a, double b, function f, function fi) {
  double x = (a * f(b) - b * f(a)) / (f(b) - f(a));

  while (fabs(f(x)) > EPSILON) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = (a * f(b) - b * f(a)) / (f(b) - f(a));
  }

  return x;
}

double ponto_fixo(double a, double b, function f, function fi) {
  double x = fi((b - a) / 2);

  while (fabs(f(x)) > EPSILON) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = fi(x);
  }

  return x;
}

double df(function f, double x) { return (f(x) + f(x + EPSILON)) / EPSILON; }

double newton(double a, double b, function f, function fi) {
  double x = a + ((b - a) / 2);

  while (fabs(f(x)) > EPSILON) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = x - (f(x) / df(f, x));
  }

  return x;
}

double secante(double a, double b, function f, function fi) {
  double x2;

  while (fabs(f(b)) > EPSILON) {
    x2 = b - (f(b) * (b - a)) / (f(b) - f(a));

    a = b;
    b = x2;
  }

  return b;
}

// Consiste em inicialmente utilizar o método do ponto fixo por alguams
// iterações para reduzir o intervalo Em seguida, utiliza-se o método da
// bisseção para uma convergência garantida até o epsilon
double metodo1(double a, double b, function f, function fi) {
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

    if (fabs(f(x)) <= EPSILON) {
      return x;
    }
  }

  // Aqui é apenas o algoritmo da bisseção, visto em sala
  double x = a + (b - a) / 2.0f;

  while (fabs(f(x)) > EPSILON) {
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = a + (b - a) / 2.0f;
  }

  return x;
}

MetodoNumerico metodos[] = {bissecao, newton, ponto_fixo, secante,
                            falsa_posicao};
const int num_metodos = sizeof(metodos) / sizeof(metodos[0]);
