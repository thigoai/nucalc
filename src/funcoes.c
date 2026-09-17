#include "../include/funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float func(float x, Funcao i){
    switch (i) {
        case F1:
            return 2*pow(x,4) + 4*pow(x,3) + 3*pow(x,2) - 10*x - 15;
        case F2:
            return pow(x,5) - 2*pow(x,4) - 9*pow(x,3) + 22*pow(x,2) + 4*x - 24;
        case F3:
            return 5*pow(x,3) + pow(x,2) - exp(1 - 2*x) + cos(x) + 20;
        case F4:
            return sin(x)*x + 4;
        default:
            return 0.0;
    } 
}

float fi_func(float x, FuncaoFI i){
    switch (i) {
        case Fi1:
            return (2*pow(x,4) + 4*pow(x,3) + 3*pow(x,2) - 15) / 10.0;
        case Fi2:
            return 0.0; // TODO: fazer o resto
        case Fi3:
            return 0.0;
        case Fi4:
            return 0.0;
        default:
            return 0.0;
    }
}
