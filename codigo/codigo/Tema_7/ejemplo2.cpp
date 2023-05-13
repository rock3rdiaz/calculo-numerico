#include "trapezoidal.h"
#include <iostream>

double f(double x)
{
	return sin(x);
}

int main()
{
	// Establecemos la precision y tipo de notacion numerica de cout
	cout.precision(7);
	cout.setf(ios::scientific);
	
	const double pi = 4.0 * atan(1.0);

	double a = 0.0;
	double b = pi;

	double integral = 0.0;

	double error_relativo = 1.0e-6;

	int error;

	trapezoidal(f, a, b, integral, error_relativo, error);

	if (error == 0)
		cout << "Integral = " << integral << endl;
	else
		cout << "No se ha alcanzado la convergencia..." << endl;

	return 0;
}
