#include "../include/model.hpp"
#include <cmath>

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
