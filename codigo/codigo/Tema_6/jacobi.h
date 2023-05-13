// Calculo numerico: Tema 6 / jacobi.h

#include <cmath>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

// Modifica los elementos de A que se ven afectados por la rotacion de Jacobi
void rotacion(vector<vector<double>> &A, const double seno, const double tangente_angulo_medio, const int i, const int j, const int k, const int l)
{
	double Aij = A[i][j];
	double Akl = A[k][l];

	A[i][j] = Aij - seno * (Akl + Aij * tangente_angulo_medio);
	A[k][l] = Akl + seno * (Aij - Akl * tangente_angulo_medio);
}

// Rutina de reodenacion en orden descendente de los autovalores y sus correspondientes autovectores
void reordenacion(vector<double> &d, vector<vector<double>> &V)
{
	int N = d.size();

	for (int i = 0; i < N - 1; i++)
	{
		double tmp = d[i];
		int k = i;

		for (int j = i; j < N; j++)
		{
			if (d[j] >= tmp)
			{
				tmp = d[j];
				k = j;
			}
		}

		if (k != i)
		{
			d[k] = d[i];
			d[i] = tmp;

			for (int j = 0; j < N; j++)
			{
				tmp = V[j][i];
				V[j][i] = V[j][k];
				V[j][k] = tmp;
			}
		}
	}
}

// Metodo de Jacobi para la diagonalizacion de matrices reales y simetricas
// Argumentos:
// A ...... Matriz real y simetrica de entrada
// V ...... Matriz de salida con los autovectores
// d ...... Vector de salida con los autovalores
// nrot ... Numero de rotaciones de Jacobi efectuadas
void jacobi(vector<vector<double>> A, vector<vector<double>> &V, vector<double> &d, int &nrot)
{
	// Dimension de A
	int N = A.size();

	// Inicializamos matriz V a la identidad
	for (int p = 0; p < N; p++)
	{
		for (int q = 0; q < N; q++)
			V[p][q] = 0.0;
		V[p][p] = 1.0;
	}

	// Vectores auxiliares de calculo
	vector<double> b(N), z(N);

	// Inicializamos B y D a la diagonal de A
	for (int p = 0; p < N; p++)
	{
		b[p] = A[p][p];
		d[p] = A[p][p];
		z[p] = 0.0;
	}

	nrot = 0;

	double epsilon = numeric_limits<double>::epsilon();

	// Ejecutamos el bucle de barridos
	for (int i = 1; i <= 50; i++)
	{
		// Suma de la magnitud de los elementos no diagonales de A
		double suma_no_diag = 0.0;

		for (int p = 0; p < N - 1; p++)
		{
			for (int q = p + 1; q < N; q++)
				suma_no_diag += fabs(A[p][q]);
		}

		// Convergencia?
		if (suma_no_diag == 0.0)
		{
			reordenacion(d, V);
			return;
		}

		double umbral = 0.0;

		// Umbral en los tres primeros barridos
		if (i < 4)
			umbral = 0.2 * suma_no_diag / (N * N);

		for (int p = 0; p < N - 1; p++)
		{
			for (int q = p + 1; q < N; q++)
			{
				double g = 100.0 * fabs(A[p][q]);

				// Tras cuatro barridos, saltamos la rotacion si el elemento no diagonal es pequeno
				if (i > 4 && g <= epsilon * fabs(d[p]) && g <= epsilon * fabs(d[q]))
					A[p][q] = 0.0;
				// Realizamos la rotacion si el elemento es suficientemente grande
				else if (fabs(A[p][q]) > umbral)
				{
					double tangente, gamma;
					// Variable auxiliar de calculo
					double h = d[q] - d[p];

					// Produce gamma = 0.5 * h / A[p][q] overflow?
					if (g <= epsilon * fabs(h))
						// Lease: tangente = 1/(2*gamma)
						tangente = A[p][q] / h;
					else
					{
						gamma = 0.5 * h / A[p][q];
						tangente = 1.0 / (fabs(gamma) + sqrt(1.0 + gamma * gamma));
						if (gamma < 0.0) tangente = -tangente;
					}

					double coseno = 1.0 / sqrt(1.0 + tangente * tangente);
					double seno = tangente * coseno;

					double tangente_angulo_medio = seno / (1.0 + coseno);

					h = tangente * A[p][q];

					z[p] -= h;
					z[q] += h;

					d[p] -= h;
					d[q] += h;

					A[p][q] = 0.0;

					// Realizamos la rotacion
					// 0 <= j < p
					for (int j = 0; j < p; j++)
						rotacion(A, seno, tangente_angulo_medio, j, p, j, q);
					// p < j < q
					for (int j = p + 1; j < q; j++)
						rotacion(A, seno, tangente_angulo_medio, p, j, j, q);
					// q < j < n
					for (int j = q + 1; j < N; j++)
						rotacion(A, seno, tangente_angulo_medio, p, j, q, j);
					// La acumulamos
					for (int j = 0; j < N; j++)
						rotacion(V, seno, tangente_angulo_medio, j, p, j, q);

					nrot++;
				}
			}
		}

		// Actualizamos d con la suma de (tangente * a[p][q]) y reinicializamos z
		for (int p = 0; p < N; p++)
		{
			b[p] += z[p];
			d[p] = b[p];
			z[p] = 0.0;
		}
	}

	cout << "Demasiadas iteraciones en rutina jacobi..." << endl;
}
