
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> { // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk : virtual public BinaryTree<Data>::Node { // Must extend Node

  private:

    // ...

  protected:

    // ...

  public:

    Data element;
    NodeLnk* leftchild = nullptr;
    NodeLnk* rightchild = nullptr;

    //Costructor
    NodeLnk(const Data&);

    //Distructor
    virtual ~NodeLnk();

    // Specific member functions

    Data& Element() noexcept override; // Mutable access to the element (concrete function should not throw exceptions)
    const Data& Element() const noexcept override; // Immutable access to the element (concrete function should not throw exceptions)

    bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept override; // (concrete function should not throw exceptions)

    NodeLnk& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
    NodeLnk& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

  };

  void funzioneCostruzione(int, NodeLnk*, const LinearContainer<Data>&);
  NodeLnk* copyTree(NodeLnk*);

  NodeLnk* root = nullptr;
  
public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept;
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
