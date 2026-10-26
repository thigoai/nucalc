#include "../include/metodos.h"

#include <math.h>

const double EPSILON = 1e-6;
const int MAX_ITER = 10000;

/**
 * @brief Implementa o método da Bissecção para encontrar raízes de funções.
 *
 * O método divide o intervalo [a, b] ao meio iterativamente até que
 * o valor absoluto da função no ponto médio seja menor que a tolerância (e).
 * Pressupõe que a raiz está contida no intervalo, ou seja, f(a) e f(b) possuem
 * sinais opostos.
 *
 * @param a Limite esquerdo do intervalo analisado.
 * @param b Limite direito do intervalo analisado.
 * @param f Ponteiro para uma das função a ser analisadas, definidas em
 * 'funcoes.c'.
 * @param fi Ponteiro para a fi de f, não utilizado nesse método.
 *
 * @return A raiz aproximada da função dentro da precisão EPSILON e a quantidade
 * de iterações.
 */
RetornoMetodo bissecao(double a, double b, function f, function fi) {
  int iteracoes = 0;
  double x = a + ((b - a) / 2); // O meio do intervalo inicial é atribuido a x.

  // Enquanto o valor do de f(x) for maior que a precisão aceitavel, faça:
  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;

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

  // retorna um x com precisao aceitavel.
  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}

/**
 * @brief Implementa o método da Falsa Posição para encontrar raízes de funções.
 *
 * O método aproxima a raiz utilizando a reta secante, analisando o ponto em que
 * ela corta o eixo x iterando até que o valor absoluto de f(x) seja menor que a
 * tolerância (e).
 *
 * @param a Limite esquerdo do intervalo analisado.
 * @param b Limite direito do intervalo analisado.
 * @param e Precisão aceitável.
 * @param f Ponteiro para uma das função a ser analisadas, definidas em
 * 'funcoes.c'.
 * @param fi Ponteiro para a fi de f, não utilizado nesse método.
 *
 * @return A raiz aproximada da função dentro da precisão EPSILON e a quantidade
 * de iterações.
 */
RetornoMetodo falsa_posicao(double a, double b, function f, function fi) {
  // chute inicial para valor de x.
  double x = (a * f(b) - b * f(a)) / (f(b) - f(a));
  int iteracoes = 0;

  // Enquanto o valor do de f(x) for maior que a precisão aceitavel, faça:
  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
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

  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}

/**
 * @brief Implementa o método do Ponto Fixo para encontrar raízes de funções.
 *
 * O método aproxima a raiz utilizando o Teorema do Ponto Fixo, onde cada
 * raiz aproximada é calculada a função fi até que o valor absoluto
 * da função no ponto médio seja menor que a tolerância (e).
 * Pressupõe que a raiz está contida no intervalo, ou seja, f(a) e f(b) possuem
 * sinais opostos.
 *
 * @param a Limite esquerdo do intervalo analisado.
 * @param b Limite direito do intervalo analisado.
 * @param e Precisão aceitável.
 * @param f Ponteiro para uma das função a ser analisadas, definidas em
 * 'funcoes.c'.
 * @param fi Ponteiro para a fi de f.
 *
 * @return A raiz aproximada da função dentro da precisão EPSILON e a quantidade
 * de iterações.
 */
RetornoMetodo ponto_fixo(double a, double b, function f, function fi) {
  double x = fi((b - a) / 2); // chute inicial para valor de x.
  int iteracoes = 0;

  // Enquanto o valor do de f(x) for maior que a precisão aceitavel, faça:
  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
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

  // retorna um x com precisao aceitavel.
  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}

/**
 * @brief Calcula a aproximação numérica da derivada de uma função.
 *
 * @param f Ponteiro para a função a ser derivada.
 * @param x Ponto no qual a derivada será avaliada.
 *
 * @return O valor aproximado da derivada da função no ponto x.
 */
double df(function f, double x) { return (f(x + EPSILON) - f(x)) / EPSILON; }

/**
 * @brief Implementa o método de Newton para encontrar raízes de funções.
 *
 * O método aproxima a raiz utilizando a reta tangente à curva da função no
 * ponto atual (x), iterando até que o valor absoluto de f(x) seja menor que a
 * tolerância (e). A derivada da função, necessária para o cálculo do passo, é
 * aproximada numericamente. O chute inicial é definido como o ponto médio do
 * intervalo [a, b].
 *
 * @param a Limite esquerdo do intervalo analisado (usado para o chute inicial).
 * @param b Limite direito do intervalo analisado (usado para o chute inicial).
 * @param f Ponteiro para uma das função a ser analisadas, definidas em
 * 'funcoes.c'.
 * @param fi Ponteiro para a fi de f, não utilizado nesse método.
 *
 * @return A raiz aproximada da função dentro da precisão EPSILON e a quantidade
 * de iterações.
 */
RetornoMetodo newton(double a, double b, function f, function fi) {
  double x = a + ((b - a) / 2); // chute inicial para valor de x.
  int iteracoes = 0;

  // Enquanto o valor do de f(x) for maior que a precisão aceitavel, faça:
  while (fabs(f(x)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;
    // verifica se o zero da função está entre a e x.
    if (f(a) * f(x) < 0) {
      // se sim, b recebe valor de x. o intervalo passa a ser [a,x]
      b = x;
    } else {
      // senão a recebe o valor de x e o intervalo passa a ser [x, b].
      a = x;
    }

    // x recebe a próxima aproximação.
    x = x - (f(x) / df(f, x));
  }

  // retorna um x com precisao aceitavel.
  return (RetornoMetodo){.raiz = x, .iteracoes = iteracoes};
}
/**
 * @brief Implementa o método da Secante para encontrar raízes de funções.
 *
 * O método aproxima a raiz utilizando aproximações por diferenças finitas para
 * substituir a derivada do método de Newton. Utiliza dois pontos anteriores (a
 * e b) para traçar uma reta secante e determinar a próxima estimativa da raiz,
 * iterando até que |f(b)| seja menor que a tolerância EPSILON ou atinja
 * MAX_ITER. Diferente da Bissecção e da Falsa Posição, não exige que a raiz
 * esteja estritamente confinada no intervalo a cada passo.
 *
 * @param a Primeiro ponto inicial da aproximação (x_{k-1}).
 * @param b Segundo ponto inicial da aproximação (x_k).
 * @param f Ponteiro para a função analisada.
 * @param fi Ponteiro para a função de iteração, não utilizado nesse método.
 *
 * @return A raiz aproximada da função dentro da precisão EPSILON e a quantidade
 * de iterações.
 */
RetornoMetodo secante(double a, double b, function f, function fi) {
  int iteracoes = 0;
  double x2;

  // Enquanto a função no ponto atual for maior que a precisão tolerada, faça:
  while (fabs(f(b)) > EPSILON && iteracoes < MAX_ITER) {
    iteracoes++;

    // Calcula a próxima aproximação da raiz pela interseção da reta secante com
    // o eixo x.
    x2 = b - (f(b) * (b - a)) / (f(b) - f(a));

    // Atualiza os pontos para a próxima iteração: a recebe o ponto anterior e b
    // recebe a nova estimativa.
    a = b;
    b = x2;
  }

  // Retorna a raiz estimada com precisão aceitável e a contagem de iterações.
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

MetodoNumerico metodos[] = {bissecao, newton,        ponto_fixo,
                            secante,  falsa_posicao, metodo1};
const int num_metodos = sizeof(metodos) / sizeof(metodos[0]);
