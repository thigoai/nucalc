#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// float func(float x) {
// 	return 2 * (x * x * x * x) + 4 * (x * x * x) + 3 * (x * x) - 10 * x - 15;
// }

// float fi_func(float x) {
//     return (2 * (x * x * x * x) + 4 * (x * x * x) + 3 * (x * x) - 15) / 10;
// }


float pontofixo(float a, float b, float e, float (*f)(float)) {
    float x = fi_func((b - a) / 2);

    while (fabs(f(x)) > e) {
        if(f(a) * f(x) < 0) {
            b = x;
        } else {
            a = x;
        }

        x = fi_func(x);
    }

    return x;
}