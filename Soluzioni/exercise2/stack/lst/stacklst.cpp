#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

//Costructor with LinearContainer
template <typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& con) : List<Data>(con) {}

//Copy costructor
template <typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& cpyList) : List<Data>(cpyList){}

//Move costructor
template <typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& mvList) noexcept : List<Data>(std::move(mvList)){}

/* ************************************************************************** */

//Copy Assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& assStack) {
  List<Data>::operator=(assStack);
  return *this;
}

//Move Assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& assStack) {
  List<Data>::operator=(std::move(assStack));
  return *this;
}

/* ************************************************************************** */

//Comparison Operator
template <typename Data>
bool StackLst<Data>::operator==(const StackLst &stackConf) const noexcept {
    return List<Data>::operator==(stackConf);
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst &stackConf) const noexcept {
    return List<Data>::operator!=(stackConf);
}

/* *************************************************************************** */

//Copy Push
template <typename Data>
void StackLst<Data>::Push(const Data &data) noexcept {
  List<Data>::InsertAtFront(data);
}

//Move Push
template <typename Data>
void StackLst<Data>::Push(Data &&data) noexcept {
    List<Data>::InsertAtFront(data);
}

//Top
template <typename Data>
Data& StackLst<Data>::Top() const {
  if (List<Data>::Empty())
    throw std::length_error("Access to the Top of an empty stack.");

  return this->Front();
}

//Pop
template <typename Data>
void StackLst<Data>::Pop() {
  if (List<Data>::Empty())
    throw std::length_error("Access to the Top of an empty stack.");

  const Data &data = this->Front();

  List<Data>::RemoveFromFront();
}

//TopNPop
template <typename Data>
Data StackLst<Data>::TopNPop() {
  Data testa = Top();
  Pop();
  return testa;
}

/* ************************************************************************** */

}
