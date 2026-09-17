#include "falsapos.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float falsapos(float a, float b, float e, float (*f)(float)) {

    float x = (a*f(b) - b*f(a))/(f(b) - f(a));

    while (fabs(f(x)) > e) {
        if(f(a) * f(x) < 0) {
            b = x;
        } else {
            a = x;
        }

        x = (a*f(b) - b*f(a))/(f(b) - f(a));
    }

    return x;
}