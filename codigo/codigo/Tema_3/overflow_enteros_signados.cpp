// Calculo Numerico: Tema 3 / overflow_enteros_signados.cpp

#include <iostream>
#include <limits>

using namespace std;

int main()
{
    // Mostramos informacion del tipo 'short int'
    // mediante el uso de las utilidades incluidas en <limits>

    cout << "Informacion sobre el tipo 'short int'" << endl;
    cout << "Numero de bits (sin signo): " << numeric_limits<short int>::digits << endl;
    cout << "Valor minimo representable: " << numeric_limits<short int>::min() << endl;
    cout << "Valor maximo representable: " << numeric_limits<short int>::max() << endl;
	
    // Inicializamos la variable x con el valor maximo representable

    short int x = numeric_limits<short int>::max();
    short int y = 1, z = 0;

    z = x + y; // En esta suma se produce un overflow
	
    cout << "x + y = " << x << " + " << y << " = " << z << endl;

    // Inicializamos la variable x con el valor minimo representable

    x = numeric_limits<short int>::min();
    y = 1; z = 0;
    
    z = x - y; // En esta resta se produce un overflow
	
    cout << "x - y = " << x << " - " << y << " = " << z << endl;

    return 0;
}