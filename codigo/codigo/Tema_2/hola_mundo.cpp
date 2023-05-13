// Calculo Numerico: Tema 2 / hola_mundo.cpp

// Incluimos las cabeceras necesarias...
#include <iostream> // ...para poder usar cout y endl
#include <vector> // ...para poder usar vector
#include <string> // ...para poder usar string

// Hacemos los nombres del espacio de nombres std accesibles directamente
using namespace std;

// Funcion principal
int main()
{
    // Inicializamos el mensaje como vector de strings con varias palabras
    vector<string> mensaje {"Hola", "mundo", "del", "calculo", "numerico!"};

    // Iteramos con un bucle sobre las palabras del mensaje
    for (string palabra : mensaje)
    {
        // Mostramos una palabra en la pantalla
        cout << palabra << " ";
    }
    // Finalizamos la linea
    cout << endl;

    // La funcion devuelve el valor 0 (exito)
    return 0;
}
