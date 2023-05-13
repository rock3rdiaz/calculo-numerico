// Calculo Numerico: Tema 2 / cuenta_atras_while.cpp
// Incluimos la cabezera para usar cout y endl
#include <iostream>
using namespace std;
int main()
{
    // Inicializamos la variable-contador
    int n = 10;
    // Bucle while: itera mientras la condicion n > 0 se cumpla
    while (n > 0)
    {
        // Mostramos el contador en pantalla
        cout << n << ", ";
        // Disminuimos el contador en una unidad
        --n;
    }
    // En este punto hemos salido del bucle (n vale 0). Se produce el despegue.
    cout << "despegue!" << endl;
    return 0;
}
