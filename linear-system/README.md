# nucalc — Sistemas Lineares

Implementação em C++ de métodos de resolução de sistemas lineares `Ax = b`.

Foram utilizadas matrizes do MatrixMarket do tipo real e simétricas para os testes.

## Pré requisitos

- Compilador c++
- Baixar as matrizes em `data/matrizes/matrix.mtx`

## Compilar

```sh
g++ -std=c++20 -O3 src/main.cpp -o linear-system
g++ -std=c++20 -O3 src/gerar_b.cpp -o gerar-b
```

## Gerar o vetor b

```sh
./gerar-b data/matrizes/foo.mtx data/b/foo.b
```

Gera `data/b/foo.b` com valores uniformes em `[-50, 50]`.

## Resolver

```sh
./linear-system data/matrizes/foo.mtx data/b/foo.b <metodo>
```

O programa imprime tempo, iterações, resíduo, convergência, status e o vetor
solução, e acrescenta uma linha em `metricas.csv`.

Para rodar todas as combinações matriz × método e reconstruir o `metricas.csv`:

```sh
./rodar_metricas.sh
```

## Estrutura

```
include/model.hpp     tipos, tolerâncias, Status e Resultado
include/io.hpp        struct Metricas e declarações de I/O
src/main.cpp          CLI, resíduo final e gravação das métricas
src/io.cpp            ler_matrix, ler_b, salvar_b, salvar_metricas
src/mecanismos.cpp    substituições, normas, resíduo e critério de parada
src/metodos.cpp       metodo1..metodo4 (implementar aqui)
src/gerar_b.cpp       gerador do vetor b
rodar_metricas.sh     execução em lote e reconstrução do metricas.csv
data/                 matrizes .mtx e vetores .b
```

## 1.0 Ambiente computacional utilizado para os testes

- Processador: Ryzen 7 5700g (8 cores/16 threads)
- Memória: 16Gb DDR4
- Sistema Operacional: Fedora 45

## 1.1 Métodos implementados

Dentro de `src/metodos.cpp` foram implementados os quatro métodos requisitados:

- Eliminação de Gauss
- Fatoração LU
- Método de Gauss Jacobi
- Método de Gauss Seidel

Para os últimos dois, o critério de parada usa as duas distâncias entre iterados
consecutivos: a absoluta `‖x⁽ᵏ⁾ − x⁽ᵏ⁻¹⁾‖∞` e a relativa
`‖x⁽ᵏ⁾ − x⁽ᵏ⁻¹⁾‖∞ / max(‖x⁽ᵏ⁾‖∞, ‖x⁽ᵏ⁻¹⁾‖∞)`. O método para quando **as duas**
ficam abaixo de 10⁻⁶, como pede o enunciado. A implementação está em
`criterio_parada`, em `src/mecanismos.cpp`.

O laço é limitado a `MAX_ITERACOES = 10⁴`, valores não finitos encerram a
execução como divergência e o `Status` registra o motivo da parada.

O vetor resíduo `r = b − Ax` é calculado ao final de cada execução por
`calcular_residuo` e resumido no `metricas.csv` pela norma `‖r‖∞`. Nos métodos
diretos, a coluna `iteracoes` registra o número de etapas de eliminação
(`n − 1`).

Colunas do `metricas.csv`:

- `n`: dimensão do sistema;
- `tempo_ms`: tempo do método em milissegundos;
- `iteracoes`: varreduras (iterativos) ou etapas de eliminação (diretos);
- `residuo`: `‖b − Ax‖∞`;
- `convergiu`: 1 quando o critério de parada foi atingido;
- `status`: `convergiu`, `max_iteracoes` ou `divergiu`.

## 1.2 Pseudocódigo

O pseudocódigo de cada algoritmo está definido como comentário acima do método, como pode ser observado em `src/metodos.cpp`. Alguns mecanismos importantes utilizados dentro dos métodos também têm pseudocódigo, como pode ser observado em `mecanismos.cpp`.

## 1.3 Matrizes do MatrixMarket

As matrizes foram baixadas e estão no repositório, em `data/matrizes/*.mtx`.

## 1.4 Leitura de dados

Para a leitura de dados, foi utilizado o deepseek para fazer um código que transforma o arquivo em uma matriz em memória. O código foi devidamente revisado pelos integrantes do grupo.

## 1.5 Vetor B

Para o vetor B, foi criado um binário específico que gera um vetor aleatorizado baseado na matriz passada como entrada, os valores são limitados aleatoriamente entre -50 e 50 e salvos em `data/b/*.b`.

## 1.6 ... Ué

## 1.7

Executando os quatro métodos com os mesmos parâmetros da seção 1.1, obtivemos:

| matriz | n | método | tempo (ms) | iterações | resíduo | status |
| :--- | ---: | :--- | ---: | ---: | ---: | :--- |
| bcsstk22 | 138 | gauss_elim | 0.38 | 137 | 1.09e-12 | convergiu |
| bcsstk22 | 138 | lu_factor | 0.44 | 137 | 1.66e-12 | convergiu |
| bcsstk22 | 138 | gauss_jacobi | 21.27 | 1763 | nan | divergiu |
| bcsstk22 | 138 | gauss_seidel | 54.71 | 4838 | 8.57e-03 | convergiu |
| bcsstk23 | 3134 | gauss_elim | 10845.88 | 3133 | 1.34e-05 | convergiu |
| bcsstk23 | 3134 | lu_factor | 10808.11 | 3133 | 1.16e-05 | convergiu |
| bcsstk23 | 3134 | gauss_jacobi | 3659.28 | 518 | nan | divergiu |
| bcsstk23 | 3134 | gauss_seidel | 7737.52 | 1067 | 9.03e+03 | convergiu |
| bcsstk24 | 3562 | gauss_elim | 17284.27 | 3561 | 2.51e-07 | convergiu |
| bcsstk24 | 3562 | lu_factor | 16230.35 | 3561 | 4.14e-07 | convergiu |
| bcsstk24 | 3562 | gauss_jacobi | 3593.93 | 390 | nan | divergiu |
| bcsstk24 | 3562 | gauss_seidel | 93213.98 | 10000 | 1.17e+04 | max_iteracoes |

Os métodos diretos (eliminação de Gauss e fatoração LU) convergiram nas três
matrizes. O método de Gauss-Jacobi divergiu nas três. O método de Gauss-Seidel
convergiu na `bcsstk22` e na `bcsstk23` e não atingiu o critério de parada na
`bcsstk24` dentro de 10⁴ iterações.
