#include "./mecanismos.cpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

double atualiza_celula(double to, double from, double multiplicador) {
  return to - from * multiplicador;
}

namespace eliminacao_gauss {

void pivoteamento(Matriz &A, Vetor &b, size_t i) {
  size_t n = b.size();
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
}

void atualiza_linha(Matriz &A, Vetor &b, size_t from, size_t to,
                    double multiplicador) {
  for (size_t i = 0; i < b.size(); i++) {
    A[to][i] = atualiza_celula(A[to][i], A[from][i], multiplicador);
  }

  b[to] = atualiza_celula(b[to], b[from], multiplicador);
}

void escalonamento(Matriz &A, Vetor &b) {
  size_t n = b.size();

  for (size_t i = 0; i < n - 1; i++) {
    pivoteamento(A, b, i);
    double pivo = A[i][i];

    for (size_t j = i + 1; j < n; j++) {
      double multiplicador = A[j][i] / pivo;
      atualiza_linha(A, b, i, j, multiplicador);
    }
  }
}

Resultado metodo(Matriz &A, Vetor &b) {
  size_t n = b.size();

  escalonamento(A, b);

  return {retrosubstituicao(A, b), n - 1, Status::Convergiu};
}

} // namespace eliminacao_gauss

namespace fatoracao_lu {

void pivoteamento(Matriz &U, Matriz &L, Vetor &b, size_t i) {
  size_t n = b.size();
  size_t p = i;

  for (size_t k = i + 1; k < n; k++) {
    if (std::fabs(U[k][i]) > std::fabs(U[p][i])) {
      p = k;
    }
  }

  if (p != i) {
    std::swap(U[i], U[p]);

    // Só alterna o que já foi calculado.
    for (size_t k = 0; k < i; k++) {
      std::swap(L[i][k], L[p][k]);
    }
    std::swap(b[i], b[p]);
  }

  if (U[i][i] == 0.0) {
    throw std::runtime_error("Impossível de continuar, diagonal zerada.");
  }
}

void atualiza_linha(Matriz &A, size_t from, size_t to, double multiplicador) {
  for (size_t i = 0; i < A.size(); i++) {
    A[to][i] = atualiza_celula(A[to][i], A[from][i], multiplicador);
  }
}

void fatoracao(Matriz &L, Matriz &U, Vetor &b) {
  size_t n = b.size();

  for (size_t i = 0; i < n - 1; i++) {
    pivoteamento(U, L, b, i);
    double pivo = U[i][i];

    for (size_t j = i + 1; j < n; j++) {
      double multiplicador = U[j][i] / pivo;
      L[j][i] = multiplicador;
      atualiza_linha(U, i, j, multiplicador);
    }
  }
}

void inicializar_diagonal_de_l(Matriz &L) {
  for (size_t i = 0; i < L.size(); i++) {
    L[i][i] = 1.0;
  }
}

Resultado metodo(Matriz &U, Vetor &b) {
  size_t n = b.size();

  Matriz L(n, std::vector<double>(n, 0.0));
  inicializar_diagonal_de_l(L);

  fatoracao(L, U, b);
  Vetor y = prosubstituicao(L, b);

  return {retrosubstituicao(U, y), n - 1, Status::Convergiu};
}

} // namespace fatoracao_lu

namespace gauss_jacobi {

Resultado metodo(const Matriz &A, const Vetor &b) {
  size_t n = b.size();

  Vetor x(n, 0.0);
  Vetor y(n, 0.0);

  for (size_t iteracao = 1; iteracao <= MAX_ITERACOES; iteracao++) {
    for (size_t i = 0; i < n; i++) {
      double soma = 0.0;

      for (size_t j = 0; j < n; j++) {
        if (i != j) {
          soma += A[i][j] * x[j];
        }
      }

      y[i] = (b[i] - soma) / A[i][i];
    }

    const Status status = criterio_parada(x, y);
    x = y;

    if (status != Status::Continuar) {
      return {x, iteracao, status};
    }
  }

  return {x, MAX_ITERACOES, Status::MaxIteracoes};
}

} // namespace gauss_jacobi

namespace gauss_seidel {

Resultado metodo(const Matriz &A, const Vetor &b) {
  size_t n = b.size();

  Vetor x(n, 0.0);

  for (size_t iteracao = 1; iteracao <= MAX_ITERACOES; iteracao++) {
    const Vetor anterior = x;

    for (size_t i = 0; i < n; i++) {
      double soma = 0.0;

      for (size_t j = 0; j < n; j++) {
        if (i != j) {
          soma += A[i][j] * x[j];
        }
      }

      x[i] = (b[i] - soma) / A[i][i];
    }

    const Status status = criterio_parada(anterior, x);

    if (status != Status::Continuar) {
      return {x, iteracao, status};
    }
  }

  return {x, MAX_ITERACOES, Status::MaxIteracoes};
}

} // namespace gauss_seidel
