#ifndef METRICAS_H
#define METRICAS_H

#include "funcoes.h"
#include "metodos.h"
#include <stdbool.h>
#include <stdio.h>

struct Metricas {
  double tempo;
  int id;
  int iteracoes;
  bool finish;
  double raiz;
};

struct Metricas executar_metodo(MetodoNumerico metodo, function f, function fi,
                                double a, double b, int i, int j);

void salvar_csv_cabecalho(FILE *fp);

void salvar_metrica_csv(FILE *fp, int id_func, int id_metodo, int id_raiz,
                        int repeticao, double a, double b, struct Metricas m);

#endif
