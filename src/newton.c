#include "../include/newton.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float df_func(float (*f)(float), float x, float h){
    return (f(x) + f(x + h))/ h;
}

float newton(float a, float b, float e, float (*f)(float)) {
    float x = a + ((b - a) / 2);

    while (fabs(f(x)) > e) {
        if(f(a) * f(x) < 0) {
            b = x;
        } else {
            a = x;
        }

        x = x - (f(x)/df_func(f, x, e));
    }

    return x;
}