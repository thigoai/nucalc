# Matrizes

Coloque aqui os três arquivos `.mtx` do Matrix Market.
Descompacte os `.mtx.gz` com `gunzip`.

| arquivo | n | entradas no .mtx | fonte |
|---------|---|------------------|-------|
| `bcsstk22.mtx` | 138 | 417 | https://math.nist.gov/MatrixMarket/data/Harwell-Boeing/bcsstruc3/bcsstk22.html |
| `bcsstk23.mtx` | 3134 | 24156 | https://math.nist.gov/MatrixMarket/data/Harwell-Boeing/bcsstruc3/bcsstk23.html |
| `bcsstk24.mtx` | 3562 | 81736 | https://math.nist.gov/MatrixMarket/data/Harwell-Boeing/bcsstruc3/bcsstk24.html |

Para gerar o vetor `b` de uma matriz, a partir de `linear-system/`:

```sh
./gerar-b data/matrizes/nome_da_matriz.mtx
```

Isso cria `data/matrizes/nome_da_matriz.b`.
