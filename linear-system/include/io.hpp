#pragma once

#include <string>
#include <vector>

struct Metricas {
  std::string arquivo_mtx;
  std::string arquivo_b;
  std::string metodo;
  double tempo = 0.0;
  size_t iteracoes = 0;
  double residuo = 0.0;
  bool convergiu = false;
};

std::vector<std::vector<double>> ler_matrix(const std::string &nome);
std::vector<double> ler_b(const std::string &nome, int n);
void salvar_b(const std::string &nome, const std::vector<double> &b);
void salvar_metricas(const Metricas &m);
