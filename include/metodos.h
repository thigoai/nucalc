#ifndef METODOS_H
#define METODOS_H

typedef double (*MetodoNumerico)(double a, double b, double e,
                                 double (*f)(double), double (*fi)(double));

double bissecao(double a, double b, double e, double (*f)(double),
                double (*fi)(double));

double falsa_posicao(double a, double b, double e, double (*f)(double),
                     double (*fi)(double));

double ponto_fixo(double a, double b, double e, double (*f)(double),
                  double (*fi)(double));

double newton(double a, double b, double e, double (*f)(double),
              double (*fi)(double));

double secante(double a, double b, double e, double (*f)(double),
               double (*fi)(double));

double df_func(double (*f)(double), double x, double h);

extern MetodoNumerico metodos[];
extern const int num_metodos; // Opcional, para evitar recalculações

#endif
