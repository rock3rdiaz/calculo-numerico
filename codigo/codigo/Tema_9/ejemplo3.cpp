// Calculo numerico: Tema 9 / ejemplo3.cpp

#include <cmath>
#include "matricial.h"

void pqr(double t, double &p, double &q, double &r)
{
	p = t / 2.0;
	q = -t * t / 2.0;
	r = -2.0 * exp(q);
	return;
}

int main()
{
	cout.precision(7);

	// Extremos de integracion
	double a = 0.0;
	double b = sqrt(2.0);

	// Condiciones de contorno
	double ya = 2.0;
	double yb = 2.0 / exp(1.0);

	// Numero de intervalos
	int n = 50;

	// Solucion
	vector<double> y(n - 1);

	matricial(a, b, ya, yb, n, pqr, y);

	double h = (b - a) / n;

	// Resultados
	
	cout << "Tiempo\t\tNumerico\tExacto" << endl;

	for (int i = 0; i < n - 1; i++)
	{
		double t = a + (i + 1) * h;
		cout << t << '\t' << y[i] << '\t' << 2.0 * exp(-t * t / 2.0) << endl;
	}

	return 0;
}
