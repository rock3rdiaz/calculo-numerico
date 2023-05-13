// Calculo numerico: Tema 9 / crudo.cpp

#include <random>
#include <chrono>
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	const double pi = 4.0 * atan(1.0);

	cout.precision(15);
	cout.setf(ios::scientific);

	// Usamos como semilla un numero asociado al tiempo actual (libreria de C++ chrono)
	// Sera distinto cada vez que ejecutemos el calculo
	unsigned semilla = chrono::system_clock::now().time_since_epoch().count();

	// Declaramos el motor de numeros aleatorios y lo inicializamos con la semilla
	default_random_engine generador(semilla);

	// Declaramos la distribucion uniforme definida en el intervalo [0,pi]
	uniform_real_distribution<double> distribucion(0.0, pi);

	// Numero de muestras
	int N = 10000;

	// Metodo crudo de Montecarlo
	double suma = 0.0, suma2 = 0.0;
	
	for (int i = 0; i < N; i++)
	{
		double x = distribucion(generador);
		double y = sin(x) * sin(x);
		suma += y;
		suma2 += y * y;
	}

	suma /= N;
	suma2 /= N;

	// Resultados
	cout << "Numero de muestras: N = " << N << endl;
	cout << "Integral: I = " << pi * suma << endl;
	cout << "Error: E = " << pi * sqrt((suma2 - suma * suma) / N) << endl;
	cout << "Inegral exacta: Pi / 2 = " << 0.5 * pi << endl;
	cout << "Desviacion tipica: Pi / sqrt(8) = " << pi / sqrt(8) << endl;

	return 0;
}
