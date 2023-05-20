#include <iostream>
#include <ctime>
#include <array>
#include "non_lineals.h"

using namespace std;
using namespace non_lineals;

int main() {

    unsigned t0 = clock();

    cout << "Iniciando proceso ..." << endl;

    array<double, 2> x0 = { 1.0, 1.0 }; // aproximacion incial

    non_lineals::Newton_nD(x0); // invocacion del metodo principal

    unsigned t1 = clock();

    double time_elapsed = (double(t1 - t0) / CLOCKS_PER_SEC);

    cout << "Proceso finalizado. Tiempo de procesamiento: " << time_elapsed << " segundos" << endl;

    return 0;
}
