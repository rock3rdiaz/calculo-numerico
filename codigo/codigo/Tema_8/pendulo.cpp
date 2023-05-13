// Calculo numerico: Tema 8 / pendulo.cpp

#include "eqdifs.h"
#include "euler.h"

int llamadas = 0;

// y[0] = angulo
// y[1] = velocidad angular
void derivadas_1(double t, vector<double> y, vector<double> &deriv)
{
	llamadas++;

	deriv[0] = y[1];
	deriv[1] = -sin(y[0]);

	return;
}

// y[0] = tiempo
// y[1] = velocidad angular
void derivadas_2(double theta, vector<double> y, vector<double> &deriv)
{
	llamadas++;

	deriv[0] = 1.0 / y[1];
	deriv[1] = -sin(theta) / y[1];

	return;
}

int main()
{
	const double pi = 4.0 * atan(1.0);

	vector<vector<double>> y(2, vector<double> (2));

	double alpha0 = 30.0; // Amplitud inicial en grados (positiva)
	double theta0 = alpha0 * pi / 180.0; // Y en radianes
	
	// Condiciones iniciales
	
	y[0][0] = theta0; // Angulo
	y[1][0] = 0.0; // Velocidad angular

	double t = 0.0;
	double h = pi / 100.0;

	double error = 1.0e-10;

	// Deteccion del cambio de signo del angulo
	
	bool cambio = false;

	while (!cambio)
	{
		eqdifs(t, h, 1, y, derivadas_1, error, euler);

		if (y[0][1] < 0.0) cambio = true;
		
		y[0][0] = y[0][1];
		y[1][0] = y[1][1];

		t += h;
	}

	// Integramos tomando como variable el angulo

	y[0][0] = t + h;
	y[1][0] = y[1][1];

	double theta = y[0][1];
	
	eqdifs(theta, -theta, 1, y, derivadas_2, error, euler);

	// Resultado
	
	cout << "Angulo inicial = " << alpha0 << endl;
	cout << "T/4 = " << y[0][1] << endl;
	cout << "Llamadas: " << llamadas << endl;

	return 0;
}
