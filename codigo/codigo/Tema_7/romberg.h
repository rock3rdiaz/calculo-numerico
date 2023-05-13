// Calculo numerico: Tema 7 / romberg.h

#include "trapaux.h"
#include "interpolacion.h"

// Integracion numerica de Romberg (extrapolacion de Richarson + regla trapezoidal)
// Argumentos:
// funcion .......... Funcion a integrar
// [a, b] ........... Intervalo de integracion
// integral ......... Resultado de la integracion
// error_absoluto ... Error absoluto admitido
// error ............ Codigo de error: 0 si ha convergido, 1 si no ha convergido
void romberg(double (*funcion)(double), double a, double b, double &integral, double error_absoluto, int &error)
{
	const int maxits = 20;

	vector<double> sumas;
	vector<double> pasos;

	error = 0;

	double h = b - a;

	for (int it = 0; it < maxits; it++)
	{
		double suma;

		trapaux(funcion, a, b, suma, it);

		sumas.push_back(suma);
		pasos.push_back(h * h);

		if (it >= 4)
		{
			// Comenzamos las extrapolaciones despues de 4 divisiones

			double error_interpolacion;

			interpolacion(pasos, sumas, 0.0, integral, error_interpolacion);

			if (error_interpolacion <= error_absoluto)
				return;
		}

		h /= 2.0;
	}

	error = 1;
}
