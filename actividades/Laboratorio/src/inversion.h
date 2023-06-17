// Calculo numerico: Tema 5 / inversion.h

#include <vector>
#include <algorithm>

#ifndef INVERSION_H
#define INVERSION_H

using namespace std;

namespace inversion {

    // Obtiene la inversa de una matriz previamente descompuesta
    // Argumentos de entrada:
    //		A ........ Matriz cuadrada descompuesta (LU)
    //		perm ..... Vector de reordenacion
    // Argumentos de salida:
    //		A ........ Matriz inversa
    void inversion(vector<vector<double>> &A, vector<int> perm)
    {
        // Dimension de A
        int N = A.size();

        // Inversa inferior (L)
        
        for (int i = 1; i < N; i++)
        {
            for (int j = 0; j < i; j++)
            {
                double suma = A[i][j];

                if (j < i - 1)
                {
                    for (int k = j + 1; k < i; k++)
                        suma += A[i][k] * A[k][j];
                }

                A[i][j] = -suma;
            }
        }

        // Inversa superior (U)
        
        for (int i = 0; i < N - 1; i++)
        {
            A[i][i] = 1.0 / A[i][i];

            for (int j = i + 1; j < N; j++)
            {
                double suma = 0.0;

                for (int k = i; k < j; k++)
                    suma += A[i][k] * A[k][j];

                A[i][j] = -suma / A[j][j];
            }
        }

        A[N - 1][N - 1] = 1.0 / A[N - 1][N - 1];

        // Matriz inversa
        
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                double suma = 0.0;

                int kmin = max(i, j);

                for (int k = kmin; k < N; k++)
                {
                    if (k == j)
                        suma += A[i][k];
                    else
                        suma += A[i][k] * A[k][j];
                }

                A[i][j] = suma;
            }
        }

        // Reordenamos las columnas en orden inverso
        
        for (int j = N - 1; j >= 0; j--)
        {
            int k = perm[j];

            if (k != j)
            {
                for (int i = 0; i < N; i++)
                    swap(A[i][k], A[i][j]);
            }
        }
    }
}

#endif
