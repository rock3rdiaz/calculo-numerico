// Calculo numerico: Tema 3 / divisiones.cpp

#include <iostream>

using namespace std;

int main()
{
    int x = 2, y = 5, z = 7;

    int r1 = x / y;
    int r2 = z / y;
    int r3 = (x * y) / x; // El orden de las operaciones importa
    int r4 = x * (y / x); // Los parentesis reordenan las operaciones

    cout << "2 / 5 = " << r1 << endl;
    cout << "7 / 5 = " << r2 << endl;
    cout << "(2 * 5) / 2 = " << r3 << endl;
    cout << "2 * (5 / 2) = " << r4 << endl;

    return 0;
}