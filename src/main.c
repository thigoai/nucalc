#include <stdio.h>
#include "funcoes.c" 
#include "raizes.c"  
#include "newton.c"

int main() {
    printf("Isolando as raizes...\n");
    
    tabelar_raizes(-10, 10, 1, F1);
    struct Raizes r = isolar_raizes(-10, 10, 1, F1); 
    
    printf("Raizes isoladas:\n");
    for (int i = 0; i < r.size; i+= 2) {
        printf("lower: %f, upper: %f\n", r.arr[i], r.arr[i+1]);
    }
    
    free(r.arr); 
    
    return 0;
}