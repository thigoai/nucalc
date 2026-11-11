#include "../include/model.hpp"
#include <cmath>
#include <cstdlib>

Vetor retrosubstituicao(const Matriz &A, const Vetor &b, size_t &count) {
  size_t n = b.size();

  Vetor x(n);

  count++;
  x[n - 1] = b[n - 1] / A[n - 1][n - 1];

  for (size_t i = n - 1; i-- > 0;) {
    double somatorio = 0.0;

    for (size_t j = i + 1; j < n; j++) {
      count++;
      somatorio += A[i][j] * x[j];
    }

    count++;
    x[i] = (b[i] - somatorio) / A[i][i];
  }

  return x;
}

Vetor prosubstituicao(const Matriz &L, const Vetor &b, size_t &count) {
  size_t n = b.size();
  Vetor y(n);

  for (size_t i = 0; i < n; i++) {
    double soma = 0.0;

    for (size_t j = 0; j < i; j++) {
      count++;
      soma += L[i][j] * y[j];
    }

    count++;
    y[i] = (b[i] - soma) / L[i][i];
  }

  return y;
}
double calcular_residuo(const Matriz &A, const Vetor &b, const Vetor &x) {
  const int n = static_cast<int>(A.size());
  double maior = 0.0;

  for (int i = 0; i < n; ++i) {
    double soma = 0.0;

    for (int j = 0; j < n; ++j) {
      soma += A[i][j] * x[j];
    }

    maior = std::max(maior, std::fabs(soma - b[i]));
  }

  return maior;
}

bool distancia_relativa(const Vetor &x, const Vetor &xx, double EPSILON) {
  double max_delta = 0;
  double max_xx = 0;

  for (size_t i = 0; i < x.size(); i++) {
    double delta = std::abs(xx[i] - x[i]);
    if (delta > max_delta) {
      max_delta = delta;
    }

    double abs_xx = std::abs(xx[i]);

    if (xx[i] > max_xx) {
      max_xx = xx[i];
    }
  }

  if (max_xx == 0)
    return max_delta < EPSILON;

  return max_delta / max_xx < EPSILON;
}

bool distancia_absoluta(const Vetor &x, const Vetor &xx, double EPSILON) {
  double max_delta = 0;

  for (size_t i = 0; i < x.size(); i++) {
    double delta = std::abs(xx[i] - x[i]);
    if (delta > max_delta) {
      max_delta = delta;
    }
  }

  return max_delta < EPSILON;
}
