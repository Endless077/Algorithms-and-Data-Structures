
#include <iostream>

// #include <stdexcept> // Optional when iostream is included!

using namespace std;

int main() {

  cout << "Hello everyone... I am rising some exception!" << endl;

  try {

    // throw logic_error("Some logic error.");
    // throw length_error("A lenght error occurred!");
    // throw out_of_range("An out-of-range access to some structure occurred!");

    // throw runtime_error("Some runtime error.");
    // throw overflow_error("An overflow occurred!");
    // throw underflow_error("An underflow occurred!");

    // throw bad_alloc(); // Just an example, do not throw thsi exception.

    // throw 25;

  } catch (length_error& exc) {

    cout << "Length error: " << exc.what() << endl;

    // throw;

  } catch (logic_error& exc) {

    cout << "Logic error: " << exc.what() << endl;

  } catch (overflow_error& exc) {

    cout << "Overflow error: " << exc.what() << endl;

  } catch (runtime_error& exc) {

    cout << "Runtime error: " << exc.what() << endl;

  } catch (bad_alloc& exc) {

    cout << "Bad allocation: " << exc.what() << endl;

  } catch (exception& exc) {

    cout << "All unmanaged standard exceptions reach this point!" << exc.what() << endl;

  }
  catch (...) {

    cout << "All unmanaged non-standard exceptions reach this point!" << endl;

  }

  // try {
  //
  //   try {
  //
  //     throw logic_error("Some logic error.");
  //
  //   } catch (logic_error& exc) {
  //
  //     cout << "I am unable to manage this exception: " << exc.what() << endl;
  //
  //     throw;
  //
  //   }
  //
  // } catch (...) {
  //
  //   cout << "All unmanaged exceptions reach this point!" << endl;
  //
  // }

  // try {
  //
  //   throw  5;
  //
  // } catch (int num) {
  //
  //   cout << "Exception number: " << num << endl;
  //
  // }

  return 0;
}
