// Calculo numerico: Tema 4 / ejemplo1.cpp

#include "biseccion.h"
#include "regula_falsi.h"
#include "newton_raphson.h"

// Funcion problema f(x) de la que se desea obtener la raiz
double funcion(double x)
{
	return 1.0 / (x * x) - x;
}

// Funcion que calcula f(x) y f'(x)
void funcion_y_derivada(double x, double &fx, double &dfx)
{
	fx = 1.0 / (x * x) - x;
	dfx = -2.0 / (x * x * x) - 1;
}

int main()
{
	cout.precision(15);
	cout.setf(ios::scientific);

	// Intervalo de acotamiento de la raiz
	const double a0 = 0.5, b0 = 2.0;

	// Numero maximo total de iteraciones
	const int maxits = 10000;

	// Biseccion

	cout << "Biseccion" << endl;

	double a = a0, b = b0, c;
	int its = 0, error = -2;

	// Llamamos al metodo hasta que su codigo de error sea positivo (exito) o -1 (intervalo sin raiz)
	// y mientras no se supere el numero maximo de iteraciones
	while (error == -2 && its < maxits)
		biseccion(a, b, &funcion, c, its, error);
	
	cout << "Its\ta\t\t\tb\t\t\tc" << endl;
	cout << its << '\t' << a << '\t' << b << '\t' << c << endl;

	// Regula falsi
	
	cout << "Regula falsi" << endl;

	a = a0; b = b0;
	its = 0; error = -2;

	// Llamamos al metodo hasta que su codigo de error sea positivo (exito) o -1 (intervalo sin raiz)
	// y mientras no se supere el numero maximo de iteraciones
	while (error == -2 && its < maxits)
		regula_falsi(a, b, &funcion, c, its, error);

	cout << "Its\ta\t\t\tb\t\t\tc" << endl;
	cout << its << '\t' << a << '\t' << b << '\t' << c << endl;

	// Hibrido Newton-Raphson y biseccion

	cout << "Newton-Raphson-Biseccion" << endl;

	a = a0; b = b0;
	its = 0; error = -2;

	// Llamamos al metodo hasta que su codigo de error sea positivo (exito) o -1 (intervalo sin raiz)
	// y mientras no se supere el numero maximo de iteraciones
	while (error == -2 && its < maxits)
		newton_raphson(a, b, &funcion_y_derivada, c, its, error);

	cout << "Its\ta\t\t\tb\t\t\tc" << endl;
	cout << its << '\t' << a << '\t' << b << '\t' << c << endl;


	return 0;
}
