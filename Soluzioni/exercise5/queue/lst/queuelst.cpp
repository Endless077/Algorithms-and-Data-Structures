#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

//Constructor with LinearContainer
template <typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& con) : List<Data>(con) {}

/* ************************************************************************** */

//Copy constructor
template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& cpyList) : List<Data>(cpyList){}

//Move constructor
template <typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& mvList) noexcept : List<Data>(std::move(mvList)){}

/* ************************************************************************** */

//Copy Assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& assStack) {
  List<Data>::operator=(assStack);
  return *this;
}

//Move Assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& assStack) {
  List<Data>::operator=(std::move(assStack));
  return *this;
}

/* ************************************************************************** */

//Comparison Operator
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst &stackConf) const noexcept {
    return List<Data>::operator==(stackConf);
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst &stackConf) const noexcept {
    return List<Data>::operator!=(stackConf);
}

/* *************************************************************************** */

//Enqueue (Copy)
template <typename Data>
void QueueLst<Data>::Enqueue(const Data &data) {
  List<Data>::InsertAtBack(data);
}

//Enqueue (Move)
template <typename Data>
void QueueLst<Data>::Enqueue(Data &&data) {
  List<Data>::InsertAtBack(data);
}

//Head
template <typename Data>
Data& QueueLst<Data>::Head() const {
  if (List<Data>::Empty())
    throw std::length_error("Access to Head of an empty queue.");

  return List<Data>::Front();
}

//Deaqueue
template <typename Data>
void QueueLst<Data>::Dequeue() {
  if (List<Data>::Empty())
    throw std::length_error("Access to Head of an empty queue.");

  List<Data>::RemoveFromFront();
}

//HeadNDequeue
template <typename Data>
Data QueueLst<Data>::HeadNDequeue() {
  if (List<Data>::Empty())
    throw std::length_error("Access to Head of an empty queue.");
  
  Data value = this->Head();
  Dequeue();
  return value;
}

/* *************************************************************************** */

}
