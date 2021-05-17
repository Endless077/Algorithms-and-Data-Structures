
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../vector/vector.hpp"
#include "../list/list.hpp"

//#ifndef uvar
//#define uint unsigned int
//#define ulong unsigned long
//#endif

/* ************************************************************************** */

//Final Test
void test();

//Menù
template<typename Data>
void vectorMenu(lasd::Vector<Data> &);

template<typename Data>
void listMenu(lasd::List<Data> &);

/* ************************************************************************** */

//Selector
int selectStruct();
int selectType();
int selectSize();

/* ************************************************************************** */

//Population Vector
template<typename Data>
void populationRandomVector(lasd::Vector<Data> &data);

template<>
void populationRandomVector(lasd::Vector<int> &data);

template<>
void populationRandomVector(lasd::Vector<float> &data);

template<>
void populationRandomVector(lasd::Vector<std::string> &data);

/******************************************************************************/

//Population List
template<typename Data>
void populationRandomList(lasd::List<Data> &data, int s);

template<>
void populationRandomList(lasd::List<int> &data, int size);

template<>
void populationRandomList(lasd::List<float> &data, int size);

template<>
void populationRandomList(lasd::List<std::string> &data, int size);

/* ************************************************************************** */

//Front/Back/Index
template<typename Data>
void visualizzaFrontBackIndex(const lasd::LinearContainer<Data> &container);

/* ************************************************************************** */

//Exists
template<typename Data>
void ifExists(const lasd::TestableContainer<Data> &container);

/* ************************************************************************** */

//Parte 6: utilizzo di fold
template<typename Data>
void foldFunction(const Data &, const void *, void *) noexcept;

//Parte 7: function application
template<typename Data>
void applicationFunction(Data &, void*);

/* ************************************************************************** */

//Other
std::string generateString(int len);

template<typename Data>
inline void stampavalore(Data &dato, void*);


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