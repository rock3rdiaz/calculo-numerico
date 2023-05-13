// Calculo numerico: Tema 9 / ejemplo1.cpp

#include "../Tema_8/eqdifs.h"
#include "../Tema_8/rk.h"

void derivadas(double t, vector<double> y, vector<double> &deriv)
{
	deriv[0] = y[1];
	deriv[1] = y[0] * y[0] + y[1] * y[1];
	return;
}

// Metodo del disparo

int main()
{
	cout.precision(12);

	const int num_intervalos = 100;

	double h = 1.0 / num_intervalos; // Paso de integracion
	double t0 = 0.0;

	vector<vector<double>> y(2, vector<double>(num_intervalos + 1));
	y[0][0] = 0.0;

	double error = 1.0e-4;

	vector<double> yp = { -0.5, 0.5 }; // Valores de la derivada en el origen
	
	vector<double> funcion(2);

	// Integracion
	
	for (int i = 0; i < 2; i++)
	{
		y[1][0] = yp[i];
		eqdifs(t0, h, num_intervalos, y, derivadas, error, rk);
		cout << "Derivada = " << y[1][0] << " Yb = " << y[0][num_intervalos] << endl;
		funcion[i] = y[0][num_intervalos] - 1.0;
	}

	// Regula falsi
	
	const int num_its = 7;

	for (int i = 0; i < num_its; i++)
	{
		double nueva_yp = (yp[0] * funcion[1] - yp[1] * funcion[0]) / (funcion[1] - funcion[0]);
		y[1][0] = nueva_yp;

		eqdifs(t0, h, num_intervalos, y, derivadas, error, rk);

		cout << "Derivada = " << y[1][0] << " Yb = " << y[0][num_intervalos] << endl;

		double nueva_funcion = y[0][num_intervalos] - 1.0;

		if (fabs(yp[0] - nueva_yp) < fabs(yp[1] - nueva_yp))
		{
			yp[1] = nueva_yp;
			funcion[1] = nueva_funcion;
		}
		else
		{
			yp[0] = nueva_yp;
			funcion[0] = nueva_funcion;
		}
	}

	return 0;
}
