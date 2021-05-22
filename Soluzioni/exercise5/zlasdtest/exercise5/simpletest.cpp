
#include <iostream>

/* ************************************************************************** */

#include "../container/container.hpp"

#include "../iterator/iterator.hpp"

#include "../matrix/matrix.hpp"
#include "../../matrix/vec/matrixvec.hpp"
#include "../../matrix/csr/matrixcsr.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

template <template<typename> typename Mat>
void stestMatrixInt(Mat<long>& mat, uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {

    Empty(loctestnum, loctesterr, mat, true);
    Size(loctestnum, loctesterr, mat, true, 0);

    GetRowNumber(loctestnum, loctesterr, mat, true, 0);
    GetColumnNumber(loctestnum, loctesterr, mat, true, 0);

    ExistsCell(loctestnum, loctesterr, mat, false, 0, 0);

    GetCell<long>(loctestnum, loctesterr, mat, false, 0, 0, 0);
    SetCell<long>(loctestnum, loctesterr, mat, false, 0, 0, 0);

    SetRowNumber(loctestnum, loctesterr, mat, true, 1);
    SetColumnNumber(loctestnum, loctesterr, mat, true, 1);

    mat.Clear();

    ExistsCell(loctestnum, loctesterr, mat, false, 0, 0);

    SetRowNumber(loctestnum, loctesterr, mat, true, 5);
    GetRowNumber(loctestnum, loctesterr, mat, true, 5);
    SetColumnNumber(loctestnum, loctesterr, mat, true, 4);
    GetColumnNumber(loctestnum, loctesterr, mat, true, 4);

    SetCell<long>(loctestnum, loctesterr, mat, true, 0, 1, 1);
    SetCell<long>(loctestnum, loctesterr, mat, true, 1, 0, 2);

    SetCell<long>(loctestnum, loctesterr, mat, true, 2, 1, 3);

    SetCell<long>(loctestnum, loctesterr, mat, true, 0, 3, 4);
    SetCell<long>(loctestnum, loctesterr, mat, true, 2, 3, 5);

    SetCell<long>(loctestnum, loctesterr, mat, true, 4, 1, 6);
    SetCell<long>(loctestnum, loctesterr, mat, true, 4, 3, 7);

    Mat<long> copmat(mat);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);
    MapPreOrder<long, long>(loctestnum, loctesterr, copmat, true, &MapPrint<long>, 0);
    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);
    MapPostOrder<long, long>(loctestnum, loctesterr, copmat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldAdd<long>, 0, 0, 28);

    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapIncrement<long>, 0);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldMultiply<long>, 0, 1, 40320);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapDecrement<long>, 0);

    SetColumnNumber(loctestnum, loctesterr, mat, true, 5);

    SetCell<long>(loctestnum, loctesterr, mat, true, 1, 4, 8);
    SetCell<long>(loctestnum, loctesterr, mat, true, 3, 4, 9);

    SetColumnNumber(loctestnum, loctesterr, mat, true, 3);
    SetColumnNumber(loctestnum, loctesterr, mat, true, 4);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);
    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldAdd<long>, 0, 0, 12);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapIncrement<long>, 0);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldMultiply<long>, 0, 1, 168);

    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapDecrement<long>, 0);

    SetRowNumber(loctestnum, loctesterr, mat, true, 4);
    SetRowNumber(loctestnum, loctesterr, mat, true, 5);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);
    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldAdd<long>, 0, 0, 6);

    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapIncrement<long>, 0);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldMultiply<long>, 0, 1, 24);

    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapDecrement<long>, 0);

    NonEqualMatrix(loctestnum, loctesterr, mat, copmat);

    SetCell<long>(loctestnum, loctesterr, mat, true, 4, 1, 6);
    SetCell<long>(loctestnum, loctesterr, mat, true, 4, 3, 7);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);
    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldAdd<long>, 0, 0, 19);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapIncrement<long>, 0);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldMultiply<long>, 0, 1, 1344);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapDecrement<long>, 0);

    NonEqualMatrix(loctestnum, loctesterr, mat, copmat);

    SetCell<long>(loctestnum, loctesterr, mat, true, 0, 3, 4);
    SetCell<long>(loctestnum, loctesterr, mat, true, 2, 3, 5);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);
    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldAdd<long>, 0, 0, 28);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapIncrement<long>, 0);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldMultiply<long>, 0, 1, 40320);

    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapDecrement<long>, 0);

    MapPreOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);
    MapPreOrder<long, long>(loctestnum, loctesterr, copmat, true, &MapPrint<long>, 0);

    EqualMatrix(loctestnum, loctesterr, mat, copmat);

    Mat<long> movmat(std::move(mat));

    GetRowNumber(loctestnum, loctesterr, mat, true, 0);
    GetColumnNumber(loctestnum, loctesterr, mat, true, 0);

    ExistsCell(loctestnum, loctesterr, mat, false, 0, 0);

    Exists<long>(loctestnum, loctesterr, movmat, false, 8);

    SetCell<long>(loctestnum, loctesterr, movmat, true, 4, 2, 8);

    MapPreOrder<long, long>(loctestnum, loctesterr, movmat, true, &MapPrint<long>, 0);
    MapPostOrder<long, long>(loctestnum, loctesterr, movmat, true, &MapPrint<long>, 0);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, movmat, true, &FoldAdd<long>, 0, 0, 36);

    Exists<long>(loctestnum, loctesterr, movmat, true, 8);

    SetRowNumber(loctestnum, loctesterr, movmat, true, 4);
    MapPostOrder<long, long>(loctestnum, loctesterr, movmat, true, &MapPrint<long>, 0);

    movmat.Clear();

    GetRowNumber(loctestnum, loctesterr, movmat, true, 0);
    GetColumnNumber(loctestnum, loctesterr, movmat, true, 0);

    mat = copmat;
    copmat.Clear();

    MapPostOrder<long, long>(loctestnum, loctesterr, mat, true, &MapPrint<long>, 0);

    SetRowNumber(loctestnum, loctesterr, mat, true, 3);
    SetColumnNumber(loctestnum, loctesterr, mat, true, 3);

    FoldPreOrder<long, long, long>(loctestnum, loctesterr, mat, true, &FoldAdd<long>, 0, 0, 6);

  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Matrix<long> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestMatrixInt(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Matrix<long> Test" << endl;
  try {
    lasd::MatrixVec<long> matvec;
    cout << endl << "Begin of MatrixVec<long> Test:" << endl;
    stestMatrixInt(matvec, loctestnum, loctesterr);
    lasd::MatrixCSR<long> matcsr;
    cout << endl << "Begin of MatrixCSR<long> Test:" << endl;
    stestMatrixInt(matcsr, loctestnum, loctesterr);
    cout << "\n";
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Matrix<long> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

template <typename Mat>
void stestMatrixFloat(Mat& mat, uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {

    SetCell(loctestnum, loctesterr, mat, true, 0, 0, 3.0);
    SetCell(loctestnum, loctesterr, mat, true, 1, 1, 2.1);
    SetCell(loctestnum, loctesterr, mat, true, 2, 2, 1.2);

    SetCell(loctestnum, loctesterr, mat, true, 3, 0, 0.3);
    SetCell(loctestnum, loctesterr, mat, true, 2, 1, 1.2);
    SetCell(loctestnum, loctesterr, mat, true, 1, 2, 2.1);

    SetCell(loctestnum, loctesterr, mat, true, 0, 2, 0.3);
    SetCell(loctestnum, loctesterr, mat, true, 1, 1, 1.2);
    SetCell(loctestnum, loctesterr, mat, true, 2, 0, 2.1);

    SetCell(loctestnum, loctesterr, mat, true, 3, 2, 3.0);
    SetCell(loctestnum, loctesterr, mat, true, 2, 1, 2.1);
    SetCell(loctestnum, loctesterr, mat, true, 1, 0, 1.2);

    Mat newmat(5, 10);
    newmat = std::move(mat);

    GetRowNumber(loctestnum, loctesterr, mat, true, 5);
    GetColumnNumber(loctestnum, loctesterr, mat, true, 10);

    GetCell(loctestnum, loctesterr, mat, false, 5, 10, 0.0);

    Exists<double>(loctestnum, loctesterr, mat, false, 3.0);

    GetCell(loctestnum, loctesterr, newmat, true, 1, 1, 1.2);
    GetCell(loctestnum, loctesterr, newmat, true, 2, 1, 2.1);

    GetRowNumber(loctestnum, loctesterr, newmat, true, 4);
    GetColumnNumber(loctestnum, loctesterr, newmat, true, 3);

  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Matrix<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestMatrixFloat(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Matrix<double> Test" << endl;
  try {
    lasd::MatrixVec<double> matvec(4, 3);
    cout << endl << "Begin of MatrixVec<double> Test:" << endl;
    stestMatrixFloat(matvec, loctestnum, loctesterr);
    lasd::MatrixCSR<double> matcsr(4, 3);
    cout << endl << "Begin of MatrixCSR<double> Test:" << endl;
    stestMatrixFloat(matcsr, loctestnum, loctesterr);
    cout << "\n";
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Matrix<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

template <typename Mat>
void stestMatrixString(Mat& mat, uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {

    SetCell(loctestnum, loctesterr, mat, true, 0, 0, string("| A"));
    SetCell(loctestnum, loctesterr, mat, true, 0, 2, string("B |"));

    SetCell(loctestnum, loctesterr, mat, true, 1, 1, string(" C |"));

    SetCell(loctestnum, loctesterr, mat, true, 2, 0, string(" D"));
    SetCell(loctestnum, loctesterr, mat, true, 2, 2, string("E |"));

    MapPreOrder<string, int>(loctestnum, loctesterr, mat, true, &MapPrint<string>, 0);
    MapPostOrder<string, int>(loctestnum, loctesterr, mat, true, &MapPrint<string>, 0);

    FoldPreOrder<string, string, string>(loctestnum, loctesterr, mat, true, &FoldStringConcatenate, string(""), string("?"), string("?| AB | C | DE |"));
    FoldPostOrder<string, string, string>(loctestnum, loctesterr, mat, true, &FoldStringConcatenate, string(""), string("?"), string("?E | D C |B || A"));

    MapPreOrder<string, string>(loctestnum, loctesterr, mat, true, &MapStringNonEmptyAppend, string(" "));

    FoldPreOrder<string, string, string>(loctestnum, loctesterr, mat, true, &FoldStringConcatenate, string(""), string("?"), string("?| A B |  C |  D E | "));
    FoldPostOrder<string, string, string>(loctestnum, loctesterr, mat, true, &FoldStringConcatenate, string(""), string("?"), string("?E |  D  C | B | | A "));

    MapPreOrder<string, string>(loctestnum, loctesterr, mat, true, &MapStringNonEmptyAppend, string("X"));

    FoldPreOrder<string, string, string>(loctestnum, loctesterr, mat, true, &FoldStringConcatenate, string(""), string("?"), string("?| A XB | X C | X D XE | X"));
    FoldPostOrder<string, string, string>(loctestnum, loctesterr, mat, true, &FoldStringConcatenate, string(""), string("?"), string("?E | X D X C | XB | X| A X"));

    GetRowNumber(loctestnum, loctesterr, mat, true, 3);
    GetColumnNumber(loctestnum, loctesterr, mat, true, 3);

  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Matrix<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestMatrixString(uint& testnum, uint& testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Matrix<string> Test" << endl;
  try {
    lasd::MatrixVec<string> matvec(3, 3);
    cout << endl << "Begin of MatrixVec<string> Test:" << endl;
    stestMatrixString(matvec, loctestnum, loctesterr);
    lasd::MatrixCSR<string> matcsr(3, 3);
    cout << endl << "Begin of MatrixCSR<string> Test:" << endl;
    stestMatrixString(matcsr, loctestnum, loctesterr);
    cout << "\n";
  } catch(...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Matrix<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testSimpleExercise5() {
  uint testnum = 0, testerr = 0;
  stestMatrixInt(testnum, testerr);
  stestMatrixFloat(testnum, testerr);
  stestMatrixString(testnum, testerr);
  cout << endl << "Exercise 5 (Simple Test) (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
