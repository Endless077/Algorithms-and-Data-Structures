
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

//#ifndef uvar
//#define uint unsigned int
//#define ulong unsigned long
//#endif

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List :  virtual public LinearContainer<Data>,
              virtual public MappableContainer<Data>,
              virtual public FoldableContainer<Data> { // Must extend LinearContainer<Data>, MappableContainer<Data>, and FoldableContainer<Data>

private:

  // ...

protected:

  using LinearContainer<Data>::size;

  struct Node
  {

    Data info;
		Node* next = nullptr;

    /* ********************************************************************** */

    //Costructor
    Node() = default;
    
    // Specific constructors
    Node(const Data&);
    Node(Data&&);

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node&);

    // Move constructor
    Node(const Node&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
		bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  Node* head = nullptr;
	Node* tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const LinearContainer<Data>&); // A list obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List<Data>&) const noexcept;
	bool operator!=(const List<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&) noexcept; // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value

  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&) noexcept; // Copy of the value
  void InsertAtBack(Data&&) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  Data& operator[](unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)


  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapPreOrder(MapFunctor, void*) override; // Override MappableContainer member
  void MapPostOrder(MapFunctor, void*) override; //Override MappableContainer member

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldPreOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  void FoldPostOrder(FoldFunctor, const void*, void*) const override;// Override FoldableContainer member

protected:

  // Auxiliary member functions (for MappableContainer)

  void MapPreOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards
  void MapPostOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  void FoldPreOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards
  void FoldPostOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
