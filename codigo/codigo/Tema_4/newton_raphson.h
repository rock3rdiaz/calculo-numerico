// Calculo numerico: Tema 4 / newton_raphson.h

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Argumentos de la funcion 'regula_falsi':
// a y b ... Extremos del intervalo de acotamiento de la raiz
// f ....... Calcula el valor de la funcion y la primera derivada
// c ....... La aproximacion a la raiz
// its ..... Numero total de iteraciones realizadas
// error ... Codigo de finalizacion de la funcion:
// 		0 = se encontro la raiz
//		-1 = raiz no contenida en el intervalo
//		-2 = demasiadas iteraciones para la tolerancia asumida

// Todos los argumentos numericos son pasados a 'regula_falsi' como referencia (&).
// La funcion f apunta (*) a una funcion que calcula el valor de nuestra funcion problema y su primera derivada
// y toma tres argumentos:
//	Argumento 1 ... Valor del punto del que se desea obtener el valor de la funcion
//	Argumento 2 ... Referencia al valor calculado de la funcion
//	Argumento 3 ... Referencia al valor calculado de la primera derivada
   
void newton_raphson(double &a, double &b, void (*f)(double, double&, double&), double &c, int &its, int &error)
{
	// Precision deseada
	const double epsilon = 1.0e-14;

	// Numero maximo de iteraciones
	const int maxits = 100;

	// Queremos que el punto a este a la izquierda del punto b
	if (a > b) swap(a, b);

	double fa, dfa;
	double fb, dfb;
	double fc, dfc;

	// Calculamos el valor de f y f' en los extremos del intervalo
	f(a, fa, dfa);
	f(b, fb, dfb);

	// Signo contrario?
	if (fa * fb > 0.0)
	{
		cout << "Newton-Raphson: raiz no contenida en el intervalo" << endl;
		error = -1;
		return;
	}

	// Tolerancia
	double eps = epsilon * max(fabs(a - b), fabs(0.5 * (a + b)));

	// Variable que indica si vamos a usar el extremo a para aplicar el metodo de Newton-Raphson
	bool usamos_a = true;

	// Comenzamos con el extremo de menor valor absoluto de f
	if (fabs(fa) > fabs(fb)) usamos_a = false;

	// Comienza el proceso iterativo
	for (int i = 0; i < maxits; i++)
	{
		// Longitud del intervalo de acotamiento
		double delta0 = b - a;

		// Correccion a la antigua aproximacion de la raiz
		double delta;

		// Variable que indica si hemos de realizar un paso de biseccion
		bool biseccion = true;

		// Probamos el punto a
		if (dfa != 0.0 && usamos_a)
		{
			delta = -fa / dfa;

			// Se acerca a la raiz y esta dentro del intervalo
			if (delta > 0.0 && delta < delta0)
			{
				c = a + delta;
				biseccion = false;
			}
		}

		// Probamos el punto b
		if (dfb != 0.0 && !usamos_a)
		{
			delta = -fb / dfb;

			// Se acerca a la raiz y esta dentro del intervalo			
			if (delta < 0.0 && fabs(delta) < delta0)
			{
				c = b + delta;
				biseccion = false;
			}
		}

		// Si es el caso realizamos biseccion
		if (biseccion)
		{
			delta = 0.5 * (b - a);
			c = 0.5 * (a + b);
		}

		// Calculamos f(c) y f'(c)
		f(c, fc, dfc);

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
			// Reemplazamos el punto b
			usamos_a = false;
			b = c;
			fb = fc;
			dfb = dfc;
		}
		else
		{
			// Reemplazamos el punto a
			usamos_a = true;
			a = c;
			fa = fc;
			dfa = dfc;
		}

		// Es la correccion menor que la tolerancia?
		if (fabs(delta) <= eps)
		{
			// El metodo ha convergido
			its += i + 1;
			error = 0;
			return;
		}
	}

	cout << "Newton-Raphson: demasiadas iteraciones para la tolerancia asumida" << endl;
	its += maxits;
	error = -2;
	return;
}
