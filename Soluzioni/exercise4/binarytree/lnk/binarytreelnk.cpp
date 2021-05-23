#include <stdexcept>

namespace lasd {

/* ************************************************************************** */
/*                              NODE  LINK                                    */
/* ************************************************************************** */

//Constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data &dato) {
    element=dato;
    leftchild = nullptr;
    rightchild = nullptr;
}

//Destructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete leftchild;
    delete rightchild;
}

// Specific member functions
template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return element;
}

template <typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return element;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return (leftchild!=nullptr);
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return (rightchild!=nullptr);
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    if(leftchild==nullptr)
        throw std::out_of_range("Access to an empty child.");

    return *leftchild;
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    if(rightchild==nullptr)
        throw std::out_of_range("Access to an empty child.");

    return *rightchild;
}

/* ************************************************************************** */
/*                              TREE  LINK                                    */
/* ************************************************************************** */

//Funzioni accessorie
template <typename Data>
void BinaryTreeLnk<Data>::funzioneCostruzione(int indice, struct BinaryTreeLnk<Data>::NodeLnk *nodo, const LinearContainer<Data> &con) {
    if( (indice*2 + 1) <= (con.Size()-1)){
        nodo->leftchild = new NodeLnk(con[indice*2 + 1]);
        funzioneCostruzione(indice*2 + 1, nodo->leftchild, con);
    }

    if( (indice*2 + 2) <= (con.Size()-1)){
        nodo->rightchild = new NodeLnk(con[indice*2 + 2]);
        funzioneCostruzione(indice*2 + 2, nodo->rightchild, con);
    }
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::copyTree(NodeLnk *toBeCopied) {
    NodeLnk* nodo = nullptr;

    if(toBeCopied!=nullptr){
        nodo = new NodeLnk(toBeCopied->element);

        if(toBeCopied->leftchild!=nullptr)
            nodo->leftchild = copyTree(toBeCopied->leftchild);

        if(toBeCopied->rightchild!=nullptr)
            nodo->rightchild = copyTree(toBeCopied->rightchild);
    }

    return nodo;
}

/* ************************************************************************** */

// Specific constructors
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data> &con) {
    size = con.Size();
    root = new BinaryTreeLnk<Data>::NodeLnk(con[0]);
    funzioneCostruzione(0, root, con);
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> &bt) {
    size=bt.size;

    if(size>0)
        root = copyTree(bt.root);
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> &&bt) noexcept : BinaryTreeLnk<Data>()  {
    std::swap(root,bt.root);
    std::swap(size,bt.size);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    Clear();
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data> &bt) {
    if(bt.size!=0){
        BinaryTreeLnk<Data>* tmpbt = new BinaryTreeLnk<Data>(bt);
	    std::swap(*tmpbt, *this);
	    delete tmpbt;
    }else{
        Clear();
    }
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data> &&bt) noexcept {
    std::swap(root,bt.root);
    std::swap(size,bt.size);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data> &bt) const noexcept {
    return BinaryTree<Data>::operator==(bt);
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data> &bt) const noexcept {
    return !(*this == bt);
}

/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree)
template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    if(root==nullptr)
        throw std::length_error("Access to an empty tree.");

    return *root;
}
/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void BinaryTreeLnk<Data>::Clear() {
    size=0;
    delete root;
    root = nullptr;
}

/* ************************************************************************** */

}
