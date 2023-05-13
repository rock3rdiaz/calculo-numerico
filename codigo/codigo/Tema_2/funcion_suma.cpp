// Calculo Numerico: Tema 2 / funcion_suma.cpp

#include <iostream>

using namespace std;

// Funcion suma: devuelve el valor de la suma de dos enteros
int suma(int a, int b)
{
    return a + b;
}

int main()
{
    // Inicializamos la variable x con el valor devuelto por la funcion suma
    int x = suma(1, 6);

    cout << "x vale " << x << endl;

    // Inicializamos dos variables
    int m1 = 3;
    int m2 = 4;

    // Llamamos a la funcion suma usando las dos variables como parametros
    cout << m1 << " + " << m2 << " = " << suma(m1, m2) << endl;

    // Podemos operar con el valor devuelto por la funcion suma
    cout << "1 + 2 - 3 = " << suma(1, 2) - 3 << endl;

    return 0;
}
