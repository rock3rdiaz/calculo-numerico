// Calculo numerico: Tema 5 / ejemplo2.cpp

#include "lu.h"
#include "sustitucion.h"
#include "inversion.h"
#include "norma_l1.h"

int main()
{
	// 1. Calculos con matriz original A

	// Declaramos la matriz A como un vector de vectores (2x2)
	vector<vector<double>> A (2, vector<double>(2));

	// Inicializamos A
	A[0][0] = 1.0; A[0][1] = 1.0;
	A[1][0] = 1.1; A[1][1] = 1.0;

	// Definimos el vector de terminos independientes
	vector<double> w = { 1.0, 2.0 };

	// Calculamos la norma L1 de A
	double norma_A = norma_l1(A);

	// Vector de permutaciones y determinante
	vector<int> perm(2);
	double det;

	// Descomposicion LU
	lu(A, perm, det);
	// Resolucion del sistema de ecuaciones
	sustitucion(A, perm, w);
	// Inversion de A
	inversion(A, perm);

	// Calculamos la norma L1 de la inversa de A
	double norma_A_inv = norma_l1(A);

	// Obtenemos el numero de condicion
	double numero_de_condicion = norma_A * norma_A_inv;

	cout << "Numero de condicion: C(A) = " << numero_de_condicion << endl;
	cout << "Solucion con A: (x = " << w[0] << ", y = " << w[1] << ")" << endl;

	// 2. Calculos con matriz A perturbada

	// Inicializamos A cambiando ligeramente A[1][0]
	A[0][0] = 1.0; A[0][1] = 1.0;
	A[1][0] = 1.05; A[1][1] = 1.0;

	w[0] = 1.0; w[1] = 2.0;

	lu(A, perm, det);
	sustitucion(A, perm, w);

	cout << "Solucion con A perturbada: (x = " << w[0] << ", y = " << w[1] << ")" << endl;

	return 0;
}
