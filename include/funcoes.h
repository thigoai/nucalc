#ifndef FUNCOES_H
#define FUNCOES_H

typedef double (*function)(double);

typedef enum { F1, F2, F3, F4 } Funcao;

function func(Funcao i);
function fi_func(Funcao i);

#endif
