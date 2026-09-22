#include "../include/raizes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// struct Raizes {
// 	float* arr;
// 	int size;
// };

// struct ponto{
// 	float x;
// 	float fx;
// };

// struct Resultados{
// 	struct ponto* arr;
// 	int size;
// };

// struct Resultados calcular_resultados(float a, float b, float h, Funcao f){

// 	struct ponto* calc = malloc(sizeof(float) * 100);
// 	int size = 0;
// 	float curr = a;

// 	while (curr < b) {
// 		if (func(curr, f) * func(curr + h, f) < 0) {
// 			calc[size].x = curr;
// 			calc[size].fx = func(curr, f);
// 		}

// 		curr += h;
// 	}

// 	struct Resultados r;
// 	r.arr = calc;
// 	r.size = size;

// 	return r;
// }

// struct Raizes isolar_raizes(struct Resultados resultados){
//     float* raizes = malloc(sizeof(float) * 100);
//     int size = 0;

//     for (int i = 0; i < resultados.size - 1; i++){
        
//         if (resultados.arr[i].fx * resultados.arr[i+1].fx < 0) {
            
//             raizes[size] = resultados.arr[i].x;    
//             raizes[size + 1] = resultados.arr[i+1].x; 
            
//             size += 2;
//         }
//     }

//     struct Raizes r;
//     r.arr = raizes;
//     r.size = size;

//     return r;
// }

struct Raizes isolar_raizes(float a, float b, float h, function_type f) {

	float* raizes = malloc(sizeof(float) * 100);
	int size = 0;
	float curr = a;

	while (curr < b) {
		if (f(curr) * f(curr + h) < 0) {
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

void tabelar_raizes(float a, float b, float h, function_type f) {

    printf("---------------------------------\n");
    printf("| %-13s | %-13s |\n", "x", "f(x), fi_func");
    printf("---------------------------------\n");

    float curr = a;

    while (curr <= b) {
        printf("| %-13.4f | %-13.4f |\n", curr, f(curr));
        curr += h;
    }
    
    printf("---------------------------------\n");
}