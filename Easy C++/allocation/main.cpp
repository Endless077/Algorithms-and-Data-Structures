
#include <iostream>

using namespace std;


int main() {

  try {

    ulong* ulptr = new ulong; // Uninitialized unsigned long
    // ulong* ulptr = new ulong(5); // new ulong{5} // Unsigned long initialized to 5

    cout << (*ulptr)++ << endl;
    cout << *ulptr << endl;

    delete ulptr; // ulptr = nullptr;
    // delete ulptr; // Double free cannot be catched!

  } catch (bad_alloc exc) {
    cout << "Quite rare exception!" << endl;
  }

  try {

    const ulong arraysize = 3; // 10000000000

    ulong* ulptr = new ulong[arraysize]; // Uninitialized array of three unsigned longs
    // ulong* ulptr = new ulong[arraysize]{}; // array of three unsigned longs initialized to the default value (0)
    // ulong* ulptr = new ulong[arraysize]{5, 6, 7}; // array of three unsigned longs initialized to 5, 6, and 7.

    cout << ulptr[0]++ << endl;
    cout << ulptr[1] << endl;
    cout << ulptr[2]-- << endl << endl;

    cout << ulptr[0] << endl;
    cout << ulptr[1] << endl;
    cout << ulptr[2] << endl;

    delete[] ulptr; // ulptr = nullptr;
    // delete[] ulptr; // Double free cannot be catched!

  } catch (bad_alloc exc) {
    cout << "Quite rare exception!" << endl;
  }

  return 0;
}
