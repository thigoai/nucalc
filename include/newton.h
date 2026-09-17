#ifndef NEWTON_H
#define NEWTON_H

float df_func(float (*f)(float), float x, float h);
float newton(float a, float b, float e, float (*f)(float));


#endif