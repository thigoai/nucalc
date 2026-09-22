#include <stdio.h>
#include <math.h>
#include "bissecao.c"
#include "funcoes.c"
#include "raizes.c"  


int main() {
    printf("Isolando as raizes...\n");
    
    function_type f = get_function(F1);
    function_type fi = get_fi_function(F1);

    double  lower = 3;
    double  upper = 4;
    printf("lower: %f, upper: %f\n", lower, upper);
	double  k = bissecao(lower, upper, 1e-3, f);


    
    return 0;
}
