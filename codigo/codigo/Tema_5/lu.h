// Calculo numerico: Tema 5 / lu.h

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

// Descomposicion LU de una matriz cuadrada segun algoritmo de Crout
// Argumentos de entrada:
//		A ........ Matriz cuadrada que se desea descomponer
// Argumentos de salida:
//		A ........ Contiene L (triangulo inferior) y U (triangulo superior y diagonal)
//		perm ..... Reordenacion de filas
//		det ...... Valor del determinante de la matriz
void lu(vector<vector<double>> &A, vector<int> &perm, double &det)
{
	
	// Dimension de la matriz A
	// Suponemos que es cuadrada
	int N = A.size();

	det = 1.0;

	// Elemento de A de valor maximo
	double Amax = 0.0;

	for (int i = 0; i < N; i++)
	{
		// No hemos realizado ninguna permutacion de filas todavia
		perm[i] = i; 

		for (int j = 0; j < N; j++)
			Amax = max(Amax, fabs(A[i][j]));
	}

	// Procedemos por columnas
	for (int j = 0; j < N; j++)
	{
		// Este calculo es necesario solo a partir de la segunda columna
		// Porque: L[i][0] = A[i][0] / U[0][0]
		if (j > 0)
		{
			// Comenzamos con la segunda fila
			// Porque: U[0][j] = A[0][j]
			for (int i = 1; i < N; i++)
			{
				double Sij = A[i][j];

				// Antes de la diagonal:  min(i, j) = i
				// Tras la diagonal: min(i, j) = j
				for (int k = 0; k < min(i, j); k++)
					Sij -= A[i][k] * A[k][j];

				A[i][j] = Sij;
			}
		}

		// Buscamos el pivote
		double pivote = 0.0;
		int indice_pivote;

		for (int k = j; k < N; k++)
		{
			if (fabs(A[k][j]) > pivote)
			{
				indice_pivote = k;
				pivote = fabs(A[k][j]);
			}
		}

		// Intercambio de filas?
		if (indice_pivote != j)
		{
			perm[j] = indice_pivote;

			for (int i = 0; i < N; i++)
				swap(A[j][i], A[indice_pivote][i]);
			
			det = -det;
		}

		pivote = A[j][j];
		
		// Es el pivote nulo?
		if (fabs(pivote) < Amax * 1.0e-14)
		{
			det = 0.0;
			cout << "Error en LU: determinante nulo.";
			return;
		}

		// Dividimos entre el pivote los elementos de L
		if (j < N - 1)
		{
			for (int i = j + 1; i < N; i++)
				A[i][j] /= pivote;
		}

		// Actualizamos el determinante
		det *= pivote;
	}
}
