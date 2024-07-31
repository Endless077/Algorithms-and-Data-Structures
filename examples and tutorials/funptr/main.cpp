
#include <iostream>

using namespace std;

void quicksort(int*, uint);
void quicksort(int*, uint, uint);
uint partition(int*, uint, uint);

enum class ComparisonType { LessThan, Equal, GreaterThen};


// Function pointer a la C
typedef ComparisonType (*CompareFunction) (int, int);

// // Function pointer a la C++
// #include <functional>
// typedef function<ComparisonType(int, int)> CompareFunction;

void quicksort(int*, uint, CompareFunction);
void quicksort(int*, uint, uint, CompareFunction);
uint partition(int*, uint, uint, CompareFunction);

ComparisonType OrdA(int a, int b) {
  if (a < b) {
    return ComparisonType::LessThan;
  } else if (a > b) {
    return ComparisonType::GreaterThen;
  }
  return ComparisonType::Equal;
}

ComparisonType OrdB(int a, int b) {
  if (a < b) {
    return ComparisonType::GreaterThen;
  } else if (a > b) {
    return ComparisonType::LessThan;
  }
  return ComparisonType::Equal;
}

ComparisonType OrdC(int a, int b) {
  if (a % 2 != b % 2) {
    return ((a % 2 == 0) ? ComparisonType::LessThan : ComparisonType::GreaterThen);
  } else if (a < b) {
    return ComparisonType::LessThan;
  } else if (a > b) {
    return ComparisonType::GreaterThen;
  }
  return ComparisonType::Equal;
}

int main() {

  int A[11] = {5, 7, 6, 8, 4, 9, 3, 10, 2, 0, 1};

  quicksort(A, 11);

  // quicksort(A, 11, OrdA);
  // // quicksort(A, 11, OrdB);
  // // // quicksort(A, 11, OrdC);

  for (uint i = 0; i < 11; i++) { cout << A[i] << ' '; }; cout << endl;

  return 0;
}

void quicksort(int* A, uint size) {
  quicksort(A, 0, size - 1);
}

void quicksort(int* A, uint p, uint r) {
  if (p < r) {
    uint q = partition(A, p, r);
    quicksort(A, p, q);
    quicksort(A, q + 1, r);
  }
}

uint partition(int* A, uint p, uint r) {

  int x = A[p];
  int i = p - 1;
  int j = r + 1;

  do {

    do { j--; } while ( x < A[j] );

    do { i++; } while ( A[i] < x );

    if (i < j) { swap(A[i], A[j]); } // "swap" is standard-library function

  } while (i < j);

  return j;

}

void quicksort(int* A, uint size, CompareFunction cmp) {
  quicksort(A, 0, size - 1, cmp);
}

void quicksort(int* A, uint p, uint r, CompareFunction cmp) {
  if (p < r) {
    uint q = partition(A, p, r, cmp);
    quicksort(A, p, q, cmp);
    quicksort(A, q + 1, r, cmp);
  }
}

uint partition(int* A, uint p, uint r, CompareFunction cmp) {

  int x = A[p];
  int i = p - 1;
  int j = r + 1;

  do {

    do { j--; } while ( cmp(x, A[j]) == ComparisonType::LessThan );

    do { i++; } while ( cmp(x, A[i]) == ComparisonType::GreaterThen );

    if (i < j) { swap(A[i], A[j]); } // "swap" is standard-library function

  } while (i < j);

  return j;

}
