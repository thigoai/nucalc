# nucalc

Trabalho da disciplina de **Cálculo Numérico** no DIMAP/UFRN.

Programa em C que compara métodos numéricos para encontrar raízes de funções,
medindo tempo de execução, número de iterações e taxa de convergência. Os
resultados são salvos em `metricas.csv` e analisados em um notebook Python.

## Métodos implementados

| id | Método        |
|----|---------------|
| 0  | Bisseção      |
| 1  | Newton        |
| 2  | Ponto Fixo    |
| 3  | Secante       |
| 4  | Falsa Posição |
| 5  | Híbrido       |

O método **Híbrido** (`metodo1`) faz algumas iterações de Ponto Fixo para
reduzir o intervalo e depois usa Bisseção para garantir a convergência.

## Funções analisadas

- `f1`: `2x⁴ + 4x³ + 3x² - 10x - 15`
- `f2`: `x⁵ - 2x⁴ - 9x³ + 22x² + 4x - 24`
- `f3`: `5x³ + x² - e^(1-2x) + cos(x) + 20`
- `f4`: `x·sen(x) + 4`

Para cada função, as raízes são isoladas no intervalo `[-1000, 1000]` com passo
`0.1`. Cada método roda **30 vezes** sobre cada raiz para permitir análise
estatística. A tolerância é `EPSILON = 1e-6`.

## Como compilar e executar

```sh
gcc src/main.c -O3 -lm
./a.out
```

Isso gera `metricas.csv` no diretório atual.

## Estrutura

```
include/   headers (funcoes, metodos, raizes, metrica)
src/       implementação em C
analise/   notebook Python (pandas/matplotlib/seaborn) para visualizar o CSV
```

## Análise dos resultados

O notebook `analise/analise.ipynb` lê o `metricas.csv` e gera tabelas e
gráficos comparando os métodos por tempo, iterações e convergência.

```sh
cd analise
uv sync
uv run jupyter notebook
```

## Colunas do CSV

`id_funcao, id_metodo, id_raiz, repeticao, a, b, tempo, iteracoes, convergiu`
