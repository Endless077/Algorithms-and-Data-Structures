
#include <iostream>

/* ************************************************************************** */

#include "../container/container.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void stestVectorInt(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<int> Test:" << endl;
  try {
    {
      lasd::Vector<int> vec;
      Empty(loctestnum, loctesterr, vec, true);

      GetFront(loctestnum, loctesterr, vec, false, 0);
      GetBack(loctestnum, loctesterr, vec, false, 0);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);

      Exists(loctestnum, loctesterr, vec, false, 0);

      MapPreOrder(loctestnum, loctesterr, vec, true, &MapPrint<int>, 0);
      MapPostOrder(loctestnum, loctesterr, vec, true, &MapPrint<int>, 0);

      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0, 0);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0, 0);
    }
    {
      lasd::Vector<int> vec(3);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 3);

      SetAt(loctestnum, loctesterr, vec, true, 0, 4);
      SetAt(loctestnum, loctesterr, vec, true, 1, 3);
      SetAt(loctestnum, loctesterr, vec, true, 2, 1);

      GetFront(loctestnum, loctesterr, vec, true, 4);
      GetBack(loctestnum, loctesterr, vec, true, 1);

      SetFront(loctestnum, loctesterr, vec, true, 5);
      SetBack(loctestnum, loctesterr, vec, true, 4);

      Exists(loctestnum, loctesterr, vec, true, 4);

      MapPreOrder(loctestnum, loctesterr, vec, true, &MapPrint<int>, 0);
      MapPostOrder(loctestnum, loctesterr, vec, true, &MapPrint<int>, 0);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0, 12);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 0, 1, 60);

      vec.Resize(2);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 0, 1, 15);
    }
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorDouble(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<double> Test:" << endl;
  try {
    lasd::Vector<double> vec(3);
    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 3);

    SetAt(loctestnum, loctesterr, vec, true, 0, 5.5);
    SetAt(loctestnum, loctesterr, vec, true, 1, 3.3);
    SetAt(loctestnum, loctesterr, vec, true, 2, 1.1);

    GetFront(loctestnum, loctesterr, vec, true, 5.5);
    GetBack(loctestnum, loctesterr, vec, true, 1.1);

    Exists(loctestnum, loctesterr, vec, true, 3.3);

    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 0.0, 9.9);
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 0.0, 1.0, 19.965);
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorString(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<string> Test:" << endl;
  try {
    lasd::Vector<string> vec(2);
    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 2);

    SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));

    GetFront(loctestnum, loctesterr, vec, true, string("A"));
    GetBack(loctestnum, loctesterr, vec, true, string("B"));

    Exists(loctestnum, loctesterr, vec, true, string("A"));

    MapPreOrder(loctestnum, loctesterr, vec, true, &MapStringAppend, string(" "));
    MapPreOrder(loctestnum, loctesterr, vec, true, &MapPrint<string>, 0);
    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string(""), string("X"), string("XA B "));
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string(""), string("X"), string("XB A "));

    Exists(loctestnum, loctesterr, vec, false, string("A"));

    lasd::Vector<string> copvec(vec);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    MapPreOrder(loctestnum, loctesterr, vec, true, &MapStringAppend, string("!"));
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    copvec = move(vec);
    FoldPreOrder(loctestnum, loctesterr, copvec, true, &FoldStringConcatenate, string(""), string("?"), string("?A !B !"));

    lasd::Vector<string> movvec(move(vec));
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string(""), string("?"), string("?A B "));
    SetAt(loctestnum, loctesterr, vec, false, 1, string(""));
    vec.Resize(1);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));

    movvec.Clear();
    Empty(loctestnum, loctesterr, movvec, true);
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVector(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  stestVectorInt(loctestnum, loctesterr);
  stestVectorDouble(loctestnum, loctesterr);
  stestVectorString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Exercise 1 - Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void stestListInt(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<int> Test:" << endl;
  try {
    lasd::List<int> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    GetFront(loctestnum, loctesterr, lst, false, 0);
    GetBack(loctestnum, loctesterr, lst, false, 0);

    Exists(loctestnum, loctesterr, lst, false, 0);

    MapPreOrder(loctestnum, loctesterr, lst, true, &MapPrint<int>, 0);
    MapPostOrder(loctestnum, loctesterr, lst, true, &MapPrint<int>, 0);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0, 0);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0, 0);

    RemoveFromFront(loctestnum, loctesterr, lst, false);
    FrontNRemove(loctestnum, loctesterr, lst, false, 0);

    InsertAtBack(loctestnum, loctesterr, lst, true, 4);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 9);
    InsertAtBack(loctestnum, loctesterr, lst, true, 2);
    InsertAtFront(loctestnum, loctesterr, lst, true, 1);

    GetFront(loctestnum, loctesterr, lst, true, 1);
    GetBack(loctestnum, loctesterr, lst, true, 2);
    SetFront(loctestnum, loctesterr, lst, true, 2);
    SetBack(loctestnum, loctesterr, lst, true, 6);

    GetAt(loctestnum, loctesterr, lst, true, 3, 4);
    SetAt(loctestnum, loctesterr, lst, true, 3, 3);

    Exists(loctestnum, loctesterr, lst, false, 4);

    MapPreOrder(loctestnum, loctesterr, lst, true, &MapPrint<int>, 0);
    MapPostOrder(loctestnum, loctesterr, lst, true, &MapPrint<int>, 0);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0, 25);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 0, 1, 1620);

    RemoveFromFront(loctestnum, loctesterr, lst, true);
    FrontNRemove(loctestnum, loctesterr, lst, true, 9);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 0, 1, 90);

    lasd::List<int> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, lst, true, &MapIncrement<int>, 0);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    InsertAtFront(loctestnum, loctesterr, lst, true, 0);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);
    coplst = lst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);

    RemoveFromFront(loctestnum, loctesterr, coplst, true);
    FrontNRemove(loctestnum, loctesterr, coplst, true, 6);
    coplst = move(lst);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0, 11);
    FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldAdd<int>, 0, 0, 17);

    lasd::List<int> movlst(move(lst));
    MapPreOrder(loctestnum, loctesterr, movlst, true, &MapIncrement<int>, 0);
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 0, 0, 14);

    movlst.Clear();
    Empty(loctestnum, loctesterr, movlst, true);
    Size(loctestnum, loctesterr, movlst, true, 0);
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestListDouble(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<double> Test:" << endl;
  try {
    lasd::List<double> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    InsertAtBack(loctestnum, loctesterr, lst, true, -2.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 2.5);

    lst.Clear();

    InsertAtBack(loctestnum, loctesterr, lst, true, 0.5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 3.3);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 1.1);

    GetFront(loctestnum, loctesterr, lst, true, 5.5);
    GetBack(loctestnum, loctesterr, lst, true, 1.1);

    Exists(loctestnum, loctesterr, lst, false, 0.0);

    MapPreOrder(loctestnum, loctesterr, lst, true, &MapPrint<double>, 0);
    MapPostOrder(loctestnum, loctesterr, lst, true, &MapPrint<double>, 0);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<double>, 0.0, 0.0, 10.4);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<double>, 0.0, 1.0, 9.9825);
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestListString(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<string> Test:" << endl;
  try {
    lasd::List<string> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    InsertAtFront(loctestnum, loctesterr, lst, true, string("A"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("B"));

    GetFront(loctestnum, loctesterr, lst, true, string("A"));
    GetBack(loctestnum, loctesterr, lst, true, string("B"));

    Exists(loctestnum, loctesterr, lst, true, string("B"));

    MapPreOrder(loctestnum, loctesterr, lst, true, &MapStringAppend, string(" "));
    MapPreOrder(loctestnum, loctesterr, lst, true, &MapPrint<string>, 0);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string(""), string("X"), string("XA B "));
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string(""), string("X"), string("XB A "));

    Exists(loctestnum, loctesterr, lst, false, string("B"));

    lasd::List<string> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    RemoveFromFront(loctestnum, loctesterr, coplst, true);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    lst = coplst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    InsertAtBack(loctestnum, loctesterr, lst, true, string("A"));
    InsertAtFront(loctestnum, loctesterr, lst, true, string("C"));
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    coplst = move(lst);
    FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldStringConcatenate, string(""), string("?"), string("?CB A"));
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestList(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  stestListInt(loctestnum, loctesterr);
  stestListDouble(loctestnum, loctesterr);
  stestListString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Exercise 1 - List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void stestVectorListInt(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<int> Test:" << endl;
  try {
    lasd::Vector<int> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, -1);
    SetAt(loctestnum, loctesterr, vec, true, 1, 0);
    SetAt(loctestnum, loctesterr, vec, true, 2, 1);

    lasd::List<int> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, 1);
    InsertAtFront(loctestnum, loctesterr, lst, true, 0);
    InsertAtFront(loctestnum, loctesterr, lst, true, -1);

    lasd::Vector<int> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::Vector<int> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<int> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<int> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorListDouble(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<double> Test:" << endl;
  try {
    lasd::Vector<double> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, -0.5);
    SetAt(loctestnum, loctesterr, vec, true, 1, 0.0);
    SetAt(loctestnum, loctesterr, vec, true, 2, 0.5);

    lasd::List<double> lst;
    InsertAtBack(loctestnum, loctesterr, lst, true, -0.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0.0);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0.5);

    lasd::Vector<double> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::Vector<double> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<double> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<double> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorListString(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<string> Test:" << endl;
  try {
    lasd::Vector<string> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("C"));

    lasd::List<string> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, string("B"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("C"));
    InsertAtFront(loctestnum, loctesterr, lst, true, string("A"));

    lasd::Vector<string> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::Vector<string> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<string> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<string> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorList(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  stestVectorListInt(loctestnum, loctesterr);
  stestVectorListDouble(loctestnum, loctesterr);
  stestVectorListString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Exercise 1 - Vector/List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testSimpleExercise1() {
  uint testnum = 0, testerr = 0;
  stestVector(testnum, testerr);
  stestList(testnum, testerr);
  stestVectorList(testnum, testerr);
  cout << endl << "Exercise 1 (Simple Test) (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
