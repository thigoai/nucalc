#include "io.cpp"
#include "metodos.cpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <exception>
#include <iostream>
#include <string>

using namespace std;

double calcular_residuo(const Matriz &A, const Vetor &b, const Vetor &x) {
  const int n = static_cast<int>(A.size());
  double maior = 0.0;

  for (int i = 0; i < n; ++i) {
    double soma = 0.0;

    for (int j = 0; j < n; ++j) {
      soma += A[i][j] * x[j];
    }

    maior = max(maior, fabs(soma - b[i]));
  }

  return maior;
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cerr << "uso: " << argv[0] << " <matriz.mtx> <vetor.b> <metodo>\n";
    return 1;
  }

  const string arquivo_mtx = argv[1];
  const string arquivo_b = argv[2];
  const string metodo = argv[3];

  Matriz A = ler_matrix(arquivo_mtx);
  Vetor b = ler_b(arquivo_b, static_cast<int>(A.size()));

  Resultado resultado;
  const auto inicio = chrono::steady_clock::now();

  try {
    if (metodo == "gauss_elim") {
      resultado = gauss_elim(A, b);
    } else if (metodo == "lu_factor") {
      resultado = lu_factor(A, b);
    } else if (metodo == "gauss_jacobi") {
      resultado = gauss_jacobi(A, b);
    } else if (metodo == "gauss_seidel") {
      resultado = gauss_seidel(A, b);
    } else {
      cerr << "metodo invalido: " << metodo << '\n';
      return 1;
    }
  } catch (const exception &erro) {
    cerr << "erro: " << erro.what() << '\n';
    return 1;
  }

  const auto fim = chrono::steady_clock::now();
  const double tempo = chrono::duration<double, milli>(fim - inicio).count();
  const double residuo = calcular_residuo(A, b, resultado.x);

  Metricas m;
  m.arquivo_mtx = arquivo_mtx;
  m.arquivo_b = arquivo_b;
  m.metodo = metodo;
  m.tempo = tempo;
  m.iteracoes = resultado.iteracoes;
  m.residuo = residuo;
  m.convergiu = residuo <= TOLERANCIA;

  salvar_metricas(m);

  cout << "n: " << A.size() << '\n';
  cout << "metodo: " << metodo << '\n';
  cout << "tempo: " << tempo << " ms\n";
  cout << "iteracoes: " << resultado.iteracoes << '\n';
  cout << "residuo: " << residuo << '\n';
  cout << "convergiu: " << (m.convergiu ? "sim" : "nao") << '\n';

  return 0;
}
