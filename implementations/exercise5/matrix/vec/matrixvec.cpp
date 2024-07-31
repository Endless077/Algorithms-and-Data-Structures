#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

// Constructor
template <typename Data>
MatrixVec<Data>::MatrixVec() : Vector<Data>(0){}

// Specific constructors
template <typename Data>
MatrixVec<Data>::MatrixVec(const ulong i, const ulong j) : Vector<Data>(i*j) {
    rowSize = i;
    colSize = j;
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(const MatrixVec<Data> &inMatrix) : Vector<Data>(inMatrix) {
    rowSize = inMatrix.rowSize;
    colSize = inMatrix.colSize;
}

// Move constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec<Data> &&inMatrix) noexcept : Vector<Data>(std::move(inMatrix)) {
    std::swap(rowSize,inMatrix.rowSize);
    std::swap(colSize,inMatrix.colSize);    
}

/* ************************************************************************ */

// Destructor
template <typename Data>
MatrixVec<Data>::~MatrixVec() {
    Clear();
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data> &inMatrix) {
    MatrixVec<Data>* tmpmat = new MatrixVec<Data>(inMatrix);
	std::swap(*tmpmat, *this);
	delete tmpmat;
	return *this;
}

// Move assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& inMatrix) noexcept {
    Vector<Data>::operator=(std::move(inMatrix));
    std::swap(rowSize,inMatrix.rowSize);
    std::swap(colSize,inMatrix.colSize);    
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data> &inMatrix) const noexcept {
    if(rowSize==inMatrix.rowSize && colSize==inMatrix.colSize)
        return Vector<Data>::operator==(inMatrix);

    return false;
}

template <typename Data>
bool MatrixVec<Data>::operator!=(const MatrixVec<Data>  &inMatrix) const noexcept {
    return !(*this == inMatrix);
}

/* ************************************************************************ */

// Specific member functions (inherited from Matrix)

template <typename Data>
void MatrixVec<Data>::RowResize(const ulong newRow) {
    if (newRow == 0) {
        Vector<Data>::Clear();
        rowSize = 0;
        return;
    }
    
    Vector<Data>::Resize(newRow*colSize);
    rowSize = newRow;
}

template <typename Data>
void MatrixVec<Data>::ColumnResize(const ulong newCol) {
    if (newCol == 0) {
        Vector<Data>::Clear();
        colSize = 0;
        return;
    }
        
    if(newCol==colSize)
        return;
    
    Data* TmpElements = new Data[newCol*rowSize] {};
    ulong curr = 0;
    ulong jump_curr = 0;

    if(newCol > colSize) {
        ulong jump = newCol - colSize;
    
        for(ulong i = 0; i<rowSize; i++){
            for(ulong j = 0; j<colSize; j++) {
                std::swap(Elements[curr], TmpElements[jump_curr]);
                curr++;
                jump_curr++;
            }
            jump_curr = jump_curr + jump;
        }

    }else if(newCol < colSize) {
        ulong jump = colSize - newCol;

        for(ulong i = 0; i<rowSize; i++){
            for(ulong j = 0; j<newCol; j++) {
                std::swap(Elements[jump_curr], TmpElements[curr]);
                curr++;
                jump_curr++;
            }
            jump_curr = jump_curr + jump;
        }
    }
    colSize = newCol;
    size = newCol*rowSize;

    std::swap(Elements, TmpElements);
    delete[] TmpElements;
}

template <typename Data>
bool MatrixVec<Data>::ExistsCell(const ulong i, const ulong j) const noexcept {
    return (i < rowSize) && (j < colSize);
}

template <typename Data>
Data& MatrixVec<Data>::operator()(const ulong i, const ulong j) {
    return const_cast<Data&>(static_cast<const MatrixVec<Data> *>(this)->operator()(i,j));
}

template <typename Data>
const Data& MatrixVec<Data>::operator()(const ulong i, const ulong j) const {
    if(!ExistsCell(i,j))
        throw std::out_of_range("Access index for the Matrix is out of range.");
    
    return Vector<Data>::operator[]((i*colSize)+j);
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void MatrixVec<Data>::Clear() {
    Vector<Data>::Clear();
    rowSize = 0;
    colSize = 0;
}

/* ************************************************************************** */

}
