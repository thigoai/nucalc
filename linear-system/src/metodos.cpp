#include "./mecanismos.cpp"
#include <stdexcept>

Resultado gauss_elim(Matriz &A, Vetor &b) {
  size_t n = b.size();
  size_t count = 0;

  for (size_t i = 0; i < n - 1; i++) {
    double pivo = A[i][i];

    size_t p = i;

    for (size_t k = i + 1; k < n; k++) {
      if (std::fabs(A[k][i]) > std::fabs(A[p][i])) {
        p = k;
      }
    }

    if (p != i) {
      std::swap(A[i], A[p]);
      std::swap(b[i], b[p]);
    }

    if (A[i][i] == 0.0) {
      throw std::runtime_error("Impossível de continuar, diagonal zerada.");
    }

    for (int j = i + 1; j < n; j++) {
      double multiplicador = A[j][i] / pivo;

      auto line_update = [&multiplicador](double to, double from) {
        return to - from * multiplicador;
      };

      apply(A, b, i, j, count, line_update);
    }
  }

  Vetor x = retrosubstituicao(A, b, count);

  return Resultado{
      .x = x,
      .iteracoes = count,
  };
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
