#include <cmath>
#include <array>
#include "lu.h"
#include "sustitucion.h"

#ifndef NON_LINEALS_H
#define NON_LINEALS

using namespace std;
using namespace lu;
using namespace sustitucion;

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
     * Recibe un puntero a la funcion con la definicion del sistema, el jacobiano del sistema,
     * el valor de tolerancia y una primera aproximacion de la solucion.
     *
     */
    void Newton_nD(array<double, 2> &initial_approx, const double &e0){
        array<double, 2> _fx { 0.0, 0.0 };
        array<array<double, 2>, 2> _jfx { { { 0.0, 0.0 }, { 0.0, 0.0 } } };
        fx(initial_approx[0], initial_approx[1], _fx);
        jfx(initial_approx[0], initial_approx[1], _jfx);

        cout << "F(x0) = {" << " x: " << _fx[0] << ", y: " << _fx[1] << " }" << endl;
        cout << "JF(x0) = {" << " x00: " << _jfx[0][0] << ", y01: " << _jfx[0][1]  << ", x10: " << _jfx[1][0] << ", y11: " << _jfx[1][1] << "}" << endl;

    }

}

#endif
