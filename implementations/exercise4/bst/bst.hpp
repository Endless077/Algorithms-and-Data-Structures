
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public BinaryTreeLnk<Data> { // Must extend BinaryTreeLnk<Data>

private:

  // ...

protected:

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

  // ...

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&); // A bst obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST&);

  // Move constructor
  BST(BST&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&);

  // Move assignment
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST&) const noexcept;
  bool operator!=(const BST&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void Insert(const Data&) noexcept; // Copy of the value
  void Insert(Data&&) noexcept; // Move of the value
  void Remove(const Data&) noexcept;

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

protected:

  // Auxiliary member functions

  //DataNDelete
  Data DataNDelete(struct BST<Data>::NodeLnk*);

  //Detach
  struct BST<Data>::NodeLnk* Detach(struct BST<Data>::NodeLnk*&) noexcept;

  //Detach Max/Min
  struct BST<Data>::NodeLnk* DetachMin(struct BST<Data>::NodeLnk*&) noexcept;
  struct BST<Data>::NodeLnk* DetachMax(struct BST<Data>::NodeLnk*&) noexcept;

  /* ************************************************************************ */

  //Skip
  struct BST<Data>::NodeLnk* SkipOnLeft(struct BST<Data>::NodeLnk*&) noexcept;
  struct BST<Data>::NodeLnk* SkipOnRight(struct BST<Data>::NodeLnk*&) noexcept;

  /* ************************************************************************ */
  
  //FindPointerTo Max/Min NOT CONST
  struct BST<Data>::NodeLnk*& FindPointerToMin(struct BST<Data>::NodeLnk*&) noexcept;
  struct BST<Data>::NodeLnk*& FindPointerToMax(struct BST<Data>::NodeLnk*&) noexcept;

  //FindPointerTo Max/Min CONST
  struct BST<Data>::NodeLnk* const& FindPointerToMin(struct BST<Data>::NodeLnk* const&) const noexcept;
  struct BST<Data>::NodeLnk* const& FindPointerToMax(struct BST<Data>::NodeLnk* const&) const noexcept;

  /* ************************************************************************ */

  //FindPointerTo NOT CONST
  struct BST<Data>::NodeLnk*& FindPointerTo(struct BST<Data>::NodeLnk*&, const Data&) noexcept;

  //FindPointerTo CONST
  struct BST<Data>::NodeLnk* const& FindPointerTo(struct BST<Data>::NodeLnk* const&, const Data&) const noexcept;

  /* ************************************************************************ */

  //FindPointerTo Predecessor/Successor NOT CONST
  struct BST<Data>::NodeLnk*& FindPointerToPredecessor(struct BST<Data>::NodeLnk*&, const Data&) noexcept;
  struct BST<Data>::NodeLnk*& FindPointerToSuccessor(struct BST<Data>::NodeLnk*&, const Data&) noexcept;

  //FindPointerTo Predecessor/Successor CONST
  struct BST<Data>::NodeLnk* const& FindPointerToPredecessor(struct BST<Data>::NodeLnk* const&, const Data&) const noexcept;
  struct BST<Data>::NodeLnk* const& FindPointerToSuccessor(struct BST<Data>::NodeLnk* const&, const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
