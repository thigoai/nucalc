#include <stdexcept>
#include <vector>

using Matriz = std::vector<std::vector<double>>;
using Vetor = std::vector<double>;

constexpr double TOLERANCIA = 1e-6;
constexpr int MAX_ITERACOES = 10000;

struct Resultado {
  Vetor x;
  int iteracoes = 0;
};

Resultado gauss_elim(const Matriz &A, const Vetor &b) {
  (void)A;
  (void)b;
  throw std::runtime_error("gauss_elim nao implementado");
}

Resultado lu_factor(const Matriz &A, const Vetor &b) {
  (void)A;
  (void)b;
  throw std::runtime_error("lu_factor nao implementado");
}

Resultado gauss_jacobi(const Matriz &A, const Vetor &b) {
  (void)A;
  (void)b;
  throw std::runtime_error("gauss_jacobi nao implementado");
}

Resultado gauss_seidel(const Matriz &A, const Vetor &b) {
  (void)A;
  (void)b;
  throw std::runtime_error("gauss_seidel nao implementado");
}
