// Calculo numerico: Tema 9 / cuadrante.cpp

#include <random>
#include <chrono>
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	cout.precision(15);
	cout.setf(ios::scientific);

	// Usamos como semilla un numero asociado al tiempo actual (libreria de C++ chrono)
	// Sera distinto cada vez que ejecutemos el calculo
	unsigned semilla = chrono::system_clock::now().time_since_epoch().count();

	// Declaramos el motor de numeros aleatorios y lo inicializamos con la semilla
	default_random_engine generador(semilla);

	// Declaramos la distribucion uniforme definida en el intervalo [0,1]
	// Puntos con coordenadas en este intervalo pertenecen al cuadrante
	uniform_real_distribution<double> distribucion(0.0, 1.0);

	// Numero de puntos generados al azar
	const int N = 1000;

	// Numero de puntos interiores
	int M = 0;

	for (int i = 0; i < N; i++)
	{
		// Generamos las coordenadas de un punto al azar
		double x = distribucion(generador);
		double y = distribucion(generador);

		// Calculamos el radio del punto
		double r = x * x + y * y;

		// Si el punto es interior a la circunferencia lo contamos
		if (r <= 1.0) M++;
	}

	// Resultados
	double I = static_cast<double>(M) / static_cast<double>(N);
	double E = sqrt(M) / N;
	double sigma = sqrt(M * (1.0 - I)) / N;
	double I_exacta = atan(1.0); // Pi / 4

	cout << "Numero de puntos generados: N = " << N << endl;
	cout << "Numero de puntos interiores: M = " << M << endl;
	cout << "Area del cuadrante: I = " << I << endl;
	cout << "Estimacion del error: E = " << E << endl;
	cout << "Estimacion mejorada del error: sigma = " << sigma << endl;
	cout << "Area exacta: Pi / 4 = " << I_exacta << endl;

	return 0;
}
