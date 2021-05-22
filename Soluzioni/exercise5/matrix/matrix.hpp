
#ifndef MATRIX_HPP
#define MATRIX_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Matrix { // Must extend MappableContainer<Data> and FoldableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~Matrix() specifiers

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  // type RowNumber() specifiers; // (concrete function should not throw exceptions)
  // type ColumnNumber() specifiers; // (concrete function should not throw exceptions)

  // type RowResize() specifiers;
  // type ColumnResize() specifiers;

  // type ExistsCell() specifiers; // (concrete function should not throw exceptions)

  // type operator()() specifiers; // Mutable access to the element (concrete function should throw exceptions only when out of range)
  // type operator()() specifiers; // Immutable access to the element (concrete function should throw exceptions when not present)

};

/* ************************************************************************** */

}

#include "matrix.cpp"

#endif
