// Calculo numerico: Tema 8 / eqdifs.h

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// Programa intermedio de integracion de ecuaciones diferenciales acopladas
// Argumentos:
// t0 .................... Punto de partida
// h ..................... Paso de discretizacion
// np .................... Numero de pasos que se desea calcular
// y ..................... Contiene los valores de las funciones:
//								Vector de vectores: Primer indice -> Numero de la ecuacion
//												    Segundo indice -> Pasos de integracion
// derivadas ............. Funcion que calcula las derivadas
// error_relativo ........ Error relativo de la integracion
// metodo ................ Funcion que implementa el metodo de integracion para avanzar un paso (euler o rk)
void eqdifs(double t0, double h, int np, vector<vector<double>> &y,
		void (*derivadas)(double t, vector<double> y, vector<double> &deriv),
		double error_relativo,
		void (*metodo)(double t, double h, vector<double> y, void (*derivadas)(double t, vector<double> y, vector<double> &deriv), vector<double> &y_nueva, double error_relativo, int &error))
{
	const int neqs_max = 10;
	const int neqs = y.size();

	if (neqs > neqs_max)
	{
		cout << "Demasiadas ecuaciones en rutina eqdifs." << endl;
		return;
	}

	vector<double> y1(neqs), yn(neqs);

	double hh = h;
	int n = 1;
	double t = t0;

	for (int i = 1; i <= np; i++)
	{
		inicio:
		
		int ierr = 0;

		double t1 = t;

		for (int j = 0; j < neqs; j++)
			y1[j] = y[j][i - 1];

		for (int j = 1; j <= n; j++)
		{
			int ierror;

			metodo(t1, hh, y1, derivadas, yn, error_relativo, ierror);
		
			if (ierror == 2)
			{
				hh /= 2.0;
				n *= 2;

				if (n > 64)
				{
					cout << "Demasiadas subdivisiones en rutina eqdifs." << endl;
					return;
				}

				goto inicio;
			}

			ierr = max(ierr, ierror);
			t1 += hh;

			for (int k = 0; k < neqs; k++)
				y1[k] = yn[k];
		}

		t += h;

		for (int j = 0; j < neqs; j++)
			y[j][i] = yn[j];

		if (ierr == 0 && n > 1)
		{
			hh *= 2.0;
			n /= 2;
		}
	}

	return;
}
