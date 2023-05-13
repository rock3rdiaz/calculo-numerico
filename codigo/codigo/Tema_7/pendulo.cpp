// Calculo numerico: Tema 7 / pendulo.cpp

#include "trapezoidal.h"
#include <iostream>

// Variable global
double mu;

// Integrando
double eliptica(double x)
{
	return 1.0 / sqrt(1.0 - mu * pow(sin(x), 2));
}

int main()
{
	const double pi = 4.0 * atan(1.0);
	const double g = 9.81; // N / kg

	double longitud = 1.0; // m

	double frecuencia0 = sqrt(g / longitud);

	// Amplitud de oscilacion: [0, 180[ grados
	double theta0 = 60.0;
	
	// En radianes
	double theta0_rad = theta0 * pi / 180.0;

	mu = pow(sin(theta0_rad / 2), 2);

	// Invocamos a la funcion trapezoidal
	double integral;
	double error_relativo = 1.0e-12;
	int error;

	trapezoidal(eliptica, 0.0, pi / 2.0, integral, error_relativo, error);

	if (error == 0)
	{
		double periodo = 4.0 * integral / frecuencia0;

		cout << "Longitud = " << longitud << " m" << endl;
		cout << "Amplitud = " << theta0 << " grados" << endl;
		cout << "Periodo = " << periodo << " s" << endl;
	}
	else
	{
		cout << "Metodo trapezoidal no convergente..." << endl;
	}

	return 0;
}
