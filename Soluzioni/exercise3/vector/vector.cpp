#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

//Costructor
template<typename Data>
Vector<Data>::Vector(const ulong newsize){
    Elements = new Data[newsize] {};
    size = newsize;
}

template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& con){
    size = con.Size();
    Elements = new Data[size];

    for (ulong index = 0; index < size; ++index){ 
        Elements[index] = con[index];
    }
}

/* ************************************************************************** */

//Copy costructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& vec) {
	Elements = new Data[vec.size];
	std::copy(vec.Elements, vec.Elements + vec.size, Elements);
	size = vec.size;
}

//Move costuctor
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
	std::swap(Elements, vec.Elements);
	std::swap(size, vec.size);
}

/* ************************************************************************** */

//Distructor
template<typename Data>
Vector<Data>::~Vector() {
	delete[] Elements;
}

/* ************************************************************************** */

//Copy assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
	Vector<Data>* tmpvec = new Vector<Data>(vec);
	std::swap(*tmpvec, *this);
	delete tmpvec;
	return *this;
}

//Move assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
	std::swap(Elements, vec.Elements);
	std::swap(size, vec.size);
	return *this;
}

/* ************************************************************************** */  

//Operator ==
template<typename Data>
bool Vector<Data>::operator==(const Vector& vec) const noexcept {
	if (size == vec.size) {
		for (ulong i = 0; i < size; ++i) {
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

//Operator !=
template<typename Data>
bool Vector<Data>::operator!=(const Vector& vec) const noexcept {
	return !(*this == vec);
}

/* ************************************************************************** */

//Resize
template<typename Data>
void Vector<Data>::Resize(const ulong newsize) {
    if (newsize == 0) {
        Clear();
    }else if (size != newsize) {
        ulong limit = (size < newsize) ? size : newsize;
        Data* TmpElements = new Data[newsize] {};
        for (ulong index = 0; index < limit; ++index) {
            std::swap(Elements[index], TmpElements[index]);
        }
        std::swap(Elements, TmpElements);
        size = newsize;
        delete[] TmpElements;
    }
}

/* ************************************************************************** */

//Clear
template<typename Data>
void Vector<Data>::Clear() {
	delete[] Elements;
	Elements = nullptr;
	size = 0;
}

/* ************************************************************************** */

//Front Access
template<typename Data>
Data& Vector<Data>::Front() const {
	if (size != 0) {
		return Elements[0];
	}
	else {
		throw std::length_error("Accesso ad un vettore vuoto.");
	}
}

//Back Access
template<typename Data>
Data& Vector<Data>::Back() const {
	if (size != 0) {
		return Elements[size - 1];
	}
	else {
	    throw std::length_error("Accesso ad un vettore vuoto.");
	}
}

//Access for []
template<typename Data>
Data& Vector<Data>::operator[](const ulong index) const {
  if (index < size) {
    return Elements[index];
  }
  else {
    throw std::out_of_range("Access at index " + std::to_string(index) + "; vector size " + std::to_string(size) + ".");
  }
}


/* ************************************************************************** */

//Vector MapPreOrder
template<typename Data>
void Vector<Data>::MapPreOrder(MapFunctor function, void* parametro) {
	for (ulong i = 0; i < size; ++i) {
		function(Elements[i], parametro);
	}
}

//Vector MapPostOrder
template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor function, void* parametro) {
	ulong index = size;
	while (index > 0) {
		function(Elements[--index], parametro);
	}
}

/* ************************************************************************** */

//Vector FoldPreOrder
template<typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor function, const void* parametro, void* accumulatore) const {
	for (ulong i = 0; i < size; ++i) {
		function(Elements[i], parametro, accumulatore);
	}
}

//Vector FoldPostOrder
template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor function, const void* parametro, void* accumulatore) const {
	ulong index = size;
	while (index > 0) {
		function(Elements[--index], parametro, accumulatore);
	}
}

/* ************************************************************************** */

}
