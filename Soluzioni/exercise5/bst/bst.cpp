#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

// Constructor (default)

// Specific constructors
template <typename Data>
BST<Data>::BST(const LinearContainer<Data> &con) {
    for(ulong i = 0; i < con.Size(); i++) {
        Insert(con[i]);
    }
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BST<Data>::BST(const BST<Data> &bt) : BinaryTreeLnk<Data>(bt) {}

// Move constructor
template <typename Data>
BST<Data>::BST(BST<Data> &&bt) noexcept : BinaryTreeLnk<Data>(std::move(bt)) {}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(const BST &bt) {
    BinaryTreeLnk<Data>::operator=(bt);
    return *this;
}

// Move assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(BST &&bt) noexcept {
    BinaryTreeLnk<Data>::operator=(std::move(bt));
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BST<Data>::operator==(const BST &bt) const noexcept {
    if(size==bt.size){
        BTInOrderIterator<Data> iterThis(*this);
        BTInOrderIterator<Data> iterOther(bt);
        while (!iterThis.Terminated()){
            if(*iterThis != *iterOther)
                return false;
            ++iterThis;
            ++iterOther;
        }
        if(iterOther.Terminated())
            return true;
        else
            return false;
    }else{
        return false;
    }
}

template <typename Data>
bool BST<Data>::operator!=(const BST &bt) const noexcept {
    return !(*this == bt);
}

/* ************************************************************************ */

// Specific member functions

//Insert Copy
template <typename Data>
void BST<Data>::Insert(const Data &dato) noexcept {
    struct BST<Data>::NodeLnk*& pointer = FindPointerTo(root, dato);
    if(pointer==nullptr){
        pointer = new struct BST<Data>::NodeLnk(dato);
        size++;
    }
}

//Insert Move
template <typename Data>
void BST<Data>::Insert(Data &&dato) noexcept {
    struct BST<Data>::NodeLnk*& pointer = FindPointerTo(root, dato);
    if(pointer==nullptr){
        pointer = new struct BST<Data>::NodeLnk(std::move(dato));
        size++;
    }
}

//Remove
template <typename Data>
void BST<Data>::Remove(const Data &dato) noexcept {
    delete Detach(FindPointerTo(root, dato));
}

/* ************************************************************************ */

//Min function
template <typename Data>
const Data& BST<Data>::Min() const {
    if(root==nullptr)
        throw std::length_error("Access to an empty BST.");

    return FindPointerToMin(root)->element;
}

template <typename Data>
Data BST<Data>::MinNRemove() {
    if(root==nullptr)
        throw std::length_error("Access to an empty BST.");
    
    return DataNDelete(DetachMin(root));
}

template <typename Data>
void BST<Data>::RemoveMin() {
    if(root==nullptr)
        throw std::length_error("Access to an empty BST.");

    delete DetachMin(root);    
}

/* ************************************************************************ */

//Max function
template <typename Data>
const Data& BST<Data>::Max() const {
    if(root==nullptr)
        throw std::length_error("Access to an empty BST.");
    
    return FindPointerToMax(root)->element;
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
    if(root==nullptr)
        throw std::length_error("Access to an empty BST.");
    
    return DataNDelete(DetachMax(root));
}

template <typename Data>
void BST<Data>::RemoveMax() {
    if(root==nullptr)
        throw std::length_error("Access to an empty BST.");
    
    delete DetachMax(root);
}

/* ************************************************************************ */

//Predecessor function
template <typename Data>
const Data& BST<Data>::Predecessor(const Data &dato) const {
    struct BST<Data>::NodeLnk* const& pointer = FindPointerToPredecessor(root, dato);
    if(&pointer==nullptr)
        throw std::length_error("Predecessor not found.");

    return (pointer)->element;   
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data &dato) {
    struct BST<Data>::NodeLnk*& pointer = FindPointerToPredecessor(root, dato);
    if(&pointer==nullptr)
        throw std::length_error("Predecessor not found.");
    
    return DataNDelete(Detach(pointer));
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data &dato) {
    struct BST<Data>::NodeLnk*& pointer = FindPointerToPredecessor(root, dato);
    if(&pointer==nullptr)
        throw std::length_error("Predecessor not found.");
    
    delete Detach(pointer);
}

/* ************************************************************************ */

//Successor function
template <typename Data>
const Data& BST<Data>::Successor(const Data &dato) const {
    struct BST<Data>::NodeLnk* const& pointer = FindPointerToSuccessor(root, dato);
    if(&pointer==nullptr)
        throw std::length_error("Successor not found.");

    return (pointer)->element;
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data &dato) {
    struct BST<Data>::NodeLnk*& pointer = FindPointerToSuccessor(root, dato);
    if(&pointer==nullptr)
        throw std::length_error("Successor not found.");

    return DataNDelete(Detach(pointer));
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data &dato) {
    struct BST<Data>::NodeLnk*& pointer = FindPointerToSuccessor(root, dato);
    if(&pointer==nullptr)
        throw std::length_error("Successor not found.");

    delete Detach(pointer);
}

/* ************************************************************************ */

// Specific member functions (inherited from TestableContainer)
template <typename Data>
bool BST<Data>::Exists(const Data &dato) const noexcept {
    return (FindPointerTo(root,dato)!=nullptr);
}

/* ************************************************************************ */

// Auxiliary member functions
template <typename Data>
Data BST<Data>::DataNDelete(struct BST<Data>::NodeLnk *node) {
    Data dato;
    std::swap(dato,node->Element());
    delete node;
    return dato;
}

template <typename Data>
struct BST<Data>::NodeLnk* BST<Data>::Detach(struct BST<Data>::NodeLnk *&node) noexcept {
    if(node!=nullptr) {
        if(node->leftchild == nullptr)
            return SkipOnRight(node);
        else if(node->rightchild == nullptr)
            return SkipOnLeft(node);
        else {
          //Valgono entrambe le modalità nel caso in cui il nodo ha entrambi i figli.
          //struct BST<Data>::NodeLnk* detach = DetachMax(node->leftchild);
            struct BST<Data>::NodeLnk* detach = DetachMin(node->rightchild);
            std::swap(node->element, detach->element);
            return detach; 
        }
    }
    return nullptr;
}

template <typename Data>
struct BST<Data>::NodeLnk* BST<Data>::DetachMin(struct BST<Data>::NodeLnk *&node) noexcept {
    return SkipOnRight(FindPointerToMin(node));
}

template <typename Data>
struct BST<Data>::NodeLnk* BST<Data>::DetachMax(struct BST<Data>::NodeLnk *&node) noexcept {
    return SkipOnLeft(FindPointerToMax(node));
}

/* ************************************************************************ */

template <typename Data>
struct BST<Data>::NodeLnk* BST<Data>::SkipOnLeft(struct BST<Data>::NodeLnk *&node) noexcept {
    struct BST<Data>::NodeLnk* skipLeft = nullptr;
    if(node!=nullptr){
        std::swap(skipLeft,node->leftchild);
        std::swap(skipLeft,node);
        size--;
    }
    return skipLeft;
}

template <typename Data>
struct BST<Data>::NodeLnk* BST<Data>::SkipOnRight(struct BST<Data>::NodeLnk *&node) noexcept {
    struct BST<Data>::NodeLnk* skipRight = nullptr;
    if(node!=nullptr){
        std::swap(skipRight,node->rightchild);
        std::swap(skipRight,node);
        size--;
    }
    return skipRight;
}

/* ************************************************************************ */

template <typename Data>
struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(struct BST<Data>::NodeLnk * const& node) const noexcept {
    struct BST<Data>::NodeLnk* const* pointer = &node;
    struct BST<Data>::NodeLnk* current = node;

    if(current!=nullptr) {
        while (current->HasLeftChild()) {
            pointer = &current->leftchild;
            current = current->leftchild;
        }
    }
    return *pointer;
}

template <typename Data>
struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(struct BST<Data>::NodeLnk * const&node) const noexcept {
    struct BST<Data>::NodeLnk* const* pointer = &node;
    struct BST<Data>::NodeLnk* current = node;

    if(current!=nullptr) {
        while (current->HasRightChild()) {
            pointer = &current->rightchild;
            current = current->rightchild;
        }
    }
    return *pointer;
}

template <typename Data>
struct BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(struct BST<Data>::NodeLnk*& node) noexcept {
    return const_cast<struct BST<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
}

template <typename Data>
struct BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(struct BST<Data>::NodeLnk*& node) noexcept {
    return const_cast<struct BST<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

/* ************************************************************************ */

template <typename Data>
struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(struct BST<Data>::NodeLnk * const&node, const Data& dato) const noexcept {
    struct BST<Data>::NodeLnk* const* pointer = &node;
    struct BST<Data>::NodeLnk* current = node;

    if(current!=nullptr) {
        while (current!=nullptr && current->element!=dato) {
            if(current->element > dato) {
                pointer = &current->leftchild;
                current = current->leftchild;
            }else if(current->element < dato){
                pointer = &current->rightchild;
                current = current->rightchild;
            }
        }
    }
    return *pointer;
}

template <typename Data>
struct BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(struct BST<Data>::NodeLnk*& node, const Data& dato) noexcept {
    return const_cast<struct BST<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, dato));
}

/* ************************************************************************ */

template <typename Data>
struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(struct BST<Data>::NodeLnk * const&node, const Data &dato) const noexcept {

    struct BST<Data>::NodeLnk* const* candidate = nullptr;
    struct BST<Data>::NodeLnk* const* current = &node;
    
    while(*current!=nullptr && (*current)->element!=dato) {
        if((*current)->element < dato) {
            candidate = current;
            current = &((*current)->rightchild);
        }else if((*current)->element > dato)
            current = &((*current)->leftchild);
    }

    if(*current!=nullptr && (*current)->leftchild!=nullptr)
        return FindPointerToMax((*current)->leftchild);
    
    return *candidate;
}

template <typename Data>
struct BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(struct BST<Data>::NodeLnk * const&node, const Data &dato) const noexcept {
    
    struct BST<Data>::NodeLnk* const* candidate = nullptr;
    struct BST<Data>::NodeLnk* const* current = &node;
    
    while(*current!=nullptr && (*current)->element!=dato) {
        if((*current)->element < dato)
            current = &((*current)->rightchild);
        else if((*current)->element > dato){
            candidate = current;
            current = &((*current)->leftchild);
        }
    }

    if(*current!=nullptr && (*current)->rightchild!=nullptr)
        return FindPointerToMin((*current)->rightchild);
    
    return *candidate; 
}

template <typename Data>
struct BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(struct BST<Data>::NodeLnk*& node, const Data &dato) noexcept {
    return const_cast<struct BST<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, dato));
}

template <typename Data>
struct BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(struct BST<Data>::NodeLnk*& node, const Data &dato) noexcept {
    return const_cast<struct BST<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, dato));
}

/* ************************************************************************** */

}