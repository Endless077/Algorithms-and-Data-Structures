#include <stdexcept>

#define DEFAULT_CAPACITY 4

namespace lasd {

/* ************************************************************************** */

//Inizializzazione
template <typename Data>
void StackVec<Data>::initialize(){
    size = DEFAULT_CAPACITY;
    Elements = new Data[size] {};
}

/* ************************************************************************** */

//Costructor
template <typename Data>
StackVec<Data>::StackVec() : Vector<Data>() {
    initialize();
}

//Costructor with LinearContainer
template <typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data> &con) : Vector<Data>(con) {
    index=con.Size();
    Resize(con.Size()*2);
}

/* ************************************************************************** */

//Copy costructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& cpyVec) : Vector<Data>(cpyVec){
    index=cpyVec.index;
}

//Move costructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& mvVec) noexcept {
    initialize();
    std::swap(size, mvVec.size);
    std::swap(Elements,mvVec.Elements);
    std::swap(index, mvVec.index);
}

/* ************************************************************************** */

//Copy Assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& assStack) {
  Vector<Data>::operator=(assStack);
  index = assStack.index;
  return *this;
}

//Move Assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& assStack) {
  Vector<Data>::operator=(std::move(assStack));
  index = assStack.index;
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data> &vec) const {
    if (index == vec.index) {
		for (ulong i = 0; i < index; ++i) {
			if (Elements[i] != vec.Elements[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data> &vec) const {
  return !(*this == vec);
}

/* ************************************************************************** */

//Copy Push
template <typename Data>
void StackVec<Data>::Push(const Data &data) noexcept {
    
    if(isStackFull())
        Expand(size*2);
    
    Elements[index] = data;
    index++;
}

//Move Push
template <typename Data>
void StackVec<Data>::Push(Data &&data) noexcept {
    
    if(isStackFull())
        Expand(size*2);

    Elements[index] = data;
    index++;
}

//Top
template <typename Data>
Data& StackVec<Data>::Top() const {
    if (Size()==0)
        throw std::length_error("Access to the Top of an empty stack.");

    return Elements[index - 1];
}

//Pop
template <typename Data>
void StackVec<Data>::Pop() {
    if (Size()==0)
        throw std::length_error("Access to the Top of an empty stack.");

    --index;

    if(isStackToReduce())
        Reduce(size/2);
}

//TopNPop
template <typename Data>
Data StackVec<Data>::TopNPop() {
  Data testa = Top();
  Pop();

  if(isStackToReduce())
    Reduce(size/2);

  return testa;
}

/* ************************************************************************** */

//Expand
template <typename Data>
void StackVec<Data>::Expand(uint newResize) noexcept {
  Resize(size + newResize);
}

//Reduce
template <typename Data>
void StackVec<Data>::Reduce(uint newResize) noexcept {
  Resize(size - newResize);
}

//Svuotamento
template <typename Data>
void StackVec<Data>::Clear() {
  Vector<Data>::Clear();
  initialize();
  index=0;
}

/* ************************************************************************** */

}
