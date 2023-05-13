// Calculo numerico: Tema 7 / ejemplo1.cpp

#include "interpolacion.h"

int main()
{
	// Establecemos la precision y tipo de notacion numerica de cout
	cout.precision(7);
	cout.setf(ios::scientific);
	
	double pi = 4.0 * atan(1.0);

	vector<double> abscisas = {
		0.0,
		pi / 6.0,
		pi / 3.0,
		pi / 4.0,
		pi / 2.0
	};

	vector<double> ordenadas = {
		0.0,
		0.5,
		sqrt(3.0) / 2.0,
		sqrt(2.0) / 2.0,
		1.0
	};

	double x = pi / 5.0;
	double y, error;

	interpolacion(abscisas, ordenadas, x, y, error);

	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "sin(x) = " << sin(x) << endl;
	cout << "Error = " << error << endl;

	return 0;
}
