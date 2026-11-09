#pragma once

#include <functional>
#include <vector>

constexpr double TOLERANCIA = 1e-6;
constexpr int MAX_ITERACOES = 10000;

using Matriz = std::vector<std::vector<double>>;
using Vetor = std::vector<double>;
using Transform = std::function<double(double, double)>;

struct Resultado {
  Vetor x;
  size_t iteracoes = 0;
};
