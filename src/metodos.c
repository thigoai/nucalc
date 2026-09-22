#include "../include/metodos.h"

#include <math.h>

const double EPSILON = 1e-6;
const int MAX_ITER = 10000;

RetornoMetodo bissecao(double a, double b, function f, function fi) {
  int iteracoes = 0;
  double x = a + ((b - a) / 2);

  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = a + ((b - a) / 2);
  }

  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}

RetornoMetodo falsa_posicao(double a, double b, function f, function fi) {
  double x = (a * f(b) - b * f(a)) / (f(b) - f(a));
  int iteracoes = 0;

  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = (a * f(b) - b * f(a)) / (f(b) - f(a));
  }

  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}

RetornoMetodo ponto_fixo(double a, double b, function f, function fi) {
  double x = fi((b - a) / 2);
  int iteracoes = 0;

  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = fi(x);
  }

  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}

double df(function f, double x) { return (f(x + EPSILON) - f(x)) / EPSILON; }

RetornoMetodo newton(double a, double b, function f, function fi) {
  double x = a + ((b - a) / 2);
  int iteracoes = 0;

  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = x - (f(x) / df(f, x));
  }

  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}

RetornoMetodo secante(double a, double b, function f, function fi) {
  int iteracoes = 0;
  double x2;

  while (fabs(f(b)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
    x2 = b - (f(b) * (b - a)) / (f(b) - f(a));

    a = b;
    b = x2;
  }

  return (RetornoMetodo){.raiz = b, .iteracoes = iteracoes};
}

// Consiste em inicialmente utilizar o método do ponto fixo por alguams
// iterações para reduzir o intervalo Em seguida, utiliza-se o método da
// bisseção para uma convergência garantida até o epsilon
RetornoMetodo metodo1(double a, double b, function f, function fi) {
  int iteracoes = 0;

  // Método do ponto fixo com 3 iterações
  // O que reduz o intervalo em 87,5%
  for (int i = 0; i < 3; i++, iteracoes++) {

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
      return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
    }
  }

  // Aqui é apenas o algoritmo da bisseção, visto em sala
  double x = a + (b - a) / 2.0f;

  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
    if (f(a) * f(x) < 0) {
      b = x;
    } else {
      a = x;
    }

    x = a + (b - a) / 2.0f;
  }

  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}

MetodoNumerico metodos[] = {bissecao, newton, ponto_fixo, secante,
                            falsa_posicao};
const int num_metodos = sizeof(metodos) / sizeof(metodos[0]);
