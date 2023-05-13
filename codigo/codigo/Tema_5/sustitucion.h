// Calculo numerico: Tema 5 / sustitucion.h

#include <vector>
#include <algorithm>

using namespace std;

// Sustitucion para resolver un sistema de ecuaciones
// Argumentos de entrada:
//		A ........ Matriz del sistema descompuesta en forma LU
//		perm ..... Vector de reordenacion de filas
//		w ........ Vector de terminos independientes
// Argumentos de salida:
//		w ........ Vector solucion del sistema
void sustitucion(vector<vector<double>> A, vector<int> perm, vector<double> &w)
{
	// Dimension de la matriz A
	int N = A.size();

	// Reordenamos vector de terminos independientes
	for (int i = 0; i < N; i++)
	{
		int k = perm[i];

		if (k != i) swap(w[k], w[i]);
	}

	// Calculamos la solucion intermedia
	// La almacenamos en w
	for (int i = 1; i < N; i++)
	{
		double suma = w[i];
		
		for (int j = 0; j < i; j++)
			suma -= A[i][j] * w[j];

		w[i] = suma;
	}

	// Calculamos la solucion al sistema de ecuaciones
	// La almacenamos en w
	w[N - 1] /= A[N - 1][N - 1];

	for (int i = N - 2; i >= 0; i--)
	{
		double suma = w[i];

		for (int j = i + 1; j < N; j++)
			suma -= A[i][j] * w[j];

		w[i] = suma / A[i][i];
	}
}
