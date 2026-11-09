#include "io.cpp"

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  if (argc != 3) {
    cerr << "uso: " << argv[0] << " <matriz.mtx> <saida.b>\n";
    return 1;
  }

  const string mtx = argv[1];
  const string saida_b = argv[2];

  ifstream arquivo(mtx);
  if (!arquivo) {
    cerr << "erro ao abrir " << mtx << '\n';
    return 1;
  }

  string linha;
  getline(arquivo, linha); // descarta o header

  int n = 0;

  while (getline(arquivo, linha)) {
    if (linha.empty() || linha[0] == '%') {
      continue;
    }

    istringstream dimensoes(linha);
    dimensoes >> n;
    break;
  }

  vector<double> b(n);
  mt19937_64 gerador(42);
  uniform_real_distribution<double> distribuicao(-50.0, 50.0);

  for (double &valor : b) {
    valor = distribuicao(gerador);
  }

  salvar_b(saida_b, b);

  cout << "b gerado: " << saida_b << " (n=" << n << ")\n";
  return 0;
}
