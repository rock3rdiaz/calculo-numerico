// Calculo numerico: Tema 6 / diacetileno.cpp

#include "jacobi.h"

// Obtencion de las frecuencias de oscilacion del diacetileno: H-C-C-C-C-H
// Los modos de oscilacion se entienden analizando signo y magnitud de los autovectores
int main()
{
	// Establecemos la precision y tipo de notacion numerica de cout
	cout.precision(7);
	cout.setf(ios::scientific);

	// Constantes
	double uma = 1.66042e-24; // gramos
	double c = 3e10; // Velocidad de la luz (cm/s)
	double pi = 3.14159265;
	double masa_hidrogeno= uma;
	double masa_carbono = 12.0 * uma;
	double khc = 5.97e5; // erg/cm2
	double kc3 = 1.55e6; // erg/cm2
	double kc1 = 3.50e5; // erg/cm2

	// Elementos matriz potencial
	double Vd0 = khc / masa_hidrogeno;
	double Vd1 = (khc + kc3) / masa_carbono;
	double Vd2 = (kc1 + kc3) / masa_carbono;
	double Ve0 = -khc / sqrt(masa_carbono * masa_hidrogeno);
	double Ve1 = -kc3 / masa_carbono;
	double Ve2 = -kc1 / masa_carbono;

	// Matriz potencial
	vector<vector<double>> V = {
		vector<double> {Vd0, Ve0, 0.0, 0.0, 0.0, 0.0},
		vector<double> {Ve0, Vd1, Ve1, 0.0, 0.0, 0.0},
		vector<double> {0.0, Ve1, Vd2, Ve2, 0.0, 0.0},
		vector<double> {0.0, 0.0, Ve2, Vd2, Ve1, 0.0},
		vector<double> {0.0, 0.0, 0.0, Ve1, Vd1, Ve0},
		vector<double> {0.0, 0.0, 0.0, 0.0, Ve0, Vd0}
	};

	// Matriz de transformacion
	// Valor inicial arbitrario
	vector<vector<double>> Q = V;

	// Autovalores
	vector<double> d(6);

	// Numero de rotaciones de Jacobi
	int nrot;

	// Diagonalizamos V
	jacobi(V, Q, d, nrot);

	// Resultados
	for (int i = 0; i < 6; i++)
	{
		cout << "Autovalor " << i << ":" << endl;
		cout << d[i] << endl;
	
		cout << "Frecuencia " << i << ":" << endl;
		cout << sqrt(d[i]) / (2.0 * pi * c) << endl;

		cout << "Autovector " << i << ":" << endl;
		for (int j = 0; j < 6; j++)
	        cout << Q[j][i] << endl;
	
		cout << endl;
	}

	cout << nrot << " rotaciones de Jacobi" << endl;

	return 0;
}
