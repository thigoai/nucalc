#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../algoritmos-de-interpolacao/linear-system.c"
#include "funcoes.c"
#include "interpolacao.c"
#include "metrica.c"

// Função para o usuário escolher qual resolvedor de sistema linear usar
int escolher_resolvedor(int argc, char **argv) {
  if (argc > 1) {
    char *fim = NULL;
    long opcao = strtol(argv[1], &fim, 10);
    if (fim == argv[1] || *fim != '\0' || opcao < 0 ||
        opcao > num_metodos_sistema_linear) {
      return -2;
    }
    return (int)opcao - 1;
  }

  printf("Resolvedores de sistema linear disponiveis:\n");
  for (int i = 0; i < num_metodos_sistema_linear; i++) {
    printf("  %d - %s\n", i + 1, nomes_sistema_linear[i]);
  }
  printf("  0 - todos (comparacao)\n\n> ");

  int opcao;
  if (scanf("%d", &opcao) != 1 || opcao < 0 ||
      opcao > num_metodos_sistema_linear) {
    return -2;
  }
  return opcao - 1;
}

void imprimir_linha_metrica(int indice, struct Metricas met) {
  const char *teste =
      !met.convergiu ? "SEM CONVERGENCIA" : (met.finish ? "OK" : "FALHOU");

  printf("  %-20s | %10.3f | ", nomes_sistema_linear[indice], met.tempo * 1e6);

  // Caso haja divergência, imprime - 
  if (isfinite(met.erro)) {
    printf("%10.3e | %s\n", met.erro, teste);
  } else {
    printf("%10s | %s\n", "-", teste);
  }
}

int main(int argc, char **argv) {
  /*
    2.3. Utilizando a interpolação via solução do sistema linear,  interpole a função f(x) = 1/(1+25x2), em 
    pontos igualmente espaçados entre x=0 e x=4, com (a) n= 4; (b) n = 10; (c) n = 15. Compare 
    os resultados obtidos com a função original. (obs. n é o grau do polinômio interpolador).
  */

  // Definindo critérios de interpolação
  const int graus[] = {4, 10, 15};
  const int num_graus = sizeof(graus) / sizeof(graus[0]);

  const double a = 0.0;
  const double b = 4.0;
  function f = get_function(F2); // f2(x) = 1 / (1 + 25x^2)

  // Usuário escolhe qual sistema linear usar na interpolação de sistema linear 
  int escolha = escolher_resolvedor(argc, argv);
  if (escolha < -1 || escolha >= num_metodos_sistema_linear) {
    fprintf(stderr, "opcao invalida; use 0..%d\n", num_metodos_sistema_linear);
    return 1;
  }

  // Imprime a função que está sendo interpolada e como está sendo o teste de erro
  printf("\nInterpolacao de f(x) = 1 / (1 + 25x^2) [%.1f, %.1f]\n", a, b);
  printf("Teste: max|P(x_i) - y_i| <= %.0e nos pontos tabelados\n\n",
         TOLERANCIA);

  // Executa e imprime os métodos 
  printf("INTEPORPOLANDO COM O SISTEMA LINEAR =================================\n\n"); 
  for (int g = 0; g < num_graus; g++) {
    int grau = graus[g];

    printf("--- Grau n = %d (%d pontos) ---\n", grau, grau + 1);

    if (escolha == -1) {
      printf("  %-20s | %10s | %10s | %s\n", "Metodo", "Tempo (us)",
             "Erro nos", "Teste");
      printf("  ---------------------|------------|------------|------------"
             "----\n");

      for (int r = 0; r < num_metodos_sistema_linear; r++) {
        struct Metricas met = executar_interpolacao(
            interpolacao_sistema_linear, metodos_sistema_linear[r], f, a, b,
            grau);
        imprimir_linha_metrica(r, met);
      }

      printf("\n");
      continue;
    }

    struct Metricas met = executar_interpolacao(
        interpolacao_sistema_linear, metodos_sistema_linear[escolha], f, a, b,
        grau);

    printf("  Metodo: %s\n", nomes_sistema_linear[escolha]);
    printf("  Tempo:  %.3f us\n", met.tempo * 1e6);
    if (met.convergiu) {
      printf("  Erro:   %.3e\n", met.erro);
    }
    printf("  Teste:  %s\n\n",
           !met.convergiu ? "SEM CONVERGENCIA"
                          : (met.finish ? "OK" : "FALHOU"));

    imprimir_resposta(a, b, 10, f, &met);
    printf("\n");
  }

  return 0;
}