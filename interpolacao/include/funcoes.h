#ifndef FUNCOES_H
#define FUNCOES_H

typedef double (*function)(double);

typedef enum { F1, F2 } Funcao;

function get_function(Funcao i);
function get_fi_function(Funcao i);

extern const Funcao funcoes[];
extern const int num_funcoes;

#endif
