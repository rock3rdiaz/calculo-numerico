// Calculo numerico: Tema 5 / circuito.cpp

#include "lu.h"
#include "sustitucion.h"
#include "inversion.h"

// Resolucion de un circuito de corriente continua
int main()
{
	// Matrix 6x6 de coeficientes
	vector<vector<double>> A = {
		vector<double> {1.0, -1.0, -1.0, 0.0, 0.0, 0.0},
		vector<double> {1.0, 0.0, 0.0, 0.0, 1.0, -1.0},
		vector<double> {0.0, 0.0, 1.0, -1.0, 1.0, 0.0},
		vector<double> {4.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		vector<double> {0.0, 0.0, 2.0, 1.0, 0.0, 0.0},
		vector<double> {0.0, 0.0, 0.0, 1.0, 1.0, 0.0}
	};

	// Vector de terminos independientes
	vector<double> w = {0.0, 0.0, 0.0, 3.0, 3.0, 2.0};
	// Copia
	vector<double> v = w;

	//1. Resolucion mediante descomposicion LU y sustitucion

	vector<int> perm(6);
	double det;

	lu(A, perm, det);
	sustitucion(A, perm, w);

	cout << "Solucion metodo 1:" << endl;
	for (int i = 0; i < 6; i++)
		cout << "I[" << i << "] = " << w[i] << endl;

	// 2. Resolucion mediante inversion
	
	inversion(A, perm);
	
	// Multiplicamos la matriz inversa por el vector de terminos independientes
	for (int i = 0; i < 6; i++)
	{
		double suma = 0.0;

		for (int j = 0; j < 6; j++)
			suma += A[i][j] * v[j];

		w[i] = suma;
	}

	cout << "Solucion metodo 2:" << endl;
	for (int i = 0; i < 6; i++)
		cout << "I[" << i << "] = " << w[i] << endl;

	return 0;
}
