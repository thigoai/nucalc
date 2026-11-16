#pragma once

#include <cstddef>
#include <vector>

constexpr double TOLERANCIA = 1e-6;
constexpr size_t MAX_ITERACOES = 10000;

using Matriz = std::vector<std::vector<double>>;
using Vetor = std::vector<double>;

enum class Status { Continuar, Convergiu, MaxIteracoes, Divergiu };

inline const char *nome_status(Status status) {
  switch (status) {
  case Status::Continuar:
    return "continuar";
  case Status::Convergiu:
    return "convergiu";
  case Status::MaxIteracoes:
    return "max_iteracoes";
  case Status::Divergiu:
    return "divergiu";
  }
  return "desconhecido";
}

struct Resultado {
  Vetor x;
  size_t iteracoes = 0;
  Status status = Status::Convergiu;
};
