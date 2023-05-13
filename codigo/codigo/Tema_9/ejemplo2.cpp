// Calculo numerico: Tema 9 / ejemplo1.cpp

#include "superposicion.h"
#include "../Tema_8/rk.h"

void derivadas_h(double t, vector<double> y, vector<double> &deriv)
{
	deriv[0] = y[1];
	deriv[1] = t * t * y[0] / 2.0 - t * y[1] / 2.0;
	return;
}

void derivadas_c(double t, vector<double> y, vector<double> &deriv)
{
	deriv[0] = y[1];
	deriv[1] = t * t * y[0] / 2.0 - t * y[1] / 2.0 - 2.0 * exp(-t * t / 2.0);
	return;
}


int main()
{
	cout.precision(7);

	vector<vector<double>> c(2, vector<double>(2));
	vector<double> d(2);

	double a = 0.0;
	double b = sqrt(2.0);

	// Condiciones de contorno
	
	c[0][0] = 1.0;
	c[0][1] = 0.0;
	c[1][0] = 1.0;
	c[1][1] = 0.0;

	d[0] = 2.0;
	d[1] = 2.0 / exp(1.0);

	int num_intervalos = 5;
	double error = 1.0e-2;

	vector<double> y(num_intervalos + 1);

	// Ecuacion completa
	
	int caso = 1;

	superposicion(a, b, c, d, num_intervalos, error, y, derivadas_h, derivadas_c, rk, caso);

	// Resultado
	
	double h = (b - a) / num_intervalos;

	cout << "Tiempo\t\tNumerico\tExacto" << endl;
	for (int i = 0; i <= num_intervalos; i++)
	{
		double t = a + i * h;
		cout << t << '\t' << y[i] << '\t' << 2.0 * exp(-t * t / 2.0) << endl;
	}

	return 0;
}
