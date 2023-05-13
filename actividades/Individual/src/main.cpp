#include <iostream>
#include <ctime>
#include "muller.h"
#include "ridders.h"

using namespace std;

void exec_muller(double x1, double x2) {
    unsigned t0 = clock();

    muller::muller(x1, x2);
    
    unsigned t1 = clock();

    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "-------------- Execution Time: " << time << " seconds" << endl;
}

void exec_ridders(double x1, double x2) {
    unsigned t0 = clock();

    ridders::ridders(x1, x2);
    
    unsigned t1 = clock();

    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "-------------- Execution Time: " << time << " seconds" << endl;
}

int main () {
    cout << "Running Muller method ..." << endl;
    exec_muller(1.2, 0.0);

    cout << "Running Ridders method ..." << endl;
    exec_ridders(0.0, 1.2);

    return 0;
}
