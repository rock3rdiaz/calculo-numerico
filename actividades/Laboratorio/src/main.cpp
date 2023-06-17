#include <iostream>
#include <ctime>
#include <iomanip>
#include "jacobi.h"
#include "lu.h"
#include "sustitucion.h"
#include "gauss_seidel.h"

using namespace std;
using namespace lu;
using namespace sustitucion;

int main() {

    cout.precision(10);

    vector<vector<double>> A = {{-4, 1, 0, 1, 0, 0, 0, 0, 0}, 
                                {1, -4, 1, 0, 1, 0, 0, 0, 0}, 
                                {0, 1, -4, 0, 0, 1, 0, 0, 0},
                                {1, 0, 0, -4, 1, 0, 1, 0, 0},
                                {0, 1, 0, 1, -4, 1, 0, 1, 0},
                                {0, 0, 1, 0, 1, -4, 0, 0, 1},
                                {0, 0, 0, 1, 0, 0, -4, 1, 0},
                                {0, 0, 0, 0, 1, 0, 1, -4, 1},
                                {0, 0, 0, 0, 0, 1, 0, 1, -4}};

    vector<double> b = {-120, 0, -30, -70, 0, -20, -290, -170, -160};

    double e0 {1e-10}; // valor de tolerancia

    unsigned t0 = clock();
    
    short code = jacobi::jacobi(A, b, e0);
    short code2 = gauss_seidel::gauss_seidel(A, b, e0);
    //short code = lu::execute_lu(A, b, e0);

    unsigned t1 = clock();

    double time_elapsed = (double(t1 - t0) / CLOCKS_PER_SEC);

    if(code == 0) {
        cout << "---------------------------------" << endl;
        cout << " Proceso finalizado con exito. Tiempo de ejecucion " << time_elapsed << " segundos." << endl;
        cout << "---------------------------------" << endl;
    }
}
