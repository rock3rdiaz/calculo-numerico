#include <iostream>
#include <array>
#include "non_lineals.h"
#include "norma_l1.h"
#include "inversion.h"
#include "sustitucion.h"
#include "lu.h"

using namespace std;
using namespace non_lineals;
using namespace norma_l1;
using namespace sustitucion;
using namespace inversion;
using namespace lu;


int main() {

    const double e0 { 1.0e-14 }; // valor de tolerancia
    
    /*
    // Declaramos la matriz A como un vector de vectores (2x2)
	vector<vector<double>> A (2, vector<double>(2));

	// Inicializamos A
	A[0][0] = 1.0; A[0][1] = 1.0;
	A[1][0] = 3.0; A[1][1] = -1.0;
    
    double norma_A = norma_l1::norma_l1(A);

    // Definimos el vector de terminos independientes
	vector<double> w = { 9.0, 4.0 };

    // Vector de permutaciones y determinante
	vector<int> perm(2);
	double det;

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
    */

    array<double, 2> x0 = { 1.0, 1.0 };
    non_lineals::Newton_nD(x0, e0);

    return 0;
}
