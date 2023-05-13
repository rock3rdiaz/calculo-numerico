// Calculo Numerico: Tema 2 / cuenta_atras_incompleta.cpp
#include <iostream>
using namespace std;
int main()
{
    // Bucle for que realiza la cuenta atras
    for (int n = 10; n > 0; n--)
    {
        // Saltamos a la siguiente iteracion si n vale 3
        if (n == 3) continue;
        cout << n << ", ";
    }
    cout << "despegue!" << endl;
    return 0;
}
