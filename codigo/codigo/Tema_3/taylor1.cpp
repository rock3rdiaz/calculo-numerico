// Calculo numerico: Tema 3 / taylor1.cpp

#include <iostream>
#include <cmath>

using namespace std;

// Funcion recursiva
float factorial(float n)
{
    if (n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

int main()
{
    // Establecemos la precision y tipo de notacion numerica de cout
    cout.precision(7);
    cout.setf(ios::scientific);
    
    const float epsilon = 1.0e-7; // Precision

    float x = 9.0; // Calculamos la serie en el valor x

    int n = 0; // Numero del termino
    float termino = 1.0; // Termino inicial: n = 0
    float serie = 1.0;

    cout << "x = " << x << "\texp(-x) = " << exp(-x) << endl;
    cout << "n\tpow(-x, n)\tfactorial(n)\tTermino\t\tSerie\t\t|Error rel.|" << endl;

    // Iteramos hasta que el error (termino de corte) sea menor que epsilon
    while (fabs(termino) > epsilon)
    {
        n++;
        termino = pow(-x, n) / factorial(n);
        serie += termino;
        
        cout << n << '\t' << pow(-x, n) << '\t' << factorial(n) << '\t' << termino << '\t' << serie << '\t' << fabs((exp(-x) - serie) / exp(-x)) << endl;
    }

    return 0;
}