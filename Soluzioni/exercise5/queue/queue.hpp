
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue : virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */
  
  // Copy assignment
	Queue& operator=(const Queue&) = delete; // Copy assignment of abstract types should not be possible.

	// Move assignment
	Queue& operator=(Queue&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Queue&) const noexcept = delete; // Comparison of abstract types might not be possible.
  /* ************************************************************************ */

  // Specific member functions

  virtual void Enqueue(const Data &) = 0; // Copy of the value
  virtual void Enqueue(Data &&) = 0; // Move of the value
  virtual Data& Head() const = 0; // (concrete function must throw std::length_error when empty)
  virtual void Dequeue() = 0; // (concrete function must throw std::length_error when empty)
  virtual Data HeadNDequeue() = 0; // (concrete function must throw std::length_error when empty)

};

/* ************************************************************************** */

}

#endif
