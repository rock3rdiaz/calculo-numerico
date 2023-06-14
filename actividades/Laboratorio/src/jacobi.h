#ifndef JACOBI_H
#define JACOBI_H

#include <iostream>
#include "utils.h"

using namespace std;
using namespace utils;

namespace jacobi {
    /**
    *
    * Metodo que ejecuta la descomposicion de la matriz en sus matrices M y N.
    * @param A: Referencia a la matriz original
    * @param M: Matriz M tras la descomposicion
    * @param N: Matriz N tras la descomposicion
    *
    */
    void get_decomposition(const vector<vector<double>> &A, vector<vector<double>> &M, 
            vector<vector<double>> &N) {
        double size_A = A[0].size();
        
        for(int i {0}; i < size_A; i++) {
            for(int j {0}; j < size_A; j++) {
                if(i != j) {
                    M[i][j] = 0.0;
                } else {
                    N[i][j] = 0.0;
                }
            }
        }

        cout << "---------------------------------" << endl;
        cout << "1. Descomposicion de la matriz A: " << endl;
        cout << "=> M: " << endl;
        cout << M << endl;
        cout << "=> N: " << endl;
        cout << N << endl;
        cout << "---------------------------------" << endl;
    }

    /**
     * Metodo que genera la primema aproximacion de la solucion.
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
    * metodo de Jacobi.
    *
    * @param A: Referencia a la matriz cuadrada del sistema.
    * @param b: Referencia al vector de terminos independientes.
    * @param tolerance: Tolerancia del algoritmo.
    * @return Codigo de salida de la ejecucion del programa. 0 ok, cualquier otro valor sera un error.
    *
    */
    int jacobi(const vector<vector<double>> &A, const vector<double> &b, double tolerance) {
        double size_A = A[0].size();

        vector<vector<double>> M = A;
        vector<vector<double>> N = A;
        vector<double> solution = get_x0(size_A); // vector de soluciones

        if(!is_diagonal(A)) {
            cout << "La matriz A no es predominante diagonal" << endl;
            return -1;
        }

        get_decomposition(A, M, N); // Ejecutamos la descomposicion de A en M y N
        
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
        cout << "=> solution: " << endl;
        cout << solution << endl;
        cout << "---------------------------------" << endl;

        return 0;
    } 
}

#endif