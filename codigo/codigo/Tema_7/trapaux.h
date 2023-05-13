// Calculo numerico: Tema 7 / trapaux.h

#include <cmath>

using namespace std;

void trapaux(double (*funcion)(double), double a, double b, double &integral, int iteracion)
{
	if (iteracion == 0)
	{
		integral = 0.5 * (b - a) * (funcion(a) + funcion(b));
		return;
	}

	// Numero de puntos medios nuevos:
	// Igual al numero de subintervalos en la iteracion anterior
	int N_puntos_nuevos = static_cast<int>(pow(2.0, iteracion - 1.0));

	// Distancia entre puntos medios
	double delta = (b - a) / N_puntos_nuevos;

	// Longitud de los subintervalos
	double h = 0.5 * delta;

	// Primer punto medio nuevo
	double x = a + h;

	double suma = 0.0;

	for (int i = 0; i < N_puntos_nuevos; i++)
	{
		suma += funcion(x);
		x += delta;
	}

	// El paso de integracion se ha reducido a la mitad respecto a la iteracion anterior
	// Debemos ajustar el valor de la integral anterior adecuadamente
	// Vease ecuacion de la regla trapezoidal repetida
	integral = 0.5 * integral + h * suma;
}
