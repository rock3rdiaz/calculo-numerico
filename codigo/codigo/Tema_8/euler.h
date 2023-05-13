// Calculo numerico: Tema 8 / euler.h

#include "../Tema_7/interpolacion.h"

// Integracion para un paso h
// Mediante la regla de Euler + Extrapolacion de Richardson
// Argumentos:
// t ............... Punto actual
// h ............... Paso de integracion que deseamos dar
// y ............... Valor de las funciones en t
// derivadas ....... Funcion que calcula las derivadas
// y_nueva ......... Valor de las funciones en t + h
// error_relativo .. Error maximo tolerado relativo
// error ........... Codigo de error:
//						0 ... Convergencia (paso muy corto)
//						1 ... Convergencia
//						2 ... No hay convergencia (paso muy largo)
void euler(double t, double h, vector<double> y, void (*derivadas)(double t, vector<double> y, vector<double> &deriv), vector<double> &y_nueva, double error_relativo, int &error)
{
	const int neqs_max = 10;
	const int neqs = y.size();

	if (neqs > neqs_max)
	{
		cout << "Demasiadas ecuaciones en rutina euler." << endl;
		return;
	}

	vector<int> numero_puntos = { 1, 2, 3, 5, 7, 10, 16 };
	const int nsub = 6;

	vector<vector<double>> yy(neqs, vector<double>(nsub + 1));
	vector<double> hh;
	vector<vector<double>> f(17, vector<double>(neqs));
	vector<double> yerror(neqs), der(neqs), der0(neqs);

	// Punto inicial

	error = 0;

	for (int i = 0; i < neqs; i++)
		f[0][i] = y[i];

	hh.push_back(h);

	derivadas(t, y, der0);

	for (int i = 0; i < neqs; i++)
		yy[i][0] = y[i] + h * der0[i];

	// Extrapolacion de Richardson
	
	for (int i = 1; i <= nsub; i++)
	{
		int npuntos = numero_puntos[i];

		double h1 = h / npuntos;
		hh.push_back(h1);

		for (int j = 0; j < neqs; j++)
			f[1][j] = f[0][j] + h1 * der0[j];

		for (int j = 2; j <= npuntos; j++)
		{
			double x = t + (j - 1) * h1;

			derivadas(x, f[j - 1], der);

			for (int k = 0; k < neqs; k++)
				f[j][k] = f[j - 1][k] + h1 * der[k];
		}

		for (int j = 0; j < neqs; j++)
			yy[j][i] = f[npuntos][j];

		// Extrapolacion

		double xerror = 0.0;

		for (int j = 0; j < neqs; j++)
		{
			interpolacion(hh, yy[j], 0.0, y_nueva[j], yerror[j]);
			xerror = max(xerror, fabs(yerror[j] / y_nueva[j]));
		}

		// Test sobre el error

		if (xerror <= error_relativo)
		{
			if (i <= 3) error = 0;
			else error = 1;
			return;
		}
	}

	error = 2;
	return;
}
