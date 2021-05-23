#include <stdexcept>

namespace lasd {

/* ************************************************************************** */
/*                               NODE VEC                                     */
/* ************************************************************************** */

//Costructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data &dato, ulong indice, Vector<NodeVec*> *vec) {
    element = dato;
    indexNode = indice;
    vectorPointer = vec;
}

// Specific member functions

template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return element;
}

template <typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return element;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (indexNode*2+1) <= (vectorPointer->Size() - 1);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
   return (indexNode*2+2) <= (vectorPointer->Size() - 1);
}

template <typename Data>
struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(!HasLeftChild())
        throw std::out_of_range("Access to an empty child.");

    return *(vectorPointer->operator[](indexNode*2+1));
}

template <typename Data>
struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(!HasRightChild())
        throw std::out_of_range("Access to an empty child.");

    return *(vectorPointer->operator[](indexNode*2+2));

}

/* ************************************************************************** */
/*                               TREE VEC                                     */
/* ************************************************************************** */

//Costructor (default)

// Specific constructors
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data> &con) {
    if(con.Size()) {
        size = con.Size();
        treevector = new Vector<NodeVec*>(size);

        for(uint i = 0; i<size; i++){
            NodeVec* node = new NodeVec(con[i],i,treevector);
            treevector->operator[](i) = node;
        }
    }
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &bt) {
    size = bt.size;
    treevector = new Vector<NodeVec*>(size);
    for(uint i = 0; i<size; i++){
        NodeVec* node = new NodeVec(bt.treevector->operator[](i)->Element(),i,treevector);
        treevector->operator[](i) = node;
    }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&bt) noexcept {
    treevector = new Vector<NodeVec*>();
    std::swap(size,bt.size);
    std::swap(treevector,bt.treevector);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
    Clear();

    delete treevector;
    treevector = nullptr;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> &bt) {
    BinaryTreeVec<Data>* tmpbt = new BinaryTreeVec<Data>(bt);
	std::swap(*this,*tmpbt);
	delete tmpbt;
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> &&bt) noexcept {
    std::swap(size,bt.size);
    std::swap(treevector,bt.treevector);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> &bt) const noexcept {
   return BinaryTree<Data>::operator==(bt);
}

template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> &bt) const noexcept{
    return !(*this == bt);
}

/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree)
template <typename Data>
struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if(size==0)
        throw std::length_error("Access to an empty binary tree.");

    return *(treevector->operator[](0));
}

/* ************************************************************************ */

//FoldBreadth
template <typename Data>
void BinaryTreeVec<Data>::FoldBreadth(const FoldFunctor fun, const void *par, void *acc) const {
    for(uint i = 0; i < size; i++) {
        fun(treevector->operator[](i)->Element(), par, acc);
    }
}

//MapBreadth
template <typename Data>
void BinaryTreeVec<Data>::MapBreadth(const MapFunctor fun, void *par) {
    for(uint i = 0; i < size; i++) {
        fun(treevector->operator[](i)->Element(), par);
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    if(size > 0) {
        for(uint i = 0; i < size; i++) {
            delete (*treevector)[i];
        }
        treevector->Clear();
        size = 0;
    }
}

/* ************************************************************************** */

}
