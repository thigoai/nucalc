#include "../include/model.hpp"
#include <algorithm>
#include <cmath>

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

// Vetor residuo r = b - A*x.
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

// Critério de parada: distância absoluta E distância relativa abaixo da
// tolerância.
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
