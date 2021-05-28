
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../matrix/matrix.hpp"
#include "../matrix/vec/matrixvec.hpp"
#include "../matrix/csr/matrixcsr.hpp"

#include <vector>

/* ************************************************************************** */

//Final Test
void test();

//Menù
template<typename Data>
void matrixMenu(lasd::Matrix<Data> &);

/* ************************************************************************** */

//Selector
int selectStruct();
int selectType();
int selectSizeRow();
int selectSizeCol();
int selectSize(ulong);

/* ************************************************************************** */

//Populate
template<typename Data>
void populateRandomLinearContainer(lasd::List<Data> &lst, int initialSize);

/* ************************************************************************** */

//IfExist
template<typename Data>
void ifExists(const lasd::TestableContainer<Data> &bt);

/* ************************************************************************** */

//Parte 5: calculator application
template<typename Data>
void foldFunction(const Data &, const void *, void *) noexcept;

//Parte 6: function application
template<typename Data>
void applicationFunction(Data &, void*);

/* ************************************************************************** */

//Other
std::string generateString(int len);

template<typename Data>
void stampavalore(Data &, void*);

//Generate Random Data
template<typename Data>
std::vector<Data> generateRandomData(int size);

template<>
std::vector<int> generateRandomData(int size);

template<>
std::vector<float> generateRandomData(int size);

template<>
std::vector<std::string> generateRandomData(int size);

//Type checking
template <typename Data>
inline bool isString(Data& t) { return false; } // normal case returns false

template <> 
inline bool isString<std::string>(std::string& t) { return true; }

template <typename Data>
inline bool isInt(Data& t) { return false; } // normal case returns false

template <> 
inline bool isInt<int>(int& t) { return true; }

template <typename Data>
inline bool isFloat(Data& t) { return false; } // normal case returns false

template <> 
inline bool isFloat<float>(float& t) { return true; }

/* ************************************************************************** */

#endif
