#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

// Constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR() {
    rowVector.Resize(1);
    rowVector[0] = &head;
}

/* ************************************************************************ */

// Specific constructors
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const ulong i, const ulong j) {
    rowSize = i;
    colSize = j;
    rowVector.Resize(i+1);

    for (ulong index = 0; index <= rowSize; index++) {
        rowVector[index] = &head;
    }
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data> &matrix) : MatrixCSR(matrix.rowSize, matrix.colSize) {
    for (ulong i = 0; i < rowSize; i++) {
        for(Node** curr = matrix.rowVector[i]; curr != matrix.rowVector[i+1]; curr = &(*curr)->next) {
            Node& node = **curr;
            (*this)(i,node.info.second) = node.info.first;
        }
    }
}

// Move constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data> &&matrix) noexcept : MatrixCSR(matrix.rowSize, matrix.colSize) {
    std::swap(rowSize,matrix.rowSize);
    std::swap(colSize,matrix.colSize);
    std::swap(rowVector,matrix.rowVector);
    std::swap(head,matrix.head);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
MatrixCSR<Data>::~MatrixCSR() {
    Clear();
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data> &matrix) {
    MatrixCSR<Data>* tmpmat = new MatrixCSR<Data>(matrix);
	std::swap(*tmpmat, *this);
	delete tmpmat;
    return *this;
}

// Move assignment
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data> &&matrix) noexcept {
    std::swap(rowSize,matrix.rowSize);
    std::swap(colSize,matrix.colSize);
    std::swap(rowVector,matrix.rowVector);
    for (ulong index = 0; (index < size) && (rowVector[index]==&matrix.head); index++) {
        rowVector[index] = &head;
    }
    for (ulong index = 0; (index < matrix.size) && (matrix.rowVector[index]==&head); index++) {
        matrix.rowVector[index] = &matrix.head;
    } 
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR<Data> &matrix) const noexcept {
    if((rowSize == matrix.rowSize) && (colSize==matrix.colSize))
        return List<std::pair<Data,ulong>>::operator==(matrix);
    
    return false;
}

template <typename Data>
bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data> &matrix) const noexcept {
    return !(*this == matrix);
}

/* ************************************************************************ */

// Specific member functions (inherited from Matrix)

template <typename Data>
void MatrixCSR<Data>::RowResize(const ulong newRow) {
    if(newRow == 0) {
        List<std::pair<Data,ulong>>::Clear();
        rowSize = 0;
        rowVector.Resize(1);
        return;
    }

    if(newRow > rowSize) {
        rowVector.Resize(newRow+1);
        
        for(ulong i = rowSize+1; i <= newRow; i++)
            rowVector[i] = rowVector[rowSize];

    }else if(newRow < rowSize) {
        Node* ptr = *rowVector[newRow]; 
        while (ptr != nullptr) {
				Node *tmp = ptr;
				ptr = ptr->next;
                size--;
				delete tmp;
		}

    rowVector.Resize(newRow+1);

    }
    rowSize = newRow;
}

template <typename Data>
void MatrixCSR<Data>::ColumnResize(const ulong newCol) {
     if(newCol ==0){
        List<std::pair<Data,ulong>>::Clear();
    }else if(newCol < colSize){
        ulong index = 1;
        Node** ptr = &head;
        while(index <= rowSize) {
            Node* nodo;
            Node** exit = rowVector[index];
            while(ptr != exit && (*ptr)->info.second < newCol) {
                nodo = *ptr;
                ptr = &(nodo->next);
            }
            if(ptr != exit) {
                Node* tmp = *ptr;
                *ptr = *exit;
                *exit = nullptr;
                for(Node* ptr = tmp; ptr != nullptr; ptr = ptr->next) {size --;}
                delete tmp;
            }
            for (;index<=rowSize && rowVector[index] == exit; index++)
                rowVector[index]=ptr;
        }
      }
    colSize = newCol;
}

template <typename Data>
bool MatrixCSR<Data>::ExistsCell(const ulong i, const ulong j) const noexcept {
    if((i >= rowSize) && (j >= colSize))
        return false;

    Node** curr = rowVector[i];

    while((curr!=rowVector[i+1]) && ((*curr)->info.second!=j)) {
        if((*curr)->info.second == j)
            return true;

        curr = &((*curr)->next);
    }

    return false;
}

template <typename Data>
Data& MatrixCSR<Data>::operator()(const ulong i, const ulong j) {
    if((i >= rowSize) && (j >= colSize))
        throw std::out_of_range("Access to a out of range row/column.");

    Node** curr = rowVector[i];
    Node** exit = rowVector[i+1];
    
    while (curr!=exit && (*curr)->info.second < j) {
        if((*curr)->info.second == j)
            return (*curr)->info.first;

        curr = &(*curr)->next;
    }

    Node* tmp = *curr;
    *curr = new Node();
    (*curr)->info.second = j;
    (*curr)->next = tmp;

    if(curr==exit) {
        ulong index = i+1;
        for(Node** ptr = exit; (*ptr!=nullptr) && (ptr==exit); ptr = &(*ptr)->next) {
            rowVector[index] = &(*curr)->next;
            index++;
        }
    }

    return (*curr)->info.first;
}

template <typename Data>
const Data& MatrixCSR<Data>::operator()(const ulong i, const ulong j) const {
    if((i >= rowSize) && (j >= colSize))
        throw std::out_of_range("Access to a out of range row/column.");
    
    Node** curr = rowVector[i];
    Node** exit = rowVector[i+1];

    while((curr!=exit) && ((*curr)->info.second!=j)) {
        if((*curr)->info.second == j)
            return (*curr)->info.first;

        curr = &((*curr)->next);
    }

    throw std::length_error("The cell does not exist.");
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void MatrixCSR<Data>::Clear() {
    if(head!=nullptr){
        List<std::pair<Data,ulong>>::Clear();
        rowVector.Resize(1);
        rowVector[0] = &head;
        rowSize = 0;
        colSize = 0;
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void* param) {
    List<std::pair<Data,ulong>>::MapPreOrder(
        [&fun](std::pair<Data,ulong>& data, void* parametro) { fun(data.first, parametro); }
        ,param);
}

template <typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* param) {
    List<std::pair<Data,ulong>>::MapPostOrder(
        [&fun](std::pair<Data,ulong>& data, void* parametro) { fun(data.first, parametro); }
        ,param);
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
  
template <typename Data>
void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* param, void* acc) const {
    List<std::pair<Data,ulong>>::FoldPreOrder(
        [&fun](const std::pair<Data,ulong>& data, const void* parametro, void* accumulatore) { fun(data.first, parametro, accumulatore); }
        ,param
        ,acc);
}

template <typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* param, void* acc) const {
    List<std::pair<Data,ulong>>::FoldPostOrder(
        [&fun](const std::pair<Data,ulong>& data, const void* parametro, void* accumulatore) { fun(data.first, parametro, accumulatore); }
        ,param
        ,acc);
}

/* ************************************************************************** */

}
