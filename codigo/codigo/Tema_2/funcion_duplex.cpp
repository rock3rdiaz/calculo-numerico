// Calculo Numerico: Tema 2 / funcion_duplex.cpp

#include <iostream>

using namespace std;

// Funcion duplex: duplica el valor de sus argumentos
// Primer argumento: pasado por referencia
// Segundo argumento: pasado por valor
void duplex(int& a, int b)
{
	a *= 2;
	b *= 2;
}

int main()
{
	int x = 2, y = 3;

	duplex(x, y);

	cout << "x = " << x << endl;
	cout << "y = " << y << endl;

	return 0;
}
