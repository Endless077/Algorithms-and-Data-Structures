
#include <iostream>

#include "test.hpp"
// #include "testx.hpp"

using namespace std;

// void testx() {}; // cout << "";

int main() {
  cout << "Call to a function: #";
  test();
  // testx();
  cout << "# Return from a function call!" << endl;
  return 0;
}
