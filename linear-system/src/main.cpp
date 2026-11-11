#include "io.cpp"
#include "metodos.cpp"
#include <chrono>
#include <exception>
#include <iostream>
#include <string>

using namespace std;

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

  Matriz A_original = A;
  Vetor b_original = b;

  Resultado resultado;
  const auto inicio = chrono::steady_clock::now();

  try {
    if (metodo == "gauss_elim") {
      resultado = eliminacao_gauss::metodo(A, b);
    } else if (metodo == "lu_factor") {
      resultado = fatoracao_lu::metodo(A, b);
    } else if (metodo == "gauss_jacobi") {
      resultado = gauss_jacobi::metodo(A, b);
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
  const double residuo = calcular_residuo(A_original, b_original, resultado.x);

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
