#include "../include/model.hpp"
#include <algorithm>
#include <cmath>

/*
 * Pseudocódigo — Retrosubstituição (resolve U x = b)
 *
 * Entrada: A (triangular superior, n×n), b (n)
 * Saída:   x (n)
 *
 * x[n − 1] ← b[n − 1] / A[n − 1][n − 1]
 * para i = n − 2 até 0 (decrementando):
 *     s ← Σ_{j=i+1}^{n−1} A[i][j] · x[j]
 *     x[i] ← (b[i] − s) / A[i][i]
 * retorna x
 */
Vetor retrosubstituicao(const Matriz &A, const Vetor &b) {
  size_t n = b.size();
  Vetor x(n);

  x[n - 1] = b[n - 1] / A[n - 1][n - 1];

  for (size_t i = n - 1; i-- > 0;) {
    double somatorio = 0.0;

    for (size_t j = i + 1; j < n; j++) {
      somatorio += A[i][j] * x[j];
    }

    x[i] = (b[i] - somatorio) / A[i][i];
  }

  return x;
}

/*
 * Pseudocódigo — Prosubstituição (resolve L y = b)
 *
 * Entrada: L (triangular inferior, n×n), b (n)
 * Saída:   y (n)
 *
 * para i = 0 até n − 1:
 *     s ← Σ_{j=0}^{i−1} L[i][j] · y[j]
 *     y[i] ← (b[i] − s) / L[i][i]
 * retorna y
 */
Vetor prosubstituicao(const Matriz &L, const Vetor &b) {
  size_t n = b.size();
  Vetor y(n);

  for (size_t i = 0; i < n; i++) {
    double soma = 0.0;

    for (size_t j = 0; j < i; j++) {
      soma += L[i][j] * y[j];
    }

    y[i] = (b[i] - soma) / L[i][i];
  }

  return y;
}

/*
 * Pseudocódigo — Norma infinito
 *
 * Entrada: v (n)
 * Saída:   ‖v‖∞ = max_i |v[i]|
 *
 * maior ← 0
 * para cada valor em v:
 *     se |valor| > maior: maior ← |valor|
 * retorna maior
 */
double norma_infinito(const Vetor &v) {
  double maior = 0.0;

  for (double valor : v) {
    const double absoluto = std::fabs(valor);
    if (!(absoluto <= maior)) { // NaN se propaga
      maior = absoluto;
    }
  }

  return maior;
}

/*
 * Pseudocódigo — Resíduo r = b − A x
 *
 * Entrada: A (n×n), b (n), x (n)
 * Saída:   r (n)
 *
 * para i = 0 até n − 1:
 *     s ← Σ_j A[i][j] · x[j]
 *     r[i] ← b[i] − s
 * retorna r
 */
Vetor calcular_residuo(const Matriz &A, const Vetor &b, const Vetor &x) {
  size_t n = b.size();
  Vetor residuo(n);

  for (size_t i = 0; i < n; i++) {
    double soma = 0.0;

    for (size_t j = 0; j < n; j++) {
      soma += A[i][j] * x[j];
    }

    residuo[i] = b[i] - soma;
  }

  return residuo;
}

/*
 * Pseudocódigo — Critério de parada
 *
 * Entrada: anterior (n), x (n), TOLERANCIA
 * Saída:   Status
 *
 * delta ← 0; norma_anterior ← 0; norma_x ← 0
 * para i = 0 até n − 1:
 *     se x[i] não é finito: retorna Divergiu
 *     delta ← max(delta, |x[i] − anterior[i]|)
 *     norma_anterior ← max(norma_anterior, |anterior[i]|)
 *     norma_x ← max(norma_x, |x[i]|)
 *
 * escala ← max(norma_anterior, norma_x)
 * absoluta ← delta < TOLERANCIA
 * relativa ← escala > 0 e delta / escala < TOLERANCIA
 * retorna Convergiu se absoluta e relativa, senão Continuar
 */
Status criterio_parada(const Vetor &anterior, const Vetor &x) {
  double delta = 0.0;
  double norma_anterior = 0.0;
  double norma_x = 0.0;

  for (size_t i = 0; i < x.size(); i++) {
    if (!std::isfinite(x[i])) {
      return Status::Divergiu;
    }

    delta = std::max(delta, std::fabs(x[i] - anterior[i]));
    norma_anterior = std::max(norma_anterior, std::fabs(anterior[i]));
    norma_x = std::max(norma_x, std::fabs(x[i]));
  }

  const double escala = std::max(norma_anterior, norma_x);
  const bool absoluta = delta < TOLERANCIA;
  const bool relativa = escala > 0.0 && delta / escala < TOLERANCIA;

  return (absoluta && relativa) ? Status::Convergiu : Status::Continuar;
}
