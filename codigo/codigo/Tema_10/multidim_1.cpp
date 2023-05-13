// Calculo numerico: Tema 9 / multidim_1.cpp

#include <random>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Funcion que integramos
// 6 dimensiones: x = (x[0], x[1], x[2]), y = (x[3], x[4], x[5])
double integrando(vector<double> x)
{
	double xx = x[0] * x[0] + x[1] * x[1] + x[2] * x[2];
	double yy = x[3] * x[3] + x[4] * x[4] + x[5] * x[5];
	double xy0 = x[0] - x[3];
	double xy1 = x[1] - x[4];
	double xy2 = x[2] - x[5];
	double xy = xy0 * xy0 + xy1 * xy1 + xy2 * xy2;
	return exp(-xx - yy - 0.5 * xy);
}

int main()
{
	// Intervalo de integracion [-xmax,xmax]
	double xmax = 5.0;

	cout.precision(15);
	cout.setf(ios::scientific);

	// Usamos como semilla un numero asociado al tiempo actual (libreria de C++ chrono)
	// Sera distinto cada vez que ejecutemos el calculo
	unsigned semilla = chrono::system_clock::now().time_since_epoch().count();

	// Declaramos el motor de numeros aleatorios y lo inicializamos con la semilla
	default_random_engine generador(semilla);

	// Declaramos la distribucion uniforme definida en el intervalo [-xmax,xmax]
	uniform_real_distribution<double> distribucion(-xmax, xmax);

	// Numero de muestras
	int N = 100000;

	double suma = 0.0, suma2 = 0.0;

	// Variables
	// 6 dimensiones: x = (x[0], x[1], x[2]), y = (x[3], x[4], x[5])
	vector<double> x(6);

	// Metodo crudo de Montecarlo
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 6; j++)
			x[j] = distribucion(generador);

		double z = integrando(x);

		suma += z;
		suma2 += z * z;
	}

	suma /= N;
	suma2 /= N;

	// Resultados
	double jacobiano = pow(2.0 * xmax, 6.0);
	double I = jacobiano * suma;
	double sigma = jacobiano * sqrt((suma2 - suma * suma) / N);

	cout << "Numero de muestras: N = " << N << endl;
	cout << "Integral: I = " << I << endl;
	cout << "Error: Sigma = " << sigma << endl;

	return 0;
}
