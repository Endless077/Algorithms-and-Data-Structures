
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../container/container.hpp"
#include "../stack/stack.hpp"
#include "../queue/queue.hpp"

#include <vector>

/* ************************************************************************** */

//Final Test
void test();

//Menù
template<typename Data>
void stackMenu(lasd::Stack<Data> &);

template<typename Data>
void queueMenu(lasd::Queue<Data> &);

/* ************************************************************************** */

//Selector
int selectStruct();
int selectBaseStruct();
int selectType();
int selectSize();

/* ************************************************************************** */

//Populate Stack
template<typename Data>
void populateRandomStack(lasd::Stack<Data> &stk, int initialSize);

//Populate Queue
template<typename Data>
void populateRandomQueue(lasd::Queue<Data> &que, int initialSize);

/******************************************************************************/

//Insert
template<typename Data>
void pushIn(lasd::Stack<Data> &);

template<typename Data>
void enqueueIn(lasd::Queue<Data> &);

//Remove
template<typename Data>
void popOut(lasd::Stack<Data> &);

template<typename Data>
void dequeueOut(lasd::Queue<Data> &);

//Access to first immediate element
template<typename Data>
void topView(lasd::Stack<Data> &);

template<typename Data>
void frontView(lasd::Queue<Data> &);

//Access to first immediate element and remove
template<typename Data>
void topRemove(lasd::Stack<Data> &);

template<typename Data>
void frontRemove(lasd::Queue<Data> &);


/******************************************************************************/

//Other
std::string generateString(int len);

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
