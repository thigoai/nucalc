#ifndef NOSSOS_METODOS_H
#define NOSSOS_METODOS_H

// Consiste em inicialmente inicialmente utilizar o método do ponto fixo, apenas para reduzir o intervalo
// Em seguida, utiliza o método da bisseção para uma convergência garantida
float metodo1(float a, float b, float e, float (*f)(float), float (*fi)(float)); 

#endif