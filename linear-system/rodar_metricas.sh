CXX="${CXX:-g++}"
CFLAGS=(-std=c++20 -O3 -Wall -Wextra)

matrizes=(bcsstk22 bcsstk23 bcsstk24)
metodos=(gauss_elim lu_factor gauss_jacobi gauss_seidel)

echo "compilando..."
g++ -O3 src/main.cpp -o linear-system 
g++ -O3 src/gerar_b.cpp -o gerar-b 

rm -f metricas.csv

for matriz in "${matrizes[@]}"; do
  mtx="data/matrizes/${matriz}.mtx"
  vetor="data/b/${matriz}.b"

  if [[ ! -f "$mtx" ]]; then
    echo "matriz ausente: $mtx" >&2
    continue
  fi

  if [[ ! -f "$vetor" ]]; then
    echo "gerando $vetor..."
    ./gerar-b "$mtx" "$vetor" || continue
  fi

  for metodo in "${metodos[@]}"; do
    echo "== ${matriz} / ${metodo}"
    ./linear-system "$mtx" "$vetor" "$metodo" 
  done
done

echo
echo "=== metricas.csv ==="
cat metricas.csv
