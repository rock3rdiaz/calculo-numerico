#include "romberg.h"
#include <cmath>

double seno(double x)
{
	return sin(x);
}

int main()
{
	const double pi = 4.0 * atan(1.0);

	double integral;
	double error = 1.0e-6;
	int kkk;

	romberg(seno, 0.0, pi, integral, error, kkk);

	if (kkk == 0)
	{
		cout << "Integral = " << integral << endl;
	}
	else
	{
		cout << "Error de convergencia!" << endl;
	}

	return 0;
}
