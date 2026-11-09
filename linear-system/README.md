# nucalc — Sistemas Lineares

Implementação em C++ de métodos de resolução de sistemas lineares `Ax = b`.

Foram utilizadas matrizes do MatrixMarket do tipo real e simétricas para os testes.

## Pré requisitos

- Compilador c++
- Baixar as matrizes em `data/matrizes/matrix.mtx`

## Compilar

```sh
g++ -O3 src/main.cpp -o linear-system
g++ -O3 src/gerar_b.cpp -o gerar-b
```

## Gerar o vetor b

```sh
./gerar-b data/matrizes/foo.mtx
```

Gera `data/matrizes/foo.b` com valores uniformes em `[-50, 50]`.

## Resolver

```sh
./linear-system data/matrizes/foo.mtx data/matrizes/foo.b <metodo>
```

O programa imprime tempo, iterações, resíduo e convergência, e acrescenta uma
linha em `metricas.csv`.

## Estrutura

```
include/io.hpp        struct Metricas e declarações de I/O
src/main.cpp      resíduo e main
src/io.cpp        ler_matrix, ler_b, salvar_b, salvar_metricas
src/metodos.cpp   metodo1..metodo4 (implementar aqui)
src/gerar_b.cpp   gerador do vetor b
data/             matrizes .mtx e vetores .b
```
