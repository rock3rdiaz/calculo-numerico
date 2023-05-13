// Calculo numerico: Tema 7 / trapezoidal.h

#include "trapaux.h"

void trapezoidal(double (*funcion)(double), double a, double b, double &integral, double error_relativo, int &error)
{
	const int maxits = 20;

	integral = 0.0;
	double integral_anterior = 0.0;

	error = 0;

	for (int i = 0; i < maxits; i++)
	{
		trapaux(funcion, a, b, integral, i);

		if (i >= 2 && fabs(integral - integral_anterior) < error_relativo * fabs(integral))
			return;

		integral_anterior = integral;
	}

	error = 1;
}
