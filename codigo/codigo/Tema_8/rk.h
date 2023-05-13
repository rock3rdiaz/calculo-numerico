// Calculo numerico: Tema 8 / rk.h

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// Integracion por el metodo de Runge-Kutta Cash-Karp
// Argumentos:
// t ........................ Punto de partida
// h ........................ Paso de integracion
// y ........................ Valor inicial de la funcion
// derivadas ................ Funcion que calcula las derivadas
// y_nueva .................. Valor final de la funcion
// error_relativoo .......... Error relativo tolerado
// error .................... Codigo de error:
//								0 ... Convergencia (paso muy corto)
//								1 ... Convergencia
//								2 ... No hay convergencia (paso muy largo)
void rk(double t, double h, vector<double> y, void (*derivadas)(double t, vector<double> y, vector<double> &deriv), vector<double> &y_nueva, double error_relativo, int &error)
{
	const int neqs_max = 10;
	const int neqs = y.size();

	if (neqs > neqs_max)
	{
		cout << "Demasiadas ecuaciones en rutina rk." << endl;
		return;
	}

	const double a2 = 0.2, a3 = 0.3, a4 = 0.6, a5 = 1.0, a6 = 0.875;
	const double b21 = 0.2, b31 = 3.0 / 40.0, b41 = 0.3, b51 = -11.0 / 54.0, b61 = 1631.0 / 55296.0;
	const double b32 = 9.0 / 40.0, b42 = -0.9, b52 = 2.5, b62 = 175.0 / 512.0;
	const double b43 = 1.2, b53 = -70.0 / 27.0, b63 = 575.0 / 13824.0;
	const double b54 = 35.0 / 27.0, b64 = 44275.0 / 110592.0;
	const double b65 = 253.0 / 4096.0;
	const double c1 = 37.0 / 378.0, c3 = 250.0 / 621.0, c4 = 125.0 / 594.0, c6 = 512.0 / 1771.0;
	const double d1 = 2825.0 / 27648.0, d3 = 18575.0 / 48384.0, d4 = 13525.0 / 55296.0, d5 = 277.0 / 14336.0, d6 = 0.25;

	vector<double> xk1(neqs), xk2(neqs), xk3(neqs), xk4(neqs), xk5(neqs), xk6(neqs), yy(neqs);

	derivadas(t, y, xk1);

	for (int i = 0; i <neqs; i++)
		yy[i] = y[i] + h * b21 * xk1[i];

	derivadas(t + a2 * h, yy, xk2);

	for (int i = 0; i <neqs; i++)
		yy[i] = y[i] + h * (b31 * xk1[i] + b32 * xk2[i]);

	derivadas(t + a3 * h, yy, xk3);

	for (int i = 0; i <neqs; i++)
		yy[i] = y[i] + h * (b41 * xk1[i] + b42 * xk2[i] + b43 * xk3[i]);

	derivadas(t + a4 * h, yy, xk4);

	for (int i = 0; i <neqs; i++)
		yy[i] = y[i] + h * (b51 * xk1[i] + b52 * xk2[i] + b53 * xk3[i] + b54 * xk4[i]);

	derivadas(t + a5 * h, yy, xk5);

	for (int i = 0; i <neqs; i++)
		yy[i] = y[i] + h * (b61 * xk1[i] + b62 * xk2[i] + b63 * xk3[i] + b64 * xk4[i] + b65 * xk5[i]);

	derivadas(t + a6 * h, yy, xk6);

	double err = 0.0;

	for (int i = 0; i <neqs; i++)
	{
		y_nueva[i] = y[i] + h * (c1 * xk1[i] + c3 * xk3[i] + c4 * xk4[i] + c6 * xk6[i]);
		yy[i] = h * ((c1 - d1) * xk1[i] + (c3 - d3) * xk3[i] + (c4 - d4) * xk4[i] - d5 * xk5[i] + (c6 - d6) * xk6[i]);
		err = max(error_relativo, 2.0 * fabs(yy[i]) / (fabs(y[i] + fabs(y_nueva[i]))));
	}

	if (err <= error_relativo)
	{
		error = 1;
		if (error_relativo / err > 10.0)
			error = 0;
	}
	else
		error = 2;

	return;
}
