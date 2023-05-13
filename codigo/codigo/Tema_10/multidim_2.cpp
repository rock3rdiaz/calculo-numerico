// Calculo numerico: Tema 9 / multidim_2.cpp

#include <random>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Parte gaussiana del integrando
// 6 dimensiones: x = (x[0], x[1], x[2]), y = (x[3], x[4], x[5])
double gaussiana(vector<double> x)
{
	double xy0 = x[0] - x[3];
	double xy1 = x[1] - x[4];
	double xy2 = x[2] - x[5];
	double xy = xy0 * xy0 + xy1 * xy1 + xy2 * xy2;
	return exp(-0.5 * xy);
}

int main()
{
	// Constantes
	double pi = 4.0 * atan(1.0);

	cout.precision(15);
	cout.setf(ios::scientific);

	// Usamos como semilla un numero asociado al tiempo actual (libreria de C++ chrono)
	// Sera distinto cada vez que ejecutemos el calculo
	unsigned semilla = chrono::system_clock::now().time_since_epoch().count();

	// Declaramos el motor de numeros aleatorios y lo inicializamos con la semilla
	default_random_engine generador(semilla);

	// Declaramos la distribucion normal o gaussiana con media 0.0 y desviacion tipica 1 / sqrt(2) 
	normal_distribution<double> distribucion(0.0, 1.0 / sqrt(2.0));

	// Numero de muestras
	int N = 1000;

	double suma = 0.0, suma2 = 0.0;

	// Variables
	// 6 dimensiones: x = (x[0], x[1], x[2]), y = (x[3], x[4], x[5])
	vector<double> x(6);

	// Metodo crudo de Montecarlo
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 6; j++)
			x[j] = distribucion(generador);

		double z = gaussiana(x);

		suma += z;
		suma2 += z * z;
	}

	suma /= N;
	suma2 /= N;

	// Resultados
	double pi_cubo = pow(pi, 3.0);
	double I = pi_cubo * suma;
	double sigma = pi_cubo * sqrt((suma2 - suma * suma) / N);

	cout << "Numero de muestras: N = " << N << endl;
	cout << "Integral: I = " << I << endl;
	cout << "Error: Sigma = " << sigma << endl;

	return 0;
}
