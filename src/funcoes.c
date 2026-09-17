#include <stdlib.h>
#include <math.h>

typedef enum {
    F1, F2, F3, F4
} FuncaoID;

double f1(double x, FuncaoID id) {
    switch(id) {
        case F1:
            return sin(x);
    }
    return 0;
}