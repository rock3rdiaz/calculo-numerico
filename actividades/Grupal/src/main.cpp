#include <iostream>
#include <iomanip>
#include <ctime>
#include <array>
#include "non_lineals.h"

using namespace std;
using namespace non_lineals;

int main() {

    std::setprecision(15);

    unsigned t0 = clock();

    cout << "------ Iniciando proceso ...\n" << endl;

    array<double, 2> p = { -1.0, -2.0 }; // aproximacion incial

    non_lineals::Newton_nD(p); // invocacion del metodo principal

    unsigned t1 = clock();

    double time_elapsed = (double(t1 - t0) / CLOCKS_PER_SEC);

    cout << "Se ha encontrado la raiz (valor aproximado) => (" << p[0] << ", " << p[1] << ")\n" << endl;
    cout << "------ Proceso finalizado. Tiempo de procesamiento: " << time_elapsed << " segundos" << endl;

    return 0;
}
