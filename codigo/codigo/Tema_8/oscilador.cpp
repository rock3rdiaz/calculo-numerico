// Calculo numerico: Tema 8 / oscilador.cpp

#include "eqdifs.h"
#include "euler.h"
#include "rk.h"

int llamadas = 0;

// Calcula las derivadas del sistema
// y[0] = x
// y[1] = v
void derivadas(double t, vector<double> y, vector<double> &deriv)
{
	llamadas++;

	const double pi = 4.0 * atan(1.0);
	const double w1 = 2.0 * pi;
	const double w = pi;
	const double g = 1.0, a = 1.0, z = 0.0;

	double w0 = sqrt(w1 * w1 + g * g);
	double f = a * sqrt(pow(w0 * w0 - w * w, 2.0) + pow(2.0 * g * w, 2.0));
	double eta = z - atan(2.0 * g * w / (w0 * w0 - w * w));
	
	deriv[0] = y[1];
	deriv[1] = -w0 * w0 * y[0] - 2.0 * g * y[1] + f * cos(w * t - eta);

	return;
}

int main()
{
	cout.precision(7);
	cout.setf(ios::scientific);

	// Constantes
	const double pi = 4.0 * atan(1.0);
	const double w1 = 2.0 * pi;
	const double w = pi;
	const double g = 1.0, a = 1.0, z = 0.0;

	// Caso
	double c1 = 100.0;
	double c2 = 0.0;

	double hm = 1.0; // Paso
	double np = 10; // Numero de pasos
	double t = 0.0; // Tiempo inicial

	double error = 1.0e-4;

	double w0 = sqrt(w1 * w1 + g * g);
	double f = a * sqrt(pow(w0 * w0 - w * w, 2.0) + pow(2.0 * g * w, 2.0));
	double eta = z - atan(2.0 * g * w / (w0 * w0 - w * w));

	double t0 = t;

	// Vector de vectores que contiene los valores de las funciones
	// En este caso hay 2 ecuaciones y 100 puntos de integracion + condicion inicial
	vector<vector<double>> y(2, vector<double>(101));

	y[0][0] = (c1 * cos(w1 * t) + c2 * sin(w1 * t)) * exp(-g * t) + a * cos(w * t - z);
	y[1][0] = -g * (c1 * cos(w1 * t) + c2 * sin (w1 * t)) * exp(-g * t) + w1 * (-c1 * sin(w1 * t) + c2 * cos(w1 * t)) * exp(-g * t) - a * w * sin(w * t - z);

	eqdifs(t, hm, np, y, derivadas, error, euler);

	// Resultados

	cout << "Numerico\tExacto\t\tError" << endl;

	for (int i = 0; i <= np; i++)
	{
		t = t0 + hm * i;
		double exacto = (c1 * cos(w1 * t) + c2 * sin(w1 * t)) * exp(-g * t) + a * cos(w * t - z);
		double error_real = fabs(y[0][i] - exacto);
		cout << y[0][i] << '\t' << exacto << '\t' << error_real << endl;
	}

	cout << "Llamadas: " << llamadas << endl;

	return 0;
}
