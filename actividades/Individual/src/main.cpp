#include <ctime>
#include <iostream>
#include "biseccion.h"
#include "muller.h"
#include "ridders.h"
#include "regula_falsi.h"
#include "newton_raphson.h"
#include "constants.h"

using namespace std;
using namespace constants;
using namespace regula_falsi;
using namespace biseccion;
using namespace newton_raphson;

void exec_biseccion(double x1, double x2) {
  cout << "------------- Running Bisection method ..." << endl;

  unsigned t0 = clock();

  double x3 = 0.0;
  int its = 0;
  int error = -2;
  while (error == -2 && its < MAX_ITERATIONS)
      biseccion::biseccion(x1, x2, x3, its, error);

  cout << "Its\tx1\t\t\tx2\t\t\tx3" << endl;
  cout << its << '\t' << x1 << '\t' << x2 << '\t' << x3 << endl;

  unsigned t1 = clock();

  double time = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "-------------- Execution Time: " << time << " seconds" << endl;
}


void exec_regula_falsi(double x1, double x2) {
  cout << "------------- Running Regula-Falsi method ..." << endl;

  unsigned t0 = clock();

  double x3 = 0.0;
  int its = 0;
  int error = -2;

  while (error == -2 && its < MAX_ITERATIONS)
    regula_falsi::regula_falsi(x1, x2, x3, its, error);

  cout << "Its\tx1\t\t\tx2\t\t\tx3" << endl;
  cout << its << '\t' << x1 << '\t' << x2 << '\t' << x3 << endl;

  unsigned t1 = clock();

  double time = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "-------------- Execution Time: " << time << " seconds" << endl;
}

void exec_newton_raphson(double x1, double x2) {
  cout << "------------- Running Newton-Raphson method ..." << endl;

  unsigned t0 = clock();

  double x3 = 0.0;
  int its = 0;
  int error = -2;
  while (error == -2 && its < MAX_ITERATIONS)
    newton_raphson::newton_raphson(x1, x2, x3, its, error);

  cout << "Its\tx1\t\t\tx2\t\t\tx3" << endl;
  cout << its << '\t' << x1 << '\t' << x2 << '\t' << x3 << endl;
  
  unsigned t1 = clock();

  double time = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "-------------- Execution Time: " << time << " seconds" << endl;
}

void exec_muller(double x1, double x2) {
  cout << "------------- Running Muller method ..." << endl;

  unsigned t0 = clock();

  muller::muller(x1, x2);

  unsigned t1 = clock();

  double time = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "-------------- Execution Time: " << time << " seconds" << endl;
}

void exec_ridders(double x1, double x2) {
  cout << "------------- Running Ridders method ..." << endl;

  unsigned t0 = clock();

  ridders::ridders(x1, x2);

  unsigned t1 = clock();

  double time = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "-------------- Execution Time: " << time << " seconds" << endl;
}

int main() {
  cout << "Iniciando ejecucion de los metodos ..." << endl;

  cout.precision(15);
  
  // rango que acota la raiz de la funcion
  double x1 = 0.0;
  double x2 = 1.2;

  exec_biseccion(x1, x2);

  cout << endl;

  exec_regula_falsi(x1, x2);

  cout << endl;

  exec_newton_raphson(x1, x2);

  cout << endl;

  exec_muller(x2, x1);

  cout << endl;

  exec_ridders(x1, x2);

  cout << "Ejecucion finalizada ..." << endl;

  return 0;
}
