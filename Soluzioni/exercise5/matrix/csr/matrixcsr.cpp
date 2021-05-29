#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

// Constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR() : rowVector(1) {
    rowVector[0] = &head;
}

/* ************************************************************************ */

// Specific constructors
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const ulong i, const ulong j) {
    rowSize = i;
    colSize = j;
    rowVector.Resize(i+1);

    for (ulong index = 0; index <= rowSize; index++)
        rowVector[index] = &head;
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data> &inMatrix) : MatrixCSR(inMatrix.rowSize, inMatrix.colSize) {
    for (ulong i = 0; i < rowSize; i++) {
        for(Node** curr = inMatrix.rowVector[i]; curr != inMatrix.rowVector[i+1]; curr = &((*curr)->next)) {
            Node& node = **curr;
            (*this)(i,node.info.second) = node.info.first;
        }
    }
}

// Move constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data> &&inMatrix) noexcept : MatrixCSR() {
    std::swap(rowSize,inMatrix.rowSize);
    std::swap(colSize,inMatrix.colSize);
    std::swap(size,inMatrix.size);
    std::swap(head,inMatrix.head);
    std::swap(rowVector,inMatrix.rowVector);

    for (ulong index = 0; (index < size) && (rowVector[index]==&inMatrix.head); index++)
        rowVector[index] = &head;
    
    inMatrix.rowVector[0] = &inMatrix.head;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data> &inMatrix) {
    MatrixCSR<Data>* tmpmat = new MatrixCSR<Data>(inMatrix);
	std::swap(*tmpmat, *this);
	delete tmpmat;
    return *this;
}

// Move assignment
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data> &&inMatrix) noexcept {
    std::swap(rowSize,inMatrix.rowSize);
    std::swap(colSize,inMatrix.colSize);
    std::swap(size,inMatrix.size);
    std::swap(head,inMatrix.head);
    std::swap(rowVector,inMatrix.rowVector);

    for (ulong index = 0; (index < size) && (rowVector[index]==&inMatrix.head); index++)
        rowVector[index] = &head;

    for (ulong index = 0; (index < inMatrix.size) && (inMatrix.rowVector[index]==&head); index++)
        inMatrix.rowVector[index] = &inMatrix.head;

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR<Data> &inMatrix) const noexcept {
    //if((rowSize == inMatrix.rowSize) && (colSize == inMatrix.colSize))
    //    return List<std::pair<Data,ulong>>::operator==(inMatrix);
    
    //return false;

    if((rowSize == inMatrix.rowSize) && (colSize == inMatrix.colSize)) {
        if(rowSize == 0 && colSize == 0)
            return true;

        Node** ptrRow1;
        Node** ptrRow2;
        Node** ptrExit1;
        Node** ptrExit2;

        Node* nodo1;
        Node* nodo2;
        
        for(int index = 0; index < rowSize; index++) {
            ptrRow1 = rowVector[index];
            ptrRow2 = inMatrix.rowVector[index];
            ptrExit1 = rowVector[index+1];
            ptrExit2 = inMatrix.rowVector[index+1];

            while (ptrRow1 != ptrExit1 || ptrRow2 != ptrExit2) {
                nodo1 = *ptrRow1;
                nodo2 = *ptrRow2;

                if ((nodo1->info.first != nodo2->info.first) && (nodo1->info.second != nodo2->info.second))
                    return false;
                
                ptrRow1 = &(*ptrRow1)->next;
                ptrRow2 = &(*ptrRow2)->next;
            }

            if((ptrRow1 == ptrExit1 && ptrRow2 != ptrExit2) || (ptrRow1 != ptrExit1 && ptrExit2 == ptrExit2))
                return false;
        }
        
        return true;
    }
    return false;
}

template <typename Data>
bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data> &inMatrix) const noexcept {
    return !(*this == inMatrix);
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
        size = subListDelete(ptr, size);
        
        *rowVector[newRow] = nullptr;
    
        rowVector.Resize(newRow+1);
    }
    rowSize = newRow;
}

template <typename Data>
void MatrixCSR<Data>::ColumnResize(const ulong newCol) {
    if(newCol==0){
        List<std::pair<Data,ulong>>::Clear();
        colSize = 0;
        return;
    }
    
    if(newCol < colSize){
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
                size = subListDelete(tmp, size);
            }
            while (index <= rowSize && rowVector[index] == exit) {
                rowVector[index]=ptr;
                index++;
            }
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
    
    while (curr!=exit && (*curr)->info.second <= j) {
        if((*curr)->info.second == j)
            return (*curr)->info.first;  

        curr = &(*curr)->next;
    }

    Node* tmp = *curr;
    *curr = new Node();
    (*curr)->info.second = j;
    (*curr)->next = tmp;
    size++;
    
    if(curr==exit) {
        ulong index = i+1;
        while (index < rowSize && rowVector[index] == rowVector[index+1]) {   
            rowVector[index] = &(*curr)->next;
            index++;
        }
        rowVector[index] = &(*curr)->next;
    }

    return (*curr)->info.first;
}

template <typename Data>
const Data& MatrixCSR<Data>::operator()(const ulong i, const ulong j) const {
    if((i >= rowSize) && (j >= colSize))
        throw std::out_of_range("Access to a out of range row/column.");
    
    Node** curr = rowVector[i];
    Node** exit = rowVector[i+1];

    while((curr!=exit) && ((*curr)->info.second<=j)) {
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
        List<std::pair<Data,ulong>>::Clear();
        rowVector.Resize(1);
        rowSize = 0;
        colSize = 0;
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

template <typename Data>
ulong MatrixCSR<Data>::subListDelete(Node* nodo, ulong aggSize) {
    while(nodo != nullptr) {
        Node* aux = nodo->next; 
        delete nodo;
        nodo = nullptr;
        nodo = aux;
        aggSize --;
    }

    return aggSize;
}

/* ************************************************************************** */

}
