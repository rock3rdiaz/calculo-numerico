#include <cmath>
#include <iostream>
#include <iomanip>
#include "constants.h"

#ifndef MULLER_H
#define MULLER_H

using namespace std;
using namespace constants;

namespace muller {

    /**
    * Metodo que calcula el valor de la funcion de prueba en el punto recibido como argumento.
    * Funcion de prueba => f(x)=e^0,75x-3sin(1.25x)
    * Para la representacion de los valores calculados en cada iteracion se han usado
    * el mismo numero de decimales que la solucion de ejemplo en el documento (15 decimales de precision).
    *
    */
    double func(double x) {
        return exp(0.75 * x) - (3 * sin(1.25 * x));
    }

    /**
     * Retorna el valor gamma
     * gamma = x0-x2/x1-x0
     *
     */
    double get_gamma(double x0, double x1, double x2) {
        return (x0 - x2) / (x1 - x0);
    }

    /**
     * Calcula el valor de a
     */
    double get_a(double x0, double x1, double x2) {
        double gamma = get_gamma(x0, x1, x2);
        return ((gamma * func(x1)) - (func(x0) * (1 + gamma)) + func(x2)) / (gamma * pow(x1 - x0, 2) * (1 + gamma));
    }

    /**
     * Calcula el valor de b
     */
    double get_b(double x0, double x1, double a) {
        return (func(x1) - func(x0) - a * pow(x1 - x0, 2)) / (x1 - x0);
    }

    /**
     * Calcula el valor de c
     */
    double get_c(double x0) {
        return func(x0);    
    }

    /**
     * Calcula el valor de xr
     */
    double get_xr(double x0, double a, double b, double c) {
        if(b < 0.0) {
            return x0 - (2 * c) / (b - sqrt(pow(b, 2) - 4 * a * c));
        }
        return x0 - (2 * c) / (b + sqrt(pow(b, 2) - 4 * a * c));
    }

    /**
     * Calculamos el punto medio del intervalo definido
     *
     */
    double get_x0(double x1, double x2) {
        return (x1 + x2) / 2.0;
    }

    /**
     * Implementacion del metodo de muller.
     * Recibe como argumento 2 puntos x1 y x2.
     * Calculamos x0 como el punto medio de x1, x2; donde x2 < x0 < x1
     */
    double muller(double x1, double x2) {
        short iter = 0; // numero de iteraciones ejecutadas por el metodo   

        // calculamos el tercer punto, mismo que sera el punto medio del intervalo
        double x0 = get_x0(x1, x2);

        // calculo de los coeficientes iniciales
        double a = get_a(x0, x1, x2);
        double b = get_b(x0, x1, a);
        double c = get_c(x0);
        double xr = get_xr(x0, a, b, c);
        double fxr = func(xr); // valor de la funcion en el cero aproximado

        cout << "Valores INICIALES x: " << "{ x2 = " << setprecision(DOUBLE_PRECISION) << x2 << ", x0 = " << setprecision(DOUBLE_PRECISION) << x0 << ", x1 = " << setprecision(DOUBLE_PRECISION) << x1 << ", f(xr) = " << setprecision(DOUBLE_PRECISION) << fxr << " }" <<endl; 
        cout << "Coeficientes INICIALES : " << "{ a = " << setprecision(DOUBLE_PRECISION) << a << ", b = " << setprecision(DOUBLE_PRECISION) << b << ", c = " << setprecision(DOUBLE_PRECISION) << c << ", xr = " << setprecision(DOUBLE_PRECISION) << xr << " }" << endl; 

        do {
            if(fabs(fxr) > EPSILON and fabs(x2 - x1) > EPSILON) {
                // nos movemos a la derecha
                if(xr > x0) {
                    x2 = x0;
                    x0 = xr;
                } 
                // nos movemos a la izquierda
                else {
                    x0 = xr;
                    x1 = x0;
                }

                x0 = get_x0(x1, x2);
                a = get_a(x0, x1, x2);
                b = get_b(x0, x1, a);
                c = get_c(x0);
                xr = get_xr(x0, a, b, c);
                fxr = func(xr);

                if(isnan(a) or isnan(b) or isnan(c) or isnan(xr)) {
                    cout << "Se ha presentado un error al intentar calcular los coeficientes o la raiz con la precision definida." << "{ a = " << setprecision(DOUBLE_PRECISION) << a << ", b = " << setprecision(DOUBLE_PRECISION) << b << ", c = " << setprecision(DOUBLE_PRECISION) << c << ", xr = " << setprecision(DOUBLE_PRECISION) << xr << " }" << endl;
                    return -1.0;
                }

                cout << "---- Iteracion: " << ++iter << endl;
                cout << "Valores x: " << "{ x2 = " << setprecision(DOUBLE_PRECISION) << x2 << ", x0 = " << setprecision(DOUBLE_PRECISION) << x0 << ", x1 = " << setprecision(DOUBLE_PRECISION) << x1 << ", f(xr) = " << setprecision(DOUBLE_PRECISION) << fxr << " }" <<endl; 
                cout << "Coeficientes: " << "{ a = " << setprecision(DOUBLE_PRECISION) << a << ", b = " << setprecision(DOUBLE_PRECISION) << b << ", c = " << setprecision(DOUBLE_PRECISION) << c << ", xr = " << setprecision(DOUBLE_PRECISION) << xr << " }" << endl; 
            } else {
                cout << "Muller ha encontrado una raiz con la precision esperada! :)" << endl;
                break;
            }
        } while(iter < MAX_ITERATIONS);

        if(iter == MAX_ITERATIONS){
            cout << "Se ha alcanzo el numero maximo de iteraciones configuradas. El metodo Muller no logro encontrar una raiz con la suficiente precision." << endl;
            return -1.0;
        }

        cout << "Numero de iteraciones: " << iter << endl;  
        cout << "Raiz aproximada: " << setprecision(DOUBLE_PRECISION) << xr << endl; 

        return xr;
    }
}

#endif