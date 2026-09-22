#include "funcoes.h"
#ifndef RAIZES_H
#define RAIZES_H

struct Raizes {
	float* arr;
	int size;
};

struct Raizes isolar_raizes(float a, float b, float h, function_type f);
void tabelar_raizes(float a, float b, float h, function_type f);

#endif