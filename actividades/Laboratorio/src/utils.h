#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

namespace utils {
    
    /**
     *
     * Sobrecarga del operador '<<' para imprimir de manera mas clara una matriz
     *
     */
    ostream& operator<<(ostream &output, const vector<vector<double>> &matrix)
    {
        int size = matrix[0].size();
        for(int i {0}; i < size; i++) {
            for(int j {0}; j < size; j++) {
                output << matrix[i][j] << " ";
            }
            output << endl;
        }
        return output;
    }

    /**
     *
     * Sobrecarga del operador '<<' para imprimir de manera mas clara un vector
     *
     */
    ostream& operator<<(ostream &output, const vector<double> &vec)
    {
        for(int i {0}; i < vec.size(); i++) {
            output << vec[i] << " ";
        }
        return output;
    }
    
    /**
     * Funcion que determina si una matriz es predominante diagonal.
     * @param matrix: Matriz cuadrada.
     * @return: 'true' si la matriz es predominante diagonal, 'false' en caso contrario.
     */
    bool is_diagonal(const vector<vector<double>> &matrix) {
        short size = matrix[0].size(); // tamaño de la matriz}
        double current_diagonal_element = 0.0; // valor del elemento de la diagonal en esta iteracion
        double current_column_sum = 0.0; // sumatoria de los elementos de la misma fila
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                current_diagonal_element = matrix[i][i]; 
                if(j != i) {
                    current_column_sum += matrix[i][j];
                }
            }
            if(abs(current_diagonal_element) >= abs(current_column_sum)) return true;
        }

        return false;
    }
}

#endif
