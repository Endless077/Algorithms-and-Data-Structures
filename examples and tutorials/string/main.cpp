
#include <iostream>

// #include <string>  // Optional when iostream is included!

using namespace std;

int main() {

  string String;
  // string String();

  string Stringa1 = "Alan Turing";
  // string Stringa1 = {"Alan Turing"};
  // string Stringa1{"Alan Turing"};
  // string Stringa1("Alan Turing");

  string Stringa2 = "Kurt Godel";

  cout << Stringa1 << " - " << Stringa2 << endl;
  cout << "Lexicographic comparison (String1 <  String2): " << (Stringa1 < Stringa2) << endl;
  cout << "Lexicographic comparison (String1 <= String2): " << (Stringa1 <= Stringa2) << endl;
  cout << "Lexicographic comparison (String1 == String2): " << (Stringa1 == Stringa2) << endl;
  cout << "Lexicographic comparison (String1 != String2): " << (Stringa1 != Stringa2) << endl;
  cout << "Lexicographic comparison (String1 >= String2): " << (Stringa1 >= Stringa2) << endl;
  cout << "Lexicographic comparison (String1 >  String2): " << (Stringa1 > Stringa2) << endl;

  // cin >> Stringa2;
  // // getline (cin, Stringa2);
  //
  // cout << Stringa1 << " - " << Stringa2 << endl;
  // cout << "Lexicographic comparison (String1 <  String2): " << (Stringa1 < Stringa2) << endl;
  // cout << "Lexicographic comparison (String1 <= String2): " << (Stringa1 <= Stringa2) << endl;
  // cout << "Lexicographic comparison (String1 == String2): " << (Stringa1 == Stringa2) << endl;
  // cout << "Lexicographic comparison (String1 != String2): " << (Stringa1 != Stringa2) << endl;
  // cout << "Lexicographic comparison (String1 >= String2): " << (Stringa1 >= Stringa2) << endl;
  // cout << "Lexicographic comparison (String1 >  String2): " << (Stringa1 > Stringa2) << endl;

  // Stringa1.clear();
  //
  // cout << "Size: " << Stringa1.size() << endl;
  // cout << "String \"" << Stringa1 << "\" is " << (Stringa1.empty() ? "" : "not ") << "empty" << endl;
  // uint i = 3; cout << "Char " << i << " of string" << Stringa1 << " is \'" << Stringa1[i] << "\'"<< endl; // 1100000
  // cout << "String front is \'" << Stringa1.front() << "\'"<< endl;
  // cout << "String back is \'" << Stringa1.back() << "\'"<< endl;
  //
  // cout << (Stringa1 + " $ " + Stringa2) << endl;
  //
  // i = 1; uint j = 2; cout << "Subtring from " << i << " to " << j << " of \"" << Stringa1 << "\" is \"" << Stringa1.substr(i, j) << "\"" << endl;

  return 0;
}
