#ifndef FUNCOES_H
#define FUNCOES_H

typedef enum{
    F1, F2, F3, F4
}Funcao;

typedef enum{
    Fi1, Fi2, Fi3, Fi4
}FuncaoFI;

float func(float x, Funcao i);

float fi_func(float x, FuncaoFI i);

#endif