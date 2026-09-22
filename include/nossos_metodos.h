#ifndef NOSSOS_METODOS_H
#define NOSSOS_METODOS_H

// Consiste em inicialmente inicialmente utilizar o método do ponto fixo, apenas
// para reduzir o intervalo Em seguida, utiliza o método da bisseção para uma
// convergência garantida
double metodo1(double a, double b, double e, double (*f)(double),
               double (*fi)(double));

#endif
