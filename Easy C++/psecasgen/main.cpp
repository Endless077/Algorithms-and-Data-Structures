
#include <iostream>

// Random generation a la C
#include <stdlib.h>
#include <time.h>

// // Random generation a la C++
// #include <random>

using namespace std;

int main() {

  // Random generation a la C
  srand(time(NULL));
  for(uint i = 0; i < 15; i++) { cout << rand() << " "; }; cout << endl;
  // for(uint i = 0; i < 15; i++) { cout << 85 + rand() % 25 << " "; }; cout << endl;

  // for(uint i = 0; i < 15; i++) { cout << rand() << " "; }; cout << endl;

  // // Random generation a la C++
  // default_random_engine genx(random_device{}());
  // uniform_int_distribution<uint> distx(7, 35);
  // for(uint i = 0; i < 15; i++) { cout << distx(genx) << " "; }; cout << endl;

  return 0;
}
