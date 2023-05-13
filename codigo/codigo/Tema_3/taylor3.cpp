// Calculo numerico: Tema 3 / taylor3.cpp

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    // Establecemos la precision y tipo de notacion numerica de cout
    cout.precision(7);
    cout.setf(ios::scientific);

    const double epsilon = 1.0e-7; // Precision
    
    double x = 10.0; // Calculamos la serie en el valor x

    int n = 0; // Numero del termino
    
    // Definimos dos tipos de variables (float y double) para calcular terminos y serie, comparando los resultados
    float termino32 = 1.0; // Termino inicial: n = 0
    double termino64 = 1.0;

    float serie32 = 1.0;
    double serie64 = 1.0;

    cout << "x = " << x << "\texp(-x) = " << exp(-x) << endl;
    cout << "N\tTermino 32bit\tTermino 64bit\tSerie 32bit\tSerie 64bit\t|Erel| 32bit\t|Erel| 64bit" << endl;

    // Iteramos hasta que el error (termino de corte) sea menor que epsilon
    while (fabs(termino64) > epsilon)
    {
        n++;

        termino32 *= x / n;
        serie32 += termino32;

        termino64 *= x / n;
        serie64 += termino64;
        
        float error_rel_32 = fabs((exp(-x) - 1.0 / serie32) / exp(-x)); // Error relativo
        double error_rel_64 = fabs((exp(-x) - 1.0 / serie64) / exp(-x));

        cout << n << '\t' << termino32 << '\t' << termino64 << '\t' << 1.0 / serie32 << '\t' << 1.0 / serie64 << '\t' << error_rel_32 << '\t' << error_rel_64 << endl;
    }

    return 0;
}
