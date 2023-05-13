// Calculo numerico: Tema 9 / matricial.h

#include <vector>
#include <iostream>

using namespace std;

// Resolucion de la ecuacion diferencial:
// y'' + p(t) y' + q(t) y = r(t)
// En el intervalo [a, b]
// Con condiciones de contorno: ya = y(t=a), yb = y(t=b)
// Argumentos:
// a, b ...................... Extremos del intervalo de integracion
// ya, yb .................... Condiciones de contorno
// n ......................... Numero de intervalos
// pqr ....................... Funcion que calcula los valores de p, q, r para un t dado
// y ......................... Vector que contiene la solucion (numero de elementos n-1)

void matricial(double a, double b, double ya, double yb, double n, void (*pqr)(double t, double &p, double &q, double &r), vector<double> &y)
{
	const int nmax = 1000;

	if (n > nmax)
	{
		cout << "Demasiados puntos en rutina matricial." << endl;
		return;
	}

	// Construccion de e, d, u, x
	
	vector<double> e(n - 1), d(n - 1), u(n - 1), x(n - 1);
	
	double h = (b - a) / n;
	double h2 = h * h;
	double hd2 = h / 2.0;

	for (int j = 1; j <= n - 1; j++)
	{
		double t = a + j * h;

		double p, q, r;
		pqr(t, p, q, r);

		int i = j - 1;

		d[i] = -2.0 + h2 * q;
		double z = hd2 * p;
		e[i] = 1 - z;
		u[i] = 1 + z;
		x[i] = h2 * r;
	}

	// Valores especiales
	
	x[0] -= e[0] * ya;
	x[n - 2] -= u[n - 2] * yb;

	// Eliminacion de e[j]
	
	for (int j = 1; j < n - 1; j++)
	{
		double z = e[j] / d[j - 1];
		d[j] -= z * u[j - 1];
		x[j] -= z * x[j - 1];
	}

	// Determinacion de la solucion
	
	y[n - 2] = x[n - 2] / d[n - 2];

	for (int j = n - 3; j >= 0; j--)
		y[j] = (x[j] - u[j] * y[j + 1]) / d[j];

	return;
}
