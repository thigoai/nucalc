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


float func(float x) {
	return 2 * (x * x * x * x) + 4 * (x * x * x) + 3 * (x * x) - 10 * x - 15;
}


int main() {

    float zero = falsapos(1, 3, 0.0001, func);

    printf("ZERO: %f, F(ZERO): %f\n", zero, func(zero));

    return 0;
}