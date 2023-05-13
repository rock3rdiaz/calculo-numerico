// Calculo numerico: Tema 4 / regula_falsi.h

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Argumentos de la funcion 'regula_falsi':
// a y b ... Extremos del intervalo de acotamiento de la raiz
// f ....... Funcion de la que se desea obtener la raiz
// c ....... La aproximacion a la raiz
// its ..... Numero total de iteraciones realizadas
// error ... Codigo de finalizacion de la funcion:
// 		0 = se encontro la raiz
//		-1 = raiz no contenida en el intervalo
//		-2 = demasiadas iteraciones para la tolerancia asumida

// Todos los argumentos numericos son pasados a 'regula_falsi' como referencia (&).
// La funcion f apunta (*) a la funcion de la que se desea obtener la raiz
// y toma un argumento de tipo double, devolviendo su resultado como double.


void regula_falsi(double &a, double &b, double (*f)(double), double &c, int &its, int &error)
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
		cout << "Regula falsi: raiz no contenida en el intervalo" << endl;
		error = -1;
		return;
	}

	// Tolerancia
	double eps = epsilon * max(fabs(a - b), fabs(0.5 * (a + b)));

	// Comienza el proceso iterativo
	for (int i = 0; i < maxits; i++)
	{
		// Obtenemos el punto de interseccion con el eje horizontal
		c = (a * fb - b * fa) / (fb - fa);
		double fc = f(c);

		// Es c es la raiz?
		if (fc == 0.0)
		{
			its += i + 1;
			error = 0;
			return;
		}

		// Menor de las distancias entre los extremos del intervalo y la aproximacion a la raiz
		double delta = min(fabs(a - c), fabs(b - c));

		// Menor que la tolerancia?
		if (delta <= eps)
		{
			// El metodo ha convergido
			its += i;
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
	cout << "Regula falsi: demasiadas iteraciones para la tolerancia asumida" << endl;
	its += maxits;
	error = -2;
	return;
}
