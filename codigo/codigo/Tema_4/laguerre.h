// Calculo numerico: Tema 4 / laguerre.h

#include <iostream>
#include <limits>
#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

using namespace std;

// Mejora un valor complejo x por el metodo de Laguerre hasta que converge a una raiz de un polinomio dado.
// La convergencia se obtiene dentro del limite de redondeo que se puede conseguir.
// Argumentos:
// 	a[0,...,n] ...... Vector de n+1 coeficientes complejos del polinomio de grado n (indice = potencia).
//	x ............... Aproximacion a una raiz del polinomio (valor complejo).
//	its ............. Numero de iteraciones realizadas.

void laguerre(vector<complex<double>> a, complex<double> &x, int &its)
{
	// Estimacion del error fraccional de redondeo
	const double eps = numeric_limits<double>::epsilon();

	// Intentamos romper posibles ciclos limite con mr valores fraccionales distintos,
	// una vez cada mt pasos, en un numero maxits total de iteraciones
	const int mr = 8, mt = 10, maxits = mt * mr;

	// Fracciones empleadas para romper un ciclo limite
	const vector<double> fracciones {0.0, 0.5, 0.25, 0.75, 0.13, 0.38, 0.62, 0.88, 1.0};

	// Grado del polinomio
	int n = a.size() - 1;

	// Bucle iterativo que aplica el metodo de Laguerre
	for (int it = 1; it <= maxits; it++)
	{
		its++;

		complex<double> poli = a[n]; // Valor del polinomio: P(x)
		complex<double> d_poli (0.0, 0.0); // Valor de la primera derivada del polinomio: P'(x)
		complex<double> d2_poli (0.0, 0.0); // Mitad de la segunda derivada: P''(x)/2

		// Error en el calculo de P(x)
		double error = abs(poli);

		// Magnitud o modulo de la aproximacion a la raiz
		double abs_x = abs(x);

		// Calculo de P(x), P'(x) y P''(x)/2
		for (int k = n - 1; k >= 0; k--)
		{
			d2_poli = x * d2_poli + d_poli;
			d_poli = x * d_poli + poli;
			poli = x * poli + a[k];
			error = abs(poli) + abs_x * error;
		}

		error *= eps;

		// Raiz encontrada?
		if (abs(poli) <= error) return;

		// Calculo de los coeficientes de delta_x
		complex<double> g = d_poli / poli;
		complex<double> g2 = g * g;
		complex<double> h = g2 - 2.0 * d2_poli / poli;

		complex<double> m (n, 0.0);
		complex<double> m1 (n - 1, 0.0);

		complex<double> r = sqrt(m1 * (m * h - g2));
		complex<double> g_mas = g + r;
		complex<double> g_menos = g - r;

		double abs_g_mas = abs(g_mas);
		double abs_g_menos = abs(g_menos);

		// Tomamos el denominador de mayor magnitud
		if (abs_g_mas < abs_g_menos) g_mas = g_menos;

		// Asumimos que la raiz que buscamos se encuentra a distancia delta_x de nuestra aproximacion x
		complex<double> delta_x;

		// Comprobamos que el denominador no es nulo
		if (max(abs_g_mas, abs_g_menos) > 0.0)
			delta_x = m / g_mas;
		else
			// Situamos la nueva aproximacion a la raiz en la circunferencia unidad
			delta_x = polar(1 + abs_x, double(it));

		// Actualizamos la aproximacion a la raiz
		complex<double> nueva_x = x - delta_x;

		// Ha convergido el calculo?
		if (nueva_x == x) return;

		if (it % mt != 0)
			x = nueva_x;
		else
			// Cada mt iteraciones tomamos un paso fraccional para romper posibles ciclos limite
			x -= fracciones[it / mt] * delta_x;

	}

	cout << "Laguerre: demasiadas iteraciones" << endl;
}

// Calcula todas las raices complejas de un polinomio dado llamando sucesivamente a la funcion laguerre.
// Argumentos:
// 	a[0,...,n] ......... Vector de n+1 coeficientes complejos del polinomio de grado n (indice = potencia).
//	raices[0,...,n-1] .. Vector con las n raices.
//	pulir_raices ....... Indica si se debe pulir o perfeccionar el calculo de las raices.
//	its ................ Vector con el numero de iteraciones para el calculo de cada raiz.

void laguerre_driver(vector<complex<double>> a, vector<complex<double>> &raices, const bool pulir_raices, vector<int> &its)
{
	const double eps = 1.0e-14;

	// Grado del polinomio
	int n = a.size() - 1;

	// Copiamos los coeficientes para deflacion sucesiva
	vector<complex<double>> a_deflacion = a;

	// Bucle de calculo de las raices
	for (int j = n - 1; j >= 0; j--)
	{
		// Aproximacion inicial a la raiz en cero para favorecer la convergencia a la raiz restante de menor magnitud
		complex<double> x (0.0, 0.0);

		vector<complex<double>> a_deflacion_2(j + 2);
		
		for (int k = 0; k < j + 2; k++)
			a_deflacion_2[k] = a_deflacion[k];

		laguerre(a_deflacion_2, x, its[j]);

		// Es la raiz efectivamente real?
		if (fabs(x.imag()) <= 2.0 * eps * fabs(x.real()))
			x = complex<double> (x.real(), 0.0);

		raices[j] = x;

		// Deflacion
		complex<double> b = a_deflacion[j + 1];
		for (int k = j; k >= 0; k--)
		{
			complex<double> c = a_deflacion[k];
			a_deflacion[k] = b;
			b = x * b + c;
		}
	}

	// Pulimos las raices usando los coeficientes no deflacionados
	if (pulir_raices)
		for (int j = 0; j < n; j++)
			laguerre(a, raices[j], its[j]);

	// Ordenamos las raices (parte real creciente)
	for (int j = 1; j < n; j++)
	{
		complex<double> x = raices[j];

		int k;

		for (k = j - 1; k >= 0; k--)
		{
			if (raices[k].real() <= x.real()) break;
			raices[k + 1] = raices[k];
		}

		raices[k + 1] = x;
	}
}
