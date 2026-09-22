#ifndef FUNCOES_H
#define FUNCOES_H

typedef double (*function_type)(double);

typedef enum { F1, F2, F3, F4 } Funcao;

function_type func(Funcao i);

function_type fi_func(Funcao i);

#endif
