
#include "./exercise1/test.hpp"

#include "./exercise2/test.hpp"

#include "./exercise3/test.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void lasdtest() {
  cout << endl << "~*~#~*~ Welcome to the LASD Test Suite ~*~#~*~ " << endl;
  testSimpleExercise1();
  testFullExercise1();
  testSimpleExercise2();
  testFullExercise2();
  testSimpleExercise3();
  testFullExercise3();
  cout << endl << "Goodbye!" << endl;
}
