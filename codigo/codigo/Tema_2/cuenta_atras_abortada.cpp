// Calculo Numerico: Tema 2 / cuenta_atras_abortada.cpp
#include <iostream>
using namespace std;
int main()
{
    // Bucle for que realiza la cuenta atras
    for (int n = 10; n > 0; n--)
    {
        cout << n << ", ";
        // Cuando hayamos contado hasta 5...
        if (n == 5)
        {
            cout << "cuenta atras abortada!" << endl;
            // ...abortamos la cuenta atras
            break;
        }
    }
    return 0;
}