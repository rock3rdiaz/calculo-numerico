#ifndef RELAJACION_H
#define RELAJACION_H

#include <iostream>
#include "utils.h"
#include <algorithm>

using namespace std;
using namespace utils;

namespace relajacion {
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
    int relajacion(const vector<vector<double>> &A, const vector<double> &b, double tolerance) {
        cout << "++++++++++++++++++++++++ Metodo Gauss-Seidel con relajacion ++++++++++++++++++" << endl;

        if(!is_diagonal(A)) {
            cout << "La matriz A no es predominante diagonal" << endl;
            return -1;
        }

        double size_A = A.size();

        vector<vector<double>> A1 = A;
        vector<vector<double>> A2 = A;

        get_decomposition(A, A1, A2); // Ejecutamos la descomposicion de A en A1 y A2

        short iter {0}; // numero de iteraciones

        vector<double> solution(size_A, 0.0); // almacenara los valores de la iteracion actual
        double new_value {0.0}; // nuevo valor de la solucion
        double diff {0.0}; // diferencia entre las dos ultimas soluciones 

        do {
            for(int i {0}; i < size_A; i++) {
                double sum = 0.0;
            
                for(int j {0}; j < size_A; j++) {
                    if(j != i) {
                        sum += A[i][j] * solution[j];
                    }
                }
                new_value = (1 / A[i][i]) * (b[i] - sum);
                diff = abs(new_value - solution[i]); // calculo de la diferencia entre las soluciones
                solution[i] = new_value;

            }

            iter++;

        } while(tolerance < diff);

        cout << "---------------------------------" << endl;
        cout << "Soluciones encontradas con la tolerancia establecida: " << endl;
        cout << "[ " << solution << "]" << endl;
        cout << "Se requirieron " << iter << " iteraciones." << endl;
        cout << "---------------------------------" << endl;
     
        return 0;
    } 
}

#endif
