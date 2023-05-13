// Calculo numerico: Tema 7 / interpolacion.h

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Algoritmo de interpolacion de las diferencias divididas de Newton
// Argumentos:
// abscisas ...... Vector de abscisas
// ordenadas ..... Vector de ordenadas
// x ............. Punto donde deseamos obtener el valor interpolado de la funcion
// y ............. Valor interpolado de la funcion
// error ......... Estimacion del error
void interpolacion(vector<double> abscisas, vector<double> ordenadas, double x, double &y, double &error)
{
	// Numero de puntos
	int N = abscisas.size();

	// Maximo numero de puntos
	const int Nmax = 20;

	if (N > Nmax)
	{
		cout << "Error de interpolacion: demasiados puntos (max. " << Nmax << ")" << endl;
		return;
	}

	// Polinomio interpolador
	vector<vector<double>> P = {
		vector<double> (N),
		vector<double> (N)
	};

	for (int i = 0; i < N; i++)
		P[0][i] = ordenadas[i];

	// Alternativamente P[k0][i] es la iteracion precendente y P[k1][i] la resultante, o al reves
	int k0 = 0;
	int k1 = 1;

	for (int j = 0; j < N - 1; j++)
	{
		for (int i = 0; i < N - 1 - j; i++)
		{
			double denominador = abscisas[i + j + 1] - abscisas[i];

			if (denominador == 0.0)
			{
				cout << "Error de interpolacion: dos abscisas identicas." << endl;
				return;
			}

			P[k1][i] = ((x - abscisas[i]) * P[k0][i + 1] - (x - abscisas[i + j + 1]) * P[k0][i]) / denominador;
		}

		swap(k0, k1);
	}

	y = P[k0][0];

	error = max(fabs(y - P[k1][0]), fabs(y - P[k1][1]));
}
