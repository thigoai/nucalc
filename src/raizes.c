#include "../include/raizes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Raizes isolar_raizes(float a, float b, float h, Funcao f) {

	float* raizes = malloc(sizeof(float) * 100);
	int size = 0;
	float curr = a;

	while (curr < b) {
		if (func(curr, f) * func(curr + h, f) < 0) {
			raizes[size] = curr;
			raizes[size + 1] = curr + h;
			size+= 2;
		}

		curr += h;
	}

	struct Raizes r;
	r.arr = raizes;
	r.size = size;

	return r;
}
