#include "../include/bissecao.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float bissecao(float a, float b, float e, float (*f)(float)) {
    float x = a + ((b - a) / 2);

    while (fabs(f(x)) > e) {
        if(f(a) * f(x) < 0) {
            b = x;
        } else {
            a = x;
        }

        x = a + ((b - a) / 2);
    }

    return x;
}