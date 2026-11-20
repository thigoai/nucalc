#define _POSIX_C_SOURCE 199309L

#include "../include/metrica.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

struct Metricas executar_interpolacao(MetodoInterpolacao metodo,
                                      MetodoSistemaLinear resolver, function f,
                                      double a, double b, int grau) {
  struct Metricas m = {.tempo = 0.0,
                       .erro = 0.0,
                       .convergiu = true,
                       .finish = false,
                       .grau = grau};

  Ponto pontos[MAX_GRAU + 1];
  gerar_pontos(a, b, grau, f, pontos);

  struct timespec inicio, fim;
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  metodo(grau, pontos, resolver, m.coeficientes);
  clock_gettime(CLOCK_MONOTONIC, &fim);

  m.tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

 // Verificador de convergência 
  for (int i = 0; i <= grau; i++) {
    if (!isfinite(m.coeficientes[i])) {
      m.convergiu = false;
      m.erro = INFINITY;
      return m;
    }
  }

  // Analisa os resíduos de erro
  for (int i = 0; i <= grau; i++) {
    double erro =
        fabs(avaliar_polinomio(m.coeficientes, grau, pontos[i].x) - pontos[i].y);
    if (erro > m.erro) {
      m.erro = erro;
    }
  }

  m.finish = m.erro <= TOLERANCIA;
  return m;
}

// Tabelar os resultados de um determinado método
// OBS: Colocar no CSV de Raoni depois talvez
void imprimir_resposta(double a, double b, int amostras, function f,
                       const struct Metricas *m) {
  if (!m->convergiu) {
    printf("  Resolvedor nao convergiu; sem polinomio para exibir.\n");
    return;
  }

  printf("  P(x) = %.6g", m->coeficientes[0]);
  for (int k = 1; k <= m->grau; k++) {
    printf(" %c %.6g*x^%d", m->coeficientes[k] < 0 ? '-' : '+',
           fabs(m->coeficientes[k]), k);
  }

  printf("\n\n  %-10s | %-13s | %-13s | %s\n", "x", "P(x)", "f(x)",
         "|P(x)-f(x)|");
  printf("  -----------|---------------|---------------|------------\n");

  for (int i = 0; i <= amostras; i++) {
    double x = a + (b - a) * i / amostras;
    double p = avaliar_polinomio(m->coeficientes, m->grau, x);

    printf("  %-10.4f | %-13.8f | %-13.8f | %.3e\n", x, p, f(x),
           fabs(p - f(x)));
  }
}
