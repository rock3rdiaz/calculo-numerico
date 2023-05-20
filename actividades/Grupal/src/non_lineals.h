/**
 *
 * @brief      Este archivo contiene la implementacion del metodo solicitado en la actividad.
 *             Hace uso de los archivos proporcionados en el tema5 de la asignatura.
 *             Solamente adicionamos unos header guards y nombres de dominio para evitar
 *             referencias ciclicas o redefiniciones de los mismos metodos.
 *
 * @author     Roger.diaz, Alicia.arellano, Ivan.santiago
 * @date       2023
*/

#include <cmath>
#include <array>
#include "lu.h"
#include "sustitucion.h"
#include "norma_l1.h"
#include "inversion.h"

#ifndef NON_LINEALS_H
#define NON_LINEALS

using namespace std;
using namespace sustitucion;
using namespace norma_l1;
using namespace inversion;
using namespace lu;

const double e0 { 1.0e-14 }; // valor de tolerancia

namespace non_lineals {


    /**
     *
     * Metodo que regresa F(x) evaluado en los puntos dados.
     * El parametro de salida 'o_fs' almacena F(x, y)
     *
     */
    void fx(const double &x, const double &y, array<double, 2> &o_fs) {
        o_fs[0] = pow(x, 2) + (x * pow(y, 3)) - 9;
        o_fs[1] = (3 * pow(x, 2) * y) - pow(y, 3) - 4;
    }

    /**
     * Metodo que evalua el jacobiano del sistema de ecuaciones 
     * en los puntos dados.
     * El parametro de salida 'o_jfs' almacena JF(x, y).
     *
     */
    void jfx(const double &x, const double &y, array<array<double, 2>, 2> &o_jfs) {
        o_jfs[0][0] = 2 * pow(x, 2) + pow(y, 3);
        o_jfs[0][1] = 3 * x * pow(y, 2);
        o_jfs[1][0] = 6 * x * y;
        o_jfs[1][1] = 3 * pow(x, 2) - 3 * pow(y, 2);
    }

    /**
     * Funcion definida en la actividad.
     * Recibe el punto x0 = (x, y) que sera la aproximacion inicial. 
     *
     */
    void Newton_nD(array<double, 2> &initial_approx) {
        array<double, 2> _fx { 0.0, 0.0 }; // referencia a F(x0)
        array<array<double, 2>, 2> _jfx { { { 0.0, 0.0 }, { 0.0, 0.0 } } }; // referencia a JF(X0)
        
        // Declaramos la matriz A como un vector de vectores (2x2)
        vector<vector<double>> A (2, vector<double>(2));
        
        // Definimos el vector de terminos independientes
        vector<double> w = { 9.0, 4.0 };
        
        // Vector de permutaciones y determinante
        vector<int> perm(2);
        double det;

        // Inicializamos A
        A[0][0] = 1.0; A[0][1] = 1.0;
        A[1][0] = 3.0; A[1][1] = -1.0;

        while (abs(_fx[0]) > e0 and abs(_fx[1]) > e0) {
            double norma_A = norma_l1::norma_l1(A);

            // Descomposicion LU
            lu::lu(A, perm, det);
            
            // Resolucion del sistema de ecuaciones
            sustitucion::sustitucion(A, perm, w);
            
            // Inversion de A
            inversion::inversion(A, perm);

            // Calculamos la norma L1 de la inversa de A
            double norma_A_inv = norma_l1::norma_l1(A);

            // Obtenemos el numero de condicion
            double numero_de_condicion = norma_A * norma_A_inv;

            cout << "Numero de condicion: C(A) = " << numero_de_condicion << endl;
            cout << "Solucion con A: (x = " << w[0] << ", y = " << w[1] << ")" << endl;
 
            fx(initial_approx[0], initial_approx[1], _fx);
            jfx(initial_approx[0], initial_approx[1], _jfx);
        }

        cout << "F(x0) = {" << " x: " << _fx[0] << ", y: " << _fx[1] << " }" << endl;
        cout << "JF(x0) = {" << " x00: " << _jfx[0][0] << ", y01: " << _jfx[0][1]  << ", x10: " << _jfx[1][0] << ", y11: " << _jfx[1][1] << "}" << endl;
    }
}

#endif
