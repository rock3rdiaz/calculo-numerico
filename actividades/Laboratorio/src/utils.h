#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <vector>
#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>

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

    /**
     *
     * Metodo que calcula las soluciones aproximadas en el sistema estudiado.
     * 
     * @param A: Referencia a la matriz de coeficientes
     * @param b: Referencia al vector de terminos independientes
     * @param solutions: Referencia al vector de soluciones aproximadas
     * @return Aproximacion a el resultado exacto
     */
    double get_fx(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &solutions) {
        short size = b.size();

        // error aproximado
        vector<double> fx_items;

        for(int i {0}; i < size; i++) {
            double fx_value = 0.0; // variable que almacena el valor de las operaciones en la fila actual
            for(int j {0}; j < size; j++) {
                fx_value += A[i][j] * solutions[j];
            }
            fx_items.push_back(abs(fx_value - b[i]));        
        }

        return accumulate(fx_items.begin(), fx_items.end(), 0.0);
    }
}

#endif
