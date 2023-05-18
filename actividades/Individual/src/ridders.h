#include <cmath>
#include <iostream>
#include <iomanip>
#include "constants.h"

#ifndef RIDDERS_H
#define RIDDERS_H

using namespace std;
using namespace constants;

namespace ridders {

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
	 * Calculamos el punto medio del intervalo definido
	 *
	 */
	double get_x3(double x1, double x2) {
	    return (x1 + x2) / 2.0;
	}

	/**
	 * Calculamos el x4 siguiendo el metodo usado por regula-falsi
	 *
	 */
	double get_x4(double x1, double x2, double x3) {
		double fx1 = func(x1);
		double fx2 = func(x2);
		double fx3 = func(x3);
		if((fx1 - fx2) < 0.0) {
			return x3 + ((x3 - x1) * ((-fx3) / sqrt(pow(fx3, 2) - (fx1 * fx2))));
		} 
	    return x3 + ((x3 - x1) * ((fx3) / sqrt(pow(fx3, 2) - (fx1 * fx2))));
	}

	/**
	 * Implementacion del metodo de Ridder.
	 * Recibe como argumento 2 puntos x1 y x2.
	 * Calculamos x3 como el punto medio de x1, x2; donde x2 < x3 < x1
	 */
	double ridders(double x1, double x2) {
		short iter = 0; // numero de iteraciones ejecutadas por el metodo
		double x3, x4, fx1, fx2, fx3, fx4 = 0.0;
		do {
			// calculamos el tercer punto, mismo que sera el punto medio del intervalo
		    x3 = get_x3(x1, x2);

		    // calculamos el cuarto punto
		    x4 = get_x4(x1, x2, x3);

		    // calculamos los valores de la funcion en los puntos del intervalo
		    fx1 = func(x1);
		    fx2 = func(x2);
		    fx3 = func(x3);
		    fx4 = func(x4);
	        if(fabs(fx4) > EPSILON and fabs(x2 - x1) > EPSILON) {
	            if(fx3 * fx4 < 0.0) {
	                x1 = x3;
	                x2 = x4;
	            } 
	            else if(fx1 * fx4 < 0.0) {
	                x2 = x4;
	            } 
	            else if(fx2 * fx4 < 0.0) {
	            	x1 = x2;
	            	x2 = x4;
	            } 

	            if(isnan(x4)) {
	                cout << "Se ha presentado un error al intentar calcular los nuevos valores con la precision definida." << "{ x4 = " << x4 << endl;
	                return -1.0;
	            }

                iter++;
	        } else {
	            break;
	        }
	    } while(iter < MAX_ITERATIONS);

	    if(iter == MAX_ITERATIONS){
            cout << "Se ha alcanzo el numero maximo de iteraciones configuradas. El metodo Ridders no logro encontrar una raiz con la suficiente precision." << endl;
            return -1.0;
        }

        cout << "Its\tx1\t\t\tx2\t\t\tx3" << endl;
        cout << iter << '\t' << x1 << '\t' << x2 << '\t' << x4 << endl;

        return x4;
	}
}

#endif
