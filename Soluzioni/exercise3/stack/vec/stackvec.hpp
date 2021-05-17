
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>, virtual protected Vector<Data> { // Must extend Stack<Data> and Vector<Data>

private:

  void initialize();
  
  // ...

protected:

  using Stack<Data>::index;
  using Vector<Data>::size;
  using Vector<Data>::Elements;
  
  using Vector<Data>::Resize;

  inline bool isStackFull() const { return size == (index+1); }
  inline bool isStackToReduce() const { return index == (size/4); }

  // ...

public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const LinearContainer<Data>&); // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data> &);

  // Move constructor
  StackVec(StackVec<Data> &&) noexcept;


  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec<Data> &operator=(const StackVec<Data> &);

  // Move assignment
  StackVec<Data> &operator=(StackVec<Data> &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec<Data> &vec) const;
  bool operator!=(const StackVec<Data> &vec) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  void Push(const Data &) noexcept override; // Override Stack member (copy of the value)
  void Push(Data &&) noexcept override; // Override Stack member (move of the value)
  Data& Top() const override; // Override Stack member (must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override { return (index==0); } // Override Container member

  inline ulong Size() const noexcept override { return index; } // Override Container member

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand(uint) noexcept;
  void Reduce(uint) noexcept;

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
