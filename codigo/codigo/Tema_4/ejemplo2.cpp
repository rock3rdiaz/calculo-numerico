// Calculo numerico: Tema 4 / ejemplo2.cpp

#include "laguerre.h"

int main()
{
	cout.precision(15);
	cout.setf(ios::scientific);

	// Vector de coeficientes complejos del polinomio
	// El indice del coeficiente corresponde a la potencia
	vector<complex<double>> a {
		complex<double> (-390625.0, 0.0),
		complex<double> (-31250.0, 0.0),
		complex<double> (-1250.0, 0.0),
		complex<double> (-1250.0, 0.0),
		complex<double> (0.0, 0.0),
		complex<double> (50.0, 0.0),
		complex<double> (2.0, 0.0),
		complex<double> (2.0, 0.0),
		complex<double> (1.0, 0.0)
	};

	// Grado del polinomio
	int n = a.size() - 1;

	// Vector de raices del polinomio
	vector<complex<double>> raices(n);

	// Vector que guarda el numero de iteraciones
	// Inicializamos cada componente al valor 0
	vector<int> its (n, 0);

	// Llamamos al driver
	laguerre_driver(a, raices, true, its);

	// Mostramos en pantalla los resultados
	cout << "Raices:" << endl;
	cout << "Parte real\t\tParte imaginaria\tIts" << endl;
	for (int k = 0; k < n; k++) 
		cout << raices[k].real() << '\t' << raices[k].imag() << '\t' << its[k] << endl;

	return 0;
}
