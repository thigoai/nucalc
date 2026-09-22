#include "../include/secante.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float secante(float x0, float x1, float e, float (*f)(float)) {
    float x2;

    while (fabs(f(x1)) > e) {
        x2 = x1 - (f(x1) * (x1 - x0)) / (f(x1) - f(x0));
        
        x0 = x1; 
        x1 = x2; 
    }
    
    return x1;
}