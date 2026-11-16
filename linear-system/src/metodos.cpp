#include "./mecanismos.cpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

double atualiza_celula(double to, double from, double multiplicador) {
  return to - from * multiplicador;
}

namespace eliminacao_gauss {

/*
 * Pseudocódigo — Pivoteamento parcial
 *
 * Entrada: A (n×n), b (n), i (etapa atual)
 * Saída:   A e b com a linha de maior |A[k][i]| na posição i
 *
 * p ← i
 * para k = i + 1 até n − 1:
 *     se |A[k][i]| > |A[p][i]|: p ← k
 * se p ≠ i:
 *     troca A[i] ↔ A[p]
 *     troca b[i] ↔ b[p]
 * se A[i][i] = 0: erro "diagonal zerada"
 */
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

/*
 * Pseudocódigo — Eliminação de Gauss
 *
 * Entrada: A (n×n), b (n)
 * Saída:   x (solução de A x = b), iterações, Status
 *
 * para i = 0 até n − 2:                      // etapas de eliminação
 *     pivoteamento(A, b, i)                  // maior |A[k][i]| vai para a
 * linha i pivo ← A[i][i] para j = i + 1 até n − 1: m ← A[j][i] / pivo A[j] ←
 * A[j] − m · A[i] b[j] ← b[j] − m · b[i]
 *
 * x ← retrosubstituicao(A, b)                // A agora é triangular superior
 * retorna x, n − 1, Convergiu
 */
Resultado metodo(Matriz &A, Vetor &b) {
  size_t n = b.size();

  escalonamento(A, b);

  return {retrosubstituicao(A, b), n - 1, Status::Convergiu};
}

} // namespace eliminacao_gauss

namespace fatoracao_lu {

/*
 * Pseudocódigo — Pivoteamento parcial na fatoração LU
 *
 * Entrada: U (n×n), L (n×n), b (n), i (etapa atual)
 * Saída:   linhas de U, de L já calculadas e b permutadas
 *
 * p ← i
 * para k = i + 1 até n − 1:
 *     se |U[k][i]| > |U[p][i]|: p ← k
 * se p ≠ i:
 *     troca U[i] ↔ U[p]
 *     troca L[i][0..i−1] ↔ L[p][0..i−1]      // só o que já foi calculado
 *     troca b[i] ↔ b[p]
 * se U[i][i] = 0: erro "diagonal zerada"
 */
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

/*
 * Pseudocódigo — Fatoração LU com pivoteamento parcial
 *
 * Entrada: A (n×n), b (n)
 * Saída:   x (solução de A x = b), iterações, Status
 *
 * U ← A; L ← identidade (n×n)
 * para i = 0 até n − 2:
 *     pivoteamento(U, L, b, i)
 *     pivo ← U[i][i]
 *     para j = i + 1 até n − 1:
 *         m ← U[j][i] / pivo
 *         L[j][i] ← m
 *         U[j] ← U[j] − m · U[i]
 *
 * y ← prosubstituicao(L, b)                  // resolve L y = b
 * x ← retrosubstituicao(U, y)                // resolve U x = y
 * retorna x, n − 1, Convergiu
 */
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

/*
 * Pseudocódigo — Gauss-Jacobi
 *
 * Entrada: A (n×n), b (n)
 * Saída:   x (aproximação), iterações, Status
 *
 * x ← 0; y ← 0
 * para k = 1 até MAX_ITERACOES:
 *     para i = 0 até n − 1:
 *         s ← Σ_{j≠i} A[i][j] · x[j]         // usa só o iterado anterior x
 *         y[i] ← (b[i] − s) / A[i][i]
 *
 *     status ← criterio_parada(x, y)         // ||y − x|| absoluta e relativa
 *     x ← y
 *     se status ≠ Continuar: retorna x, k, status
 *
 * retorna x, MAX_ITERACOES, MaxIteracoes
 */
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

/*
 * Pseudocódigo — Gauss-Seidel
 *
 * Entrada: A (n×n), b (n)
 * Saída:   x (aproximação), iterações, Status
 *
 * x ← 0
 * para k = 1 até MAX_ITERACOES:
 *     anterior ← x
 *     para i = 0 até n − 1:
 *         s ← Σ_{j≠i} A[i][j] · x[j]         // usa valores já atualizados
 *         x[i] ← (b[i] − s) / A[i][i]
 *
 *     status ← criterio_parada(anterior, x)  // ||x − anterior|| absoluta e
 *                                            // relativa se status ≠ Continuar:
 *                                            // retorna x, k, status
 *
 * retorna x, MAX_ITERACOES, MaxIteracoes
 */
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
