#ifndef RAIZES_H
#define RAIZES_H

struct Raizes {
	float* arr;
	int size;
};

struct Raizes isolar_raizes(float a, float b, float h, Funcao f);

void tabelar_raizes(float a, float b, float h, Funcao f);

#endif