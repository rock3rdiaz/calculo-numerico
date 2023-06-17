#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include <iostream>
#include <algorithm>
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
        double size_A = A.size();
        
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
        cout << A1 << endl;
        cout << "=> A2: " << endl;
        cout << A2 << endl;
        cout << "---------------------------------" << endl;
    }

     /* Metodo que genera la primera aproximacion de la solucion.
     *
     * @param initial_approx: Referencia al vector solucion.
     * @param size: Tamaño del vector solucion.
     *
     */
    vector<vector<double>> get_x0(int size) {
        vector<vector<double>> x0(2, vector<double>(size, 0.0));

        cout << "---------------------------------" << endl;
        cout << "Generacion de la aproximacion inicial: " << endl;
        cout << "=> x_l: " << endl;
        cout << x0[0] << endl;
        cout << "=> x_l+1: " << endl;
        cout << x0[1] << endl;
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

        double size_A = A.size();

        vector<vector<double>> A1 = A;
        vector<vector<double>> A2 = A;

        get_decomposition(A, A1, A2); // Ejecutamos la descomposicion de A en A1 y A2

        short iter {0};

        vector<double> current_iteration(size_A, 0.0); // almacenara los valores de la iteracion actual
        vector<double> next_iteration(size_A, 0.0); // almacenara los valores de la siguiente iteracion

        double solutions_norm = get_euclideam_norm(next_iteration, current_iteration); 
        do {
            for(int i {0}; i < size_A; i++) {
                double next_value; // valor del i-esimo elemento de la solucion.
                double current_iteration_sum; // sumatoria de los valores de la solucion actual (x_l)
                double next_iteration_sum; // sumatoria de los valores de la siguiente iteracion (x_l+1)
            
                for(int j {0}; j < size_A; j++) {
                    if(j != i) {
                        next_iteration_sum += A[i][j] * next_iteration[j] * current_iteration[j];
                    }
                }

                next_value = (1 / A1[i][i]) * (b[i] - next_iteration_sum);
                next_iteration[i] = next_value;
            }

            solutions_norm = get_euclideam_norm(next_iteration, current_iteration);

            iter++;

        } while(iter < 100);

        cout << "---------------------------------" << endl;
        cout << "Soluciones encontradas con la tolerancia establecida: " << endl;
        cout << "[ " << next_iteration << "]" << endl;
        cout << "Se requirieron " << iter << " iteraciones." << endl;
        cout << "---------------------------------" << endl;
     
        return 0;
    } 
}

#endif
