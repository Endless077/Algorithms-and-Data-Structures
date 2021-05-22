
#ifndef MATRIXCSR_HPP
#define MATRIXCSR_HPP

/* ************************************************************************** */

#include "../matrix.hpp"

// #include "../../list/list.hpp"
// #include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixCSR { // Must extend Matrix<Data>

private:

  // ...

protected:

  // using Matrix<Data>::???;

  // ...

public:

  // Default constructor
  // MatrixCSR() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  // MatrixCSR(argument) specifiers; // A matrix of some specified dimension

  /* ************************************************************************ */

  // Copy constructor
  // MatrixCSR(argument) specifiers;

  // Move constructor
  // MatrixCSR(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~MatrixCSR() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  // type RowResize() specifiers; // Override Matrix member
  // type ColumnResize() specifiers; // Override Matrix member

  // type ExistsCell() specifiers; // Override Matrix member (should not throw exceptions)

  // type operator()() specifiers; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  // type operator()() specifiers; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Clear() specifiers; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  // type MapPreOrder(arguments) specifiers; // Override MappableContainer member
  // type MapPostOrder(arguments) specifiers; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member
  // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "matrixcsr.cpp"

#endif
