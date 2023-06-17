// Calculo numerico: Tema 5 / norma_l1.h

#include <vector>
#include <cmath>
#include <algorithm>

#ifndef NORMLA_l1_H
#define NORMA_l1_H

using namespace std;

namespace norma_l1 {

    // Calculo de la norma L1 de una matriz cuadrada
    // Input: A ........ Matriz cuadrada
    // Valor de retorno: Norma L1
    double norma_l1(vector<vector<double>> A)
    {
        // Dimension de A
        int N = A.size();

        double norma = 0.0;

        // Procedemos por columnas
        for (int j = 0; j < N; j++)
        {
            double suma = 0.0;

            for (int i = 0; i < N; i++)
                suma += fabs(A[i][j]);

            if (suma > norma)
                norma = suma;
        }

        return norma;
    }
}

#endif
