#include <stdexcept>

#define DEFAULT_CAPACITY 4

namespace lasd {

/* ************************************************************************** */

//Inizializzazione
template <typename Data>
void QueueVec<Data>::initialize(){
    size = DEFAULT_CAPACITY;
    Elements = new Data[size] {};
}

/* ************************************************************************** */

//Constructor
template <typename Data>
QueueVec<Data>::QueueVec() {
    initialize();
}

//Constructor with LinearContainer
template <typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data> &con) {
    
    if(con.Size() == 0)
        initialize();
    else{

        size = con.Size()*2;
        Elements = new Data[size] {};

        for (ulong i = 0; i < con.Size(); ++i){ 
            Enqueue(con[i]);
        }
    }
}

/* ************************************************************************** */

//Copy constructor
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& cpyVec) : Vector<Data>(cpyVec){
    front = cpyVec.front;
    rear = cpyVec.rear;
}

//Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& mvVec) noexcept {
    initialize();
    std::swap(size, mvVec.size);
    std::swap(Elements,mvVec.Elements);
    std::swap(front, mvVec.front);
    std::swap(rear, mvVec.rear);

}

/* ************************************************************************** */

//Copy Assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& assQueue) {
  Vector<Data>::operator=(assQueue);
  front = assQueue.front;
  rear = assQueue.rear;
  return *this;
}

//Move Assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& assQueue) noexcept {
  Vector<Data>::operator=(std::move(assQueue));
  std::swap(front, assQueue.front);
  std::swap(rear, assQueue.rear);
  return *this;
}

/* ************************************************************************** */

//Comparison operators
template <typename Data>
bool QueueVec<Data>::operator==(const lasd::QueueVec<Data> &vec) const noexcept {
    
    if(Size() != vec.Size())
        return false;
    
    uint i = front;
    uint j = rear;
    uint k = vec.front;

    while(i!=j){
        if(Elements[i] != vec.Elements[k])
          return false;
        i = (i+1) % size;
        k = (k+1) % vec.size;
    }

    return true;
}

template <typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data> &vec) const noexcept {
  return !(*this == vec);
}

/* ************************************************************************** */

//Enqueue (Copy)
template <typename Data>
void QueueVec<Data>::Enqueue(const Data &data) {
    if(((rear+2) % size) != front){
        rear = (rear+1) % size;
        Elements[rear] = data;
    }else{
        Expand();
        Elements[rear] = data;
    }
}

//Enqueue (Move)
template <typename Data>
void QueueVec<Data>::Enqueue(Data &&data) {
    if(((rear+2) % size) != front){
        rear = (rear+1) % size;
        Elements[rear] = std::move(data);
    }else{
        Expand();
        Elements[rear] = std::move(data);
    }   
}

//Head
template <typename Data>
Data& QueueVec<Data>::Head() const {
    if (Size()==0)
        throw std::length_error("Access to the Head of an empty queue.");

    return Elements[front];
}

//Deaqueue
template <typename Data>
void QueueVec<Data>::Dequeue() {
    if (Size()==0)
        throw std::length_error("Access to the Head of an empty queue.");

    front = (front + 1) % size;
    
    if(Size() == (size/4) && size>DEFAULT_CAPACITY){
        Reduce();
    }
}

//HeadNDequeue
template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {
    if (Size()==0)
        throw std::length_error("Access to the Head of an empty queue.");

    Data &data = Elements[front];
    front = (front + 1) % size;

    if(Size() == (size/4) && size>DEFAULT_CAPACITY){
        Reduce();
    }

    return data;
}

/* ************************************************************************** */

//Specific member functions (inherited from Container)

template <typename Data>
bool QueueVec<Data>::Empty() const noexcept { return (Size()==0); }

template <typename Data>
ulong QueueVec<Data>::Size() const noexcept{ return ((rear+size) - front + 1) % size; }

template <typename Data>
void QueueVec<Data>::Clear() { 
    Vector<Data>::Clear();
    initialize();
    rear = 0; 
    front = 1;
}

/* ************************************************************************** */

// Accessory function
template <typename Data>
void QueueVec<Data>::Expand() noexcept {
    SwapVectors(size*2);
}

template <typename Data>
void QueueVec<Data>::Reduce() noexcept {
    SwapVectors(size - (size / 4));
}

template <typename Data>
void QueueVec<Data>::SwapVectors(uint newSize) noexcept {
    
    Data *tmp = new Data[newSize] {};
    uint c = 1;

    uint i = front-1;
    uint j = rear;

    while(i!=j){
        i = (i+1) % size;
        tmp[c]=Elements[i];
        c++;
    }

/*
    if(front < rear){
        for(uint i = front; i<rear+1; i++){
            tmp[c]=Elements[i];
            c++;
        }
    }else{
        for(uint j = front; j<size; j++){
            tmp[c]=Elements[j];
            c++;   
        }
        for(uint k = 0; k<=rear; k++){
            tmp[c]=Elements[k];
            c++;
        }
    }
*/

    std::swap(Elements,tmp);
    front = 1;
    rear = c;
    size=newSize;

    delete[] tmp;
}

}
