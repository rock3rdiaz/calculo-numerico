// Calculo numerico: Tema 9 / superposicion.h

#include "../Tema_8/eqdifs.h"

// Metodo de superposicion
// Problema de contorno de dos puntos
// Argumentos:
// [a, b] ..................... Intervalo de integracion
// c .......................... "Matriz" 2x2 con las condiciones de contorno
// d .......................... Vector de dos componentes con los valores de las condiciones de contorno
// num_intervalos ............. Numero de intervalos de integracion
// error ...................... Error tolerado en la integracion
// y .......................... Solucion de la ecuacion diferencial
//								Vector de (num_intervalos + 1) elementos: y[0] = y(a), y[num_intervalos] = y(b)
// caso ....................... caso = 0 si ecuacion homogenea
//								caso = 1 si ecuacion completa
// derivadas_h ................ Funcion de calculo de derivadas para la ecuacion homogenea
// derivadas_c ................ Funcion de calculo de derivadas para la ecuacion completa
// metodo ..................... Rutina de integracion (euler o rk)
void superposicion(double a, double b, vector<vector<double>> c, vector<double> d, int num_intervalos, double error, vector<double> &y,
		void (*derivadas_h)(double t, vector<double> y, vector<double> &deriv),
		void (*derivadas_c)(double t, vector<double> y, vector<double> &deriv),
		void (*metodo)(double t, double h, vector<double> y, void (*derivadas)(double t, vector<double> y, vector<double> &deriv), vector<double> &y_nueva, double error_relativo, int &error),
		int caso)
{
	const int nmax = 1000;

	if (num_intervalos > nmax)
	{
		cout << "Demasiados intervalos en rutina superposicion." << endl;
		return;
	}

	vector<vector<double>> yy(2, vector<double>(num_intervalos + 1));
	vector<double> y1(num_intervalos + 1), y2(num_intervalos + 1), y3(num_intervalos + 1);

	double h = (b - a) / num_intervalos;

	// Primera integracion
	
	yy[0][0] = 1.0;
	yy[1][0] = 0.0;

	eqdifs(a, h, num_intervalos, yy, derivadas_h, error, metodo);

	for (int i = 0; i < num_intervalos + 1; i++)
		y1[i] = yy[0][i];

	double y1b = yy[0][num_intervalos];
	double y1pb = yy[1][num_intervalos];

	// Segunda integracion
	
	yy[0][0] = 0.0;
	yy[1][0] = 1.0;

	eqdifs(a, h, num_intervalos, yy, derivadas_h, error, metodo);

	for (int i = 0; i < num_intervalos + 1; i++)
		y2[i] = yy[0][i];

	double y2b = yy[0][num_intervalos];
	double y2pb = yy[1][num_intervalos];

	// Tercera integracion: solamente para ecuaciones completas
	
	double y3b, y3pb;
	
	if (caso == 1)
	{
		yy[0][0] = 0.0;
		yy[1][0] = 0.0;

		eqdifs(a, h, num_intervalos, yy, derivadas_c, error, metodo);

		for (int i = 0; i < num_intervalos + 1; i++)
			y3[i] = yy[0][i];

		y3b = yy[0][num_intervalos];
		y3pb = yy[1][num_intervalos];
	}
	else
	{
		y3b = 0.0;
		y3pb = 0.0;
	}

	// Determinacion de alpha y beta
	
	vector<vector<double>> xmat(2, vector<double>(2));
	
	xmat[0][0] = c[0][0];
	xmat[0][1] = c[0][1];
	xmat[1][0] = c[1][0] * y1b + c[1][1] * y1pb;
	xmat[1][1] = c[1][0] * y2b + c[1][1] * y2pb;

	double determinante = xmat[0][0] * xmat[1][1] - xmat[0][1] * xmat[1][0];

	if (determinante == 0.0)
	{
		cout << "Determinante nulo: no existe solucion en rutina superposicion." << endl;
		return;
	}

	vector<double> xd(2);

	xd[0] = d[0];
	xd[1] = d[1] - c[1][0] * y3b - c[1][1] * y3pb;

	double alpha = (xd[0] * xmat[1][1] - xd[1] * xmat[0][1]) / determinante;
	double beta = (xmat[0][0] * xd[1] - xmat[1][0] * xd[0]) / determinante;

	for (int i = 0; i < num_intervalos + 1; i++)
	{
		y[i] = alpha * y1[i] + beta * y2[i];

		if (caso == 1) y[i] += y3[i];
	}

	return;
}
