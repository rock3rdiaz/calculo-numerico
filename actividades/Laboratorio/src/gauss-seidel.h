#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include <iostream>
#include "utils.h"

using namespace std;
using namespace utils;

namespace gauss_seidel {
    /**
    *
    * Metodo que ejecuta la descomposicion de la matriz en sus matrices A1 y A2.
    * @param A: Referencia a la matriz original
    * @param A1: Matriz A1 tras la descomposicion
    * @param A2: Matriz A2 tras la descomposicion
    *
    */
    void get_decomposition(const vector<vector<double>> &A, vector<vector<double>> &A1, 
            vector<vector<double>> &A2) {
        double size_A = A[0].size();
        
        for(int i {0}; i < size_A; i++) {
            for(int j {0}; j < size_A; j++) {
                if(j > i) {
                    A1[i][j] = 0.0;
                } else {
                    A2[i][j] = 0.0;
                }
            }
        }

        cout << "---------------------------------" << endl;
        cout << "1. Descomposicion de la matriz A: " << endl;
        cout << "=> A1: " << endl;
        cout << M << endl;
        cout << "=> A2: " << endl;
        cout << N << endl;
        cout << "---------------------------------" << endl;
    }

    /**
     * Metodo que genera la primera aproximacion de la solucion.
     *
     * @param initial_approx: Referencia al vector solucion.
     * @param size: Tamaño del vector solucion.
     *
     */
    vector<double> get_x0(int size) {
        vector<double> x0(size, 0.0);

        cout << "---------------------------------" << endl;
        cout << "2. Generacion de la aproximacion inicial: " << endl;
        cout << "=> x0: " << endl;
        cout << x0 << endl;
        cout << "---------------------------------" << endl;

        return x0;
    }

    /**
    *
    * Metodo que calcula la solucion de un sistema de la forma Ax = b usando el 
    * metodo de Gauss-Seidel.
    *
    * @param A: Referencia a la matriz cuadrada del sistema.
    * @param b: Referencia al vector de terminos independientes.
    * @param tolerance: Tolerancia del algoritmo.
    * @return Codigo de salida de la ejecucion del programa. 0 ok, cualquier otro valor sera un error.
    *
    */
    int gauss_seidel(const vector<vector<double>> &A, const vector<double> &b, double tolerance) {
        if(!is_diagonal(A)) {
            cout << "La matriz A no es predominante diagonal" << endl;
            return -1;
        }

        double size_A = A[0].size();

        vector<vector<double>> A1 = A;
        vector<vector<double>> A2 = A;
        vector<double> solution = get_x0(size_A); // vector de soluciones

        get_decomposition(A, A1, A2); // Ejecutamos la descomposicion de A en A1 y A2
        
        for(int i {0}; i < size_A; i++) {
            double next_value; // valor del i-esimo elemento de la solucion.
            double sum_N; // sumatoria de los valores fuera de la diagonal en esta iteracion
            for(int j {0}; j < size_A; j++) {
                if(j != i) {
                    sum_N = N[i][j] * solution[j];
                }
            }
            next_value = (1 / M[i][i]) * (b[i] - sum_N);
            solution[i] = next_value;
        }

        cout << "---------------------------------" << endl;
        cout << "3. Soluciones aproximadas: " << endl;
        cout << solution << endl;
        cout << "---------------------------------" << endl;

        return 0;
    } 
}

#endif
