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

const double e0 { 0.0e-14 }; // valor de tolerancia

namespace non_lineals {

    /**
     *
     * Metodo que regresa F(x) evaluado en los puntos dados.
     * El parametro de salida 'o_fs' almacena F(x, y)
     *
     */
    void fx(array<double, 2> &p, array<double, 2> &o_fs) {
        o_fs[0] = pow(p[0], 2) + (p[0] * pow(p[1], 3)) - 9;
        o_fs[1] = (3 * pow(p[0], 2) * p[1]) - pow(p[1], 3) - 4;
    }

    /**
     * Metodo que evalua el jacobiano del sistema de ecuaciones 
     * en los puntos dados.
     * El parametro de salida 'o_jfs' almacena JF(x, y).
     *
     */
    void jfx(array<double, 2> &p, vector<vector<double>> &o_jfs) {
        o_jfs[0][0] = (2 * p[0]) + (pow(p[1], 3));
        o_jfs[0][1] = 3 * p[0] * pow(p[1], 2);
        o_jfs[1][0] = 6 * p[0] * p[1];
        o_jfs[1][1] = (3 * pow(p[0], 2)) - (3 * pow(p[1], 2));
    }

    /**
     * Funcion definida en la actividad.
     * Recibe el punto x0 = (x, y) que sera la aproximacion inicial. 
     *
     */
    void Newton_nD(array<double, 2> &initial_approx) {
        array<double, 2> _fx { 0.0, 0.0 }; // referencia a F(x0)
        vector<vector<double>> _jfx (2, vector<double>(2)); // referencia a JF(x0)
        vector<double> w (2); // Definimos el vector de terminos independientes
        
        // Vector de permutaciones y determinante
        vector<int> perm(2);
        double det;

        short iter = 1;

        do {
            fx(initial_approx, _fx);
            jfx(initial_approx, _jfx);

            cout << "Iniciando la iteracion " << iter << " con la aproximacion (" << initial_approx[0] << ", " << initial_approx[1] << ")" << endl;
            cout << "F(x0) = ( " << _fx[0] << "\t" << _fx[1] << " )" << endl;
            cout << "JF(x0) = ( " << _jfx[0][0] << "\t" << _jfx[0][1] << " ; " << _jfx[1][0] << "\t" << _jfx[1][1] << ")" << endl;
        
            w[0] = -1 * _fx[0];
            w[1] = -1 * _fx[1];

            // Descomposicion LU
            lu::lu(_jfx, perm, det);
            
            // Resolucion del sistema de ecuaciones
            sustitucion::sustitucion(_jfx, perm, w);
            
            cout << "Solucion con w = ( " << w[0] << "\t" << w[1] << " )" << endl;
            cout << "\n" << endl;

            initial_approx[0] += w[0];
            initial_approx[1] += w[1];

            iter++;
        } while (abs(_fx[0]) > e0 and abs(_fx[1]) > e0);
    }
}

#endif
