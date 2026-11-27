#include "../include/lagrange.h"
#include <math.h>

#define DENOMINADOR_MINIMO 1e-14L

// li(x) = {
//             1, x = xi
//             0, x = xj
//          }
//recebe o grau do polinomio e o ponto atual (xi),  e quarda no vetor base
bool calcular_l_i(int grau, int i, const Ponto pontos[], long double base[]){

    int n  = grau + 1; // quant. de coeficientes do polinomio.
    for (int k = 0; k < n; k++){ base[k] = 0.0L;} // começa com vetor zerado
    base[0] = 1.0L; 

    long double denominador = 1.0L;
    long double xi = pontos[i].x;

    // pecorrer toda a tabela 
    for (int j = 0; j < n; j++){
        if (j == i){continue;} // ignora j = i no produtorio

        long double xj = pontos[j].x;
        denominador *= (xi - xj);

        // Multiplica base(x) por (x - x_j)
        for (int p = grau; p >= 1; p--) {
            base[p] = base[p - 1] - xj * base[p];
        }
        base[0] = -xj * base[0];
    }
    
    if(fabs(denominador) < DENOMINADOR_MINIMO){
        return false;
    }

    for (int p = 0; p < n; p++){
        base[p] /= denominador;
    }
    return true;
}

void interpolacao_lagrange(int grau, const Ponto pontos[], 
    MetodoSistemaLinear resolver, double coeficientes[]){

    (void)resolver;

    int n = grau + 1;
    long double base[n];
    long double acumulador[n];

    for (int k = 0; k < n; k++){
        acumulador[k] = 0.0L;
    }

    for (int i = 0; i < n; i++){
        if(!calcular_l_i(grau, i, pontos, base)){
            for (int k = 0; k < n; k++){
                coeficientes[k] = NAN; // falhou
            }
            return;
        }

        for (int p = 0; p < n; p++){
            acumulador[p] += (long double)pontos[i].y * base[p];
        }
    }

    for (int p = 0; p < n; p++) {
        coeficientes[p] = (double)acumulador[p];
    }
}