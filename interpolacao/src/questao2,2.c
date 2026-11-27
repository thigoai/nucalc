#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../algoritmos-de-interpolacao/lagrange.c"
#include "../algoritmos-de-interpolacao/linear-system.c"
#include "../algoritmos-de-interpolacao/newton.c"
#include "funcoes.c"
#include "interpolacao.c"
#include "metrica.c"

// Função para o usuário escolher uma opção
// Serve para escolher o algoritmo de interpolação
// Serve para escolher diferentes métodos de resolução de sistema linear caso ele escolha a interpolação por sistema linear
int escolher_opcao(const char *titulo, const char *nomes[], int total, const char *arg) {
  if (arg != NULL) {
    char *fim = NULL;
    long opcao = strtol(arg, &fim, 10);
    if (fim == arg || *fim != '\0' || opcao < 0 || opcao > total) {
      return -2;
    }
    return (int)opcao - 1;
  }

  printf("%s\n", titulo);
  for (int i = 0; i < total; i++) {
    printf("  %d - %s\n", i + 1, nomes[i]);
  }
  printf("  0 - todos (comparacao)\n\n> ");

  int opcao;
  if (scanf("%d", &opcao) != 1 || opcao < 0 || opcao > total) {
    return -2;
  }
  return opcao - 1;
}

// Para identificar e usar o método do sistema linear: Único que precisa
bool usa_resolvedor(MetodoInterpolacao metodo) {
  return metodo == interpolacao_sistema_linear;
}

void imprimir_cabecalho_tabela(void) {
  printf("  %-20s | %10s | %10s | %s\n", "Metodo", "Tempo (us)", "Erro nos",
         "Teste");
  printf("  ---------------------|------------|------------|-----------------\n");
}

void imprimir_linha_metrica(const char *nome, struct Metricas met) {
  const char *teste =
      !met.convergiu ? "SEM CONVERGENCIA" : (met.finish ? "OK" : "FALHOU");

  printf("  %-20s | %10.3f | ", nome, met.tempo * 1e6);

  // Caso haja divergência, imprime -
  if (isfinite(met.erro)) {
    printf("%10.3e | %s\n", met.erro, teste);
  } else {
    printf("%10s | %s\n", "-", teste);
  }
}

// Saída detalhada de um único método: métricas + polinômio avaliado
void imprimir_resultado(const char *nome_metodo, const char *nome_resolvedor,
                        double a, double b, function f, struct Metricas met,
                        int amostras) {
  if (nome_resolvedor != NULL) {
    printf("  Metodo: %s / %s\n", nome_metodo, nome_resolvedor);
  } else {
    printf("  Metodo: %s\n", nome_metodo);
  }

  printf("  Tempo:  %.3f us\n", met.tempo * 1e6);
  if (met.convergiu) {
    printf("  Erro:   %.3e\n", met.erro);
  }
  printf("  Teste:  %s\n\n",
         !met.convergiu ? "SEM CONVERGENCIA"
                        : (met.finish ? "OK" : "FALHOU"));

  imprimir_resposta(a, b, amostras, f, &met);
}

/* ==========================================================================================================================
    2.2. Utilizando todos os metodos, interpole f(x) = e^x, em pontos
    igualmente espacados entre x = 1 e x = 3, com
    (a) n = 3; (b) n = 4; (c) n = 5; (d) n = 10.
    Compare os resultados com a funcao original (n e o grau do polinomio).
  ============================================================================================================================*/ 

int main(int argc, char **argv) {

  // Definindo critérios de interpolação
  const int graus[] = {3, 4, 5, 10};
  const int num_graus = sizeof(graus) / sizeof(graus[0]);

  const double a = 1.0;
  const double b = 3.0;
  function f = get_function(F1); /* f(x) = e^x */

  // Usuário escolhe qual método de interpolação usar (0 = todos)
  int escolha_metodo =
      escolher_opcao("Metodos de interpolacao disponiveis:",
                     nomes_metodos_interpolacao, num_metodos_interpolacao,
                     argc > 1 ? argv[1] : NULL);
  if (escolha_metodo < -1 || escolha_metodo >= num_metodos_interpolacao) {
    fprintf(stderr, "metodo invalido; use 0..%d\n", num_metodos_interpolacao);
    return 1;
  }

  // Se for escolhido o método de interpolação do sistema linear
  // o programa pergunta qual resolvedor de sistema linear usar 
  bool precisa_resolvedor =
      escolha_metodo == -1 ||
      usa_resolvedor(metodos_interpolacao[escolha_metodo]);

  int escolha_resolvedor = -1;
  if (precisa_resolvedor) {
    escolha_resolvedor =
        escolher_opcao("Resolvedores de sistema linear disponiveis:",
                       nomes_sistema_linear, num_metodos_sistema_linear,
                       argc > 2 ? argv[2] : NULL);
    if (escolha_resolvedor < -1 ||
        escolha_resolvedor >= num_metodos_sistema_linear) {
      fprintf(stderr, "resolvedor invalido; use 0..%d\n",
              num_metodos_sistema_linear);
      return 1;
    }
  }

  // Imprime a função que está sendo interpolada e como está sendo o teste de erro
  printf("\nInterpolacao de f(x) = e^x em [%.1f, %.1f]\n", a, b);
  printf("Teste: max|P(x_i) - y_i| <= %.0e nos pontos tabelados\n\n",
         TOLERANCIA);

  // Executa e imprime cada método de interpolação selecionado
  for (int m = 0; m < num_metodos_interpolacao; m++) {
    if (escolha_metodo != -1 && m != escolha_metodo) {
      continue;
    }

    MetodoInterpolacao metodo = metodos_interpolacao[m];
    bool com_resolvedor = usa_resolvedor(metodo);

    printf("INTERPOLANDO COM O METODO: %s ==================\n\n",
           nomes_metodos_interpolacao[m]);

    for (int g = 0; g < num_graus; g++) {
      int grau = graus[g];

      printf("--- Grau n = %d (%d pontos) ---\n", grau, grau + 1);

      // Modo comparação: testa todos os resolvedores na mesma tabela
      if (com_resolvedor && escolha_resolvedor == -1) {
        imprimir_cabecalho_tabela();

        for (int r = 0; r < num_metodos_sistema_linear; r++) {
          struct Metricas met = executar_interpolacao(
              metodo, metodos_sistema_linear[r], f, a, b, grau);
          imprimir_linha_metrica(nomes_sistema_linear[r], met);
        }

        printf("\n");
        continue;
      }

      int r = com_resolvedor ? escolha_resolvedor : -1;
      struct Metricas met =
          executar_interpolacao(metodo, r >= 0 ? metodos_sistema_linear[r] : NULL,
                                f, a, b, grau);

      imprimir_resultado(nomes_metodos_interpolacao[m],
                         r >= 0 ? nomes_sistema_linear[r] : NULL, a, b, f, met,
                         10);
      printf("\n");
    }
  }

  return 0;
}
