#include "funcoes.c"
#include "metrica.c"
#include "raizes.c"
#include <stdio.h>

int main() {
  FILE *csv = fopen("metricas.csv", "w");
  if (!csv) {
    perror("Erro ao criar arquivo CSV");
    return 1;
  }

  salvar_csv_cabecalho(csv);

  for (int i = 0; i < num_funcoes; i++) {
    function f = get_function(funcoes[i]);
    function fi = get_fi_function(funcoes[i]);
    struct Raizes rs = isolar_raizes(-1000, 1000, 0.1, f);

    printf("Funcao %d: encontrou %d raizes\n", i, rs.size / 2);

    for (int j = 0; j < num_metodos; j++) {
      MetodoNumerico metodo = metodos[j];

      for (int l = 0; l < rs.size; l += 2) {
        int id_raiz = l;
        double a = rs.arr[l];
        double b = rs.arr[l + 1];

        for (int k = 0; k < 30; k++) {
          struct Metricas m = executar_metodo(metodo, f, fi, a, b, i, j);
          salvar_metrica_csv(csv, i, j, id_raiz, k, a, b, m);
        }
      }
    }
  }

  fclose(csv);
  printf("Métricas salvas em metricas.csv com sucesso.\n");
  return 0;
}
