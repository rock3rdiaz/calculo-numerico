// Calculo numerico: Tema 3 / taylor4.cpp

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout.precision(7);
    cout.setf(ios::scientific);

    const float epsilon = 1.0e-7;

    cout << "x\t\texp(x)\t\tSerie\t\t|Error rel.|\tNum. Terms." << endl;
    
    for (float x = -15.0; x <= 15.0; x++)
    {
        float y = fabs(x);

        int n = 0;
        float termino = 1.0;
        float serie = 1.0;

        while (termino > epsilon)
        {
            n++;
            termino *= y / n;
            serie += termino;
        }

        if (x < 0.0)
            serie = 1.0 / serie;

        cout << x << '\t' << exp(x) << '\t' << serie << '\t' << fabs((exp(x) - serie) / exp(x)) << '\t' << n << endl;
    }

    return 0;
}
