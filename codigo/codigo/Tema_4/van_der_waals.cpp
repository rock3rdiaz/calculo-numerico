// Calculo numerico: Tema 4 / van_der_waals.cpp

#include "laguerre.h"
#include "biseccion.h"

// Constantes globales
const double a = 1.390; // Parametro ec. van der Waals (depende del gas)
const double b = 0.03913; // Parametro ec. van der Waals (depende del gas)
const double R = 0.08206; // Constante universal de los gases
						  //
const double Tc = 8.0 * a / (27.0 * R * b); // Temperatura critica
const double Pc = a / (27.0 * b * b); // Presion critica

const double T = 128.0; // Temperatura (K) < Tc

// Funcion que resuelve para V la ec. de van der Waals con T fija (isoterma)
// Las raices (Va, Vc, Ve) obtenidas son los puntos de interseccion de la isoterma con la horizontal (P constante)
void calculo_puntos_interseccion(double P, double &Va, double &Vc, double &Ve)
{
	// Vector de coeficientes del polinomio (ec. de van der Waals)
	vector<complex<double>> coefs {
			complex<double> (-a * b, 0.0),
			complex<double> (a, 0.0),
			complex<double> (-b * P - R * T, 0.0),
			complex<double> (P, 0.0)
	};

	// Grado del polinomio
	int n = coefs.size() - 1;

	// Vector de raices del polinomio (puntos de interseccion)
	vector<complex<double>> raices(n);

	// Numero de iteraciones
	vector<int> its (n, 0);

	// Calculamos las raices
	laguerre_driver(coefs, raices, true, its);

	// Puntos de interseccion
	Va = raices[0].real();
	Vc = raices[1].real();
	Ve = raices[2].real();
}

// Funcion que obtiene el area que deseamos hacer cero
// Depende de Va, Vc, Ve y P para una T fija
double area(double P)
{
	double Va, Vc, Ve;

	calculo_puntos_interseccion(P, Va, Vc, Ve);

	return R * T * log((Ve - b) / (Va - b)) + a * (1.0 / Ve - 1.0 / Va) - P * (Ve - Va);
}

// Funcion principal
int main()
{
	// Intervalo de acotamiento
	double P1 = Pc / 2.0, P2 = Pc, P;

	// Ajustamos P1 hasta encontrar el intervalo que contenga la raiz
	while (area(P1) < 0.0) P1 /= 2.0;

	int its = 0, error;

	// Buscamos la raiz
	biseccion(P1, P2, &area, P, its, error);

	double Va, Vc, Ve;

	// Obtenemos Va, Vc y Ve tras hallar la raiz
	calculo_puntos_interseccion(P, Va, Vc, Ve);

	// Temperaturas
	cout << "Temperatura: T = " << T << endl;
	cout << "Temperatura critica: Tc = " << Tc << endl;

	// Resultados
	cout << "Presion de coexistencia: P = " << P << endl;
	cout << "Intersecciones con la isoterma:" << endl;
	cout << "Va = " << Va << endl;
	cout << "Vc = " << Vc << endl;
	cout << "Ve = " << Ve << endl;

	return 0;
}
