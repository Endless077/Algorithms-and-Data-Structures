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
MatrixVec<Data>::MatrixVec(const MatrixVec<Data> &matrix) : Vector<Data>(matrix) {
    rowSize = matrix.rowSize;
    colSize = matrix.colSize;
}

// Move constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec<Data> &&matrix) noexcept : Vector<Data>(std::move(matrix)){
    std::swap(rowSize,matrix.rowSize);
    std::swap(colSize,matrix.colSize);    
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
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data> &matrix) {
    MatrixVec<Data>* tmpmat = new MatrixVec<Data>(matrix);
	std::swap(*tmpmat, *this);
	delete tmpmat;
	return *this;
}

// Move assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& matrix) noexcept {
    Vector<Data>::operator=(std::move(matrix));
    std::swap(rowSize,matrix.rowSize);
    std::swap(colSize,matrix.colSize);    
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data> &matrix) const noexcept {
    if(rowSize==matrix.rowSize && colSize==matrix.colSize)
        return Vector<Data>::operator==(matrix);

    return false;
}

template <typename Data>
bool MatrixVec<Data>::operator!=(const MatrixVec<Data>  &matrix) const noexcept {
    return !(*this == matrix);
}

/* ************************************************************************ */

// Specific member functions (inherited from Matrix)

template <typename Data>
void MatrixVec<Data>::RowResize(const ulong newRow) {
    Vector<Data>::Resize(newRow*colSize);
    rowSize = newRow;
}

template <typename Data>
void MatrixVec<Data>::ColumnResize(const ulong newCol) {
    if (newCol == 0) {
        Clear();
        return;
    }
    
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
    if(i >= rowSize && j >= colSize)
        return false;
    
    return true;
}

template <typename Data>
Data& MatrixVec<Data>::operator()(const ulong i, const ulong j) {
    return const_cast<Data&>(static_cast<const MatrixVec<Data> *>(this)->operator()(i,j));
}

template <typename Data>
const Data& MatrixVec<Data>::operator()(const ulong i, const ulong j) const {
    //Exception std::out_of_range throw by Vector.
    return Vector<Data>::operator[](i*colSize+j);
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void MatrixVec<Data>::Clear() {
    if(size>0) {
        Vector<Data>::Clear();
        rowSize = 0;
        colSize = 0;
    }
}

/* ************************************************************************** */

}
