#include "../include/metrica.h"
#include "../include/raizes.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

struct Metricas executar_metodo(MetodoNumerico metodo, function f, function fi,
                                double a, double b, int id_func,
                                int id_metodo) {
  struct timespec inicio, fim;

  // Marca o tempo inicial
  clock_gettime(CLOCK_MONOTONIC, &inicio);

  // Executa o método numérico
  RetornoMetodo r = metodo(a, b, f, fi);
  double raiz = r.raiz;
  int iteracoes = r.iteracoes;

  // Marca o tempo final
  clock_gettime(CLOCK_MONOTONIC, &fim);

  // Calcula tempo decorrido em segundos
  double tempo =
      (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

  // Verifica validade numérica
  bool convergiu =
      !isnan(raiz) && !isinf(raiz) && fabs(f(raiz)) <= (EPSILON * 10.0);

  return (struct Metricas){.tempo = tempo,
                           .id = id_metodo,
                           .iteracoes = iteracoes,
                           .finish = convergiu,
                           .raiz = raiz};
}

void salvar_csv_cabecalho(FILE *fp) {
  if (!fp)
    return;
  fprintf(
      fp,
      "id_funcao,id_metodo,id_raiz,repeticao,a,b,tempo,iteracoes,convergiu\n");
}

void salvar_metrica_csv(FILE *fp, int id_func, int id_metodo, int id_raiz,
                        int repeticao, double a, double b, struct Metricas m) {
  if (!fp)
    return;
  fprintf(fp, "%d,%d,%d,%d,%.6f,%.6f,%.8f,%d,%d\n", id_func, id_metodo, id_raiz,
          repeticao, a, b, m.tempo, m.iteracoes, m.finish ? 1 : 0);
}
