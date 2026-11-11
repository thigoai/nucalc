#include "./mecanismos.cpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

double atualiza_celula(double to, double from, double multiplicador) {
  return to - from * multiplicador;
}

namespace eliminacao_gauss {

void pivoteamento(Matriz &A, Vetor &b, size_t i) {
  size_t n = b.size();

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
}

void atualiza_linha(Matriz &A, Vetor &b, size_t from, size_t to, size_t &count,
                    double multiplicador) {
  for (size_t i = 0; i < b.size(); i++) {
    count++;
    A[to][i] = atualiza_celula(A[to][i], A[from][i], multiplicador);
  }

  count++;
  b[to] = atualiza_celula(b[to], b[from], multiplicador);
}

void escalonamento(Matriz &A, Vetor &b, size_t &count) {
  size_t n = b.size();

  for (size_t i = 0; i < n - 1; i++) {
    pivoteamento(A, b, i);
    double pivo = A[i][i];

    for (int j = i + 1; j < n; j++) {
      double multiplicador = A[j][i] / pivo;

      atualiza_linha(A, b, i, j, count, multiplicador);
    }
  }
}

Resultado metodo(Matriz &A, Vetor &b) {
  size_t n = b.size();
  size_t count = 0;

  escalonamento(A, b, count);

  Vetor x = retrosubstituicao(A, b, count);

  return Resultado{
      .x = x,
      .iteracoes = count,
  };
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

void atualiza_linha(Matriz &A, size_t from, size_t to, size_t &count,
                    double multiplicador) {
  count += A.size();
  for (size_t i = 0; i < A.size(); i++) {
    A[to][i] = atualiza_celula(A[to][i], A[from][i], multiplicador);
  }
}

void fatoracao(Matriz &L, Matriz &U, Vetor &b, size_t &count) {
  size_t n = b.size();

  for (size_t i = 0; i < n - 1; i++) {
    pivoteamento(U, L, b, i);
    double pivo = U[i][i];
    for (int j = i + 1; j < n; j++) {
      double multiplicador = U[j][i] / pivo;

      L[j][i] = multiplicador;

      atualiza_linha(U, i, j, count, multiplicador);
    }
  }
}

void inicializar_diagonal_de_l(Matriz &L) {
  size_t n = L.size();
  for (size_t i = 0; i < n; i++) {
    L[i][i] = 1.0;
  }
}

Resultado metodo(Matriz &U, Vetor &b) {
  size_t n = b.size();
  size_t count = 0;

  Matriz L(n, std::vector<double>(n, 0.0));
  inicializar_diagonal_de_l(L);

  fatoracao(L, U, b, count);
  Vetor y = prosubstituicao(L, b, count);
  Vetor x = retrosubstituicao(U, y, count);

  return Resultado{
      .x = x,
      .iteracoes = count,
  };
}

} // namespace fatoracao_lu

namespace gauss_jacobi {

Resultado metodo(const Matriz &A, const Vetor &b) {
  size_t n = b.size();

  Vetor x = std::vector<double>(n, 0);
  Vetor y = std::vector<double>(n, 10);

  size_t contador = 0;

  while (true) {
    contador++;

    for (size_t i = 0; i < n; i++) {
      y[i] = 0;
      for (size_t j = 0; j < n; j++) {
        if (i != j) {
          y[i] += A[i][j] * x[j];
        }
      }

      y[i] = (b[i] - y[i]) / A[i][i];
    }

    bool convergiu =
        distancia_relativa(x, y, 1e-6) || distancia_absoluta(x, y, 1e-6);

    x = y;

    if (convergiu) {
      break;
    }
  }

  return Resultado{.x = x, .iteracoes = contador};
}
} // namespace gauss_jacobi

Resultado gauss_seidel(const Matriz &A, const Vetor &b) {
  (void)A;
  (void)b;
  throw std::runtime_error("gauss_seidel nao implementado");
}
