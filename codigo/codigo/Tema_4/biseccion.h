// Calculo numerico: Tema 4 / biseccion.h

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Argumentos de la funcion 'biseccion':
// a y b ... Extremos del intervalo de acotamiento de la raiz
// f ....... Funcion de la que se desea obtener la raiz
// c ....... La aproximacion a la raiz
// its ..... Numero total de iteraciones realizadas
// error ... Codigo de finalizacion de la funcion:
// 		0 = se encontro la raiz
//		-1 = raiz no contenida en el intervalo
//		-2 = demasiadas iteraciones para la tolerancia asumida

// Todos los argumentos numericos son pasados a 'biseccion' como referencia (&).
// La funcion f apunta (*) a la funcion de la que se desea obtener la raiz
// y toma un argumento de tipo double, devolviendo su resultado como double.

void biseccion(double &a, double &b, double (*f)(double), double &c, int &its, int &error)
{
	// Precision deseada
	const double epsilon = 1.0e-14;

	// Numero maximo de iteraciones
	const int maxits = 100;

	// Calculamos el valor de f en los extremos del intervalo
	double fa = f(a);
	double fb = f(b);

	// Signo contrario?
	if (fa * fb > 0.0)
	{
		cout << "Biseccion: raiz no contenida en el intervalo" << endl;
		error = -1;
		return;
	}

	// Tolerancia
	double eps = epsilon * max(fabs(a - b), fabs(0.5 * (a + b)));

	// Comienza el proceso iterativo
	for (int i = 0; i < maxits; i++)
	{
		// Longitud del intervalo menor que la tolerancia?
		if (fabs(a - b) <= eps)
		{
			// El metodo ha convergido
			its += i;
			error = 0;
			return;
		}

		// Biseccion
		c = 0.5 * (a + b);
		double fc = f(c);

		// Es c la raiz?
		if (fc == 0.0)
		{
			its += i + 1;
			error = 0;
			return;
		}

		// Tienen f(a) y f(c) signo contrario?
		if (fa * fc < 0.0)
		{
			// Sustituimos b por c
			b = c;
			fb = fc;
		}
		else
		{
			// Sustituimos a por c
			a = c;
			fa = fc;
		}
	}

	// Llegados a este punto se han agotado las iteraciones sin haber encontrado la raiz
	cout << "Biseccion: demasiadas iteraciones para la tolerancia asumida" << endl;
	its += maxits;
	error = -2;
	return;
}
