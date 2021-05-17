
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

//#ifndef uvar
//#define uint unsigned int
//#define ulong unsigned long
//#endif

/* ************************************************************************** */

#include <stdexcept>
#include <functional>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

  ulong size = 0;

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Container& operator=(Container&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&) const noexcept = delete;  // Comparison of abstract types might not be possible.
	bool operator!=(const Container&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual inline bool Empty() const noexcept { return (size == 0); }

	virtual inline ulong Size() const noexcept { return size; }

	virtual void Clear() = 0;

};

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
	bool operator!=(const LinearContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& Front() const = 0; // (concrete function must throw std::length_error when empty)
	virtual Data& Back() const = 0; // (concrete function must throw std::length_error when empty)

	virtual Data& operator[](const ulong) const = 0; // (concrete function must throw std::out_of_range when out of range)

};

/* ************************************************************************** */

template <typename Data>
class TestableContainer : virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~TestableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TestableContainer& operator=(const TestableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  TestableContainer& operator=(TestableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TestableContainer&) = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const TestableContainer&) = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Exists(const Data&) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer& operator=(const MappableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MappableContainer& operator=(MappableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer&) = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MappableContainer&) = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  typedef std::function<void(Data&, void*)> MapFunctor;

  virtual void MapPreOrder(const MapFunctor, void*) = 0;
  virtual void MapPostOrder(const MapFunctor, void*) = 0;

};
/* ************************************************************************** */

template <typename Data>
class FoldableContainer : virtual public  TestableContainer<Data> { // Must extend TestableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~FoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  FoldableContainer& operator=(const FoldableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  FoldableContainer& operator=(FoldableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const FoldableContainer&) = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const FoldableContainer&) = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  typedef std::function<void(const Data&, const void*, void*) noexcept> FoldFunctor;

  virtual void FoldPreOrder(const FoldFunctor, const void*, void*) const = 0;
  virtual void FoldPostOrder(const FoldFunctor, const void*, void*) const = 0;

  virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer { // Must extend MappableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~BreadthMappableContainer() specifiers

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

  // using typename MappableContainer<Data>::MapFunctor;

  // type MapBreadth(arguments) specifiers;

};

/* ************************************************************************** */

template <typename Data>
class BreadthFoldableContainer { // Must extend FoldableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~BreadthFoldableContainer() specifiers

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

  // using typename FoldableContainer<Data>::FoldFunctor;

  // type FoldBreadth(arguments) specifiers;

};

/* ************************************************************************** */

}

#include "container.cpp"

#endif
