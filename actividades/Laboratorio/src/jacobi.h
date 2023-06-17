#ifndef JACOBI_H
#define JACOBI_H

#include <iostream>
#include "utils.h"
#include <algorithm>

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
        double size_A = A.size();
        
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
        cout << "Descomposicion de la matriz A: " << endl;
        cout << "=> M: " << endl;
        cout << M << endl;
        cout << "=> N: " << endl;
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
    * metodo de Jacobi.
    *
    * @param A: Referencia a la matriz cuadrada del sistema.
    * @param b: Referencia al vector de terminos independientes.
    * @param tolerance: Tolerancia del algoritmo.
    * @return Codigo de salida de la ejecucion del programa. 0 ok, cualquier otro valor sera un error.
    *
    */
    int jacobi(const vector<vector<double>> &A, const vector<double> &b, double tolerance) {
        if(!is_diagonal(A)) {
            cout << "La matriz A no es predominante diagonal" << endl;
            return -1;
        }

        double size_A = A.size();

        vector<vector<double>> M = A;
        vector<vector<double>> N = A;
        vector<vector<double>> solutions = get_x0(size_A); // vector de soluciones x_l y x_l+1

        get_decomposition(A, M, N); // Ejecutamos la descomposicion de A en M y N
        
        short iter {0};
        double solutions_norm = get_euclideam_norm(solutions[0], solutions[1]); 
        do {
            for(int i {0}; i < size_A; i++) {
                double next_value; // valor del i-esimo elemento de la solucion para la siguiente iteracion.
                double sum_N = 0.0; // sumatoria de los valores fuera de la diagonal en esta iteracion
                for(int j {0}; j < size_A; j++) {
                    if(j != i) {
                       sum_N += N[i][j] * solutions[0][j];
                    }
                }
                next_value = (1 / M[i][i]) * (b[i] - sum_N);
                solutions[1][i] = next_value;
            }
            
            solutions_norm = get_euclideam_norm(solutions[0], solutions[1]);
            solutions[0] = solutions[1]; // se define x_l+1 como el nuevo x_l

            iter++;
        } while(tolerance <= solutions_norm);

        cout << "---------------------------------" << endl;
        cout << "Soluciones encontradas con la tolerancia establecida: " << endl;
        cout << "[ " << solutions[1] << "]" << endl;
        cout << "Se requirieron " << iter << " iteraciones." << endl;
        cout << "---------------------------------" << endl;

        return 0;
    } 
}

#endif
