#include "../include/io.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<double>> ler_matrix(const string &nome) {
  ifstream arquivo(nome);
  if (!arquivo) {
    cerr << "erro ao abrir " << nome << '\n';
    exit(1);
  }

  string linha;
  getline(arquivo, linha); // descarta o header

  int n = 0;
  int m = 0;
  int nnz = 0;

  while (getline(arquivo, linha)) {
    if (linha.empty() || linha[0] == '%') {
      continue;
    }

    istringstream dimensoes(linha);
    dimensoes >> n >> m >> nnz;
    (void)m;
    break;
  }

  vector<vector<double>> A(n, vector<double>(n, 0.0));

  for (int k = 0; k < nnz; ++k) {
    int i = 0;
    int j = 0;
    double valor = 0.0;

    arquivo >> i >> j >> valor;
    A[i - 1][j - 1] += valor;

    if (i != j) {
      A[j - 1][i - 1] += valor;
    }
  }

  return A;
}

vector<double> ler_b(const string &nome, int n) {
  ifstream arquivo(nome);
  if (!arquivo) {
    cerr << "erro ao abrir " << nome << '\n';
    exit(1);
  }

  int n_arquivo = 0;
  arquivo >> n_arquivo;
  (void)n_arquivo;

  vector<double> b(n);
  for (double &valor : b) {
    arquivo >> valor;
  }

  return b;
}

void salvar_b(const string &nome, const vector<double> &b) {
  ofstream arquivo(nome);
  if (!arquivo) {
    cerr << "erro ao criar " << nome << '\n';
    exit(1);
  }

  arquivo << b.size() << '\n';
  arquivo << setprecision(17);

  for (double valor : b) {
    arquivo << valor << '\n';
  }
}

void salvar_metricas(const Metricas &m) {
  ifstream teste("metricas.csv");
  const bool novo = !teste.good() || teste.peek() == EOF;

  ofstream csv("metricas.csv", ios::app);
  if (novo) {
    csv << "arquivo_mtx,arquivo_b,metodo,tempo,iteracoes,residuo,convergiu\n";
  }

  csv << m.arquivo_mtx << ',' << m.arquivo_b << ',' << m.metodo << ','
      << setprecision(10) << m.tempo << ',' << m.iteracoes << ',' << m.residuo
      << ',' << (m.convergiu ? 1 : 0) << '\n';
}
