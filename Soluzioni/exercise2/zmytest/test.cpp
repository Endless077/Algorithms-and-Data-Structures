#include "test.hpp"

#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <iomanip>

/* ************************************************************************** */

//Menù
void test() {
    std::cout<<"Menù del test dello studente:"<<std::endl;
    bool exit = false;
     do {
            int selectedStruct = selectStruct();
            int selectedType = selectType();
            int selectedSize = selectSize();

            if (selectedStruct == 0) {
                if (selectedType == 0) {
                    lasd::StackVec<int> stkvI;
                    populateRandomStack(stkvI,selectedSize);
                    stackMenu(stkvI);

                } else if (selectedType == 1) {
                    lasd::StackVec<float> stkvF;
                    populateRandomStack(stkvF,selectedSize); 
                    stackMenu(stkvF);

                } else if (selectedType == 2) {
                    lasd::StackVec<std::string> stkvS;
                    populateRandomStack(stkvS,selectedSize);
                    stackMenu(stkvS);
                    
                }
            } else if (selectedStruct == 1) {
                if (selectedType == 0) {
                    lasd::StackLst<int> stklI;
                    populateRandomStack(stklI,selectedSize);
                    stackMenu(stklI);

                } else if (selectedType == 1) {
                    lasd::StackLst<float> stklF;
                    populateRandomStack(stklF,selectedSize);
                    stackMenu(stklF);
                    
                } else if (selectedType == 2) {
                    lasd::StackLst<std::string> stklS;
                    populateRandomStack(stklS,selectedSize);
                    stackMenu(stklS);

                }
            } else if (selectedStruct == 2) {
                 if (selectedType == 0) {
                    lasd::QueueVec<int> quevI;
                    populateRandomQueue(quevI,selectedSize);
                    queueMenu(quevI);
                    
                } else if (selectedType == 1) {
                    lasd::QueueVec<float> quevF;
                    populateRandomQueue(quevF,selectedSize);
                    queueMenu(quevF);
                    
                } else if (selectedType == 2) {
                    lasd::QueueVec<std::string> quevS;
                    populateRandomQueue(quevS,selectedSize);
                    queueMenu(quevS);

                }
            } else if (selectedStruct == 3) {
                 if (selectedType == 0) {
                    lasd::QueueLst<int> quelI;
                    populateRandomQueue(quelI,selectedSize);
                    queueMenu(quelI);
                    
                } else if (selectedType == 1) {
                    lasd::QueueLst<float> quelF;
                    populateRandomQueue(quelF,selectedSize);
                    queueMenu(quelF);

                } else if (selectedType == 2) {
                    lasd::QueueLst<std::string> quelS;
                    populateRandomQueue(quelS,selectedSize);
                    queueMenu(quelS);

                }
            }
            exit = true;
        } while (!exit);
}

//Menù
template<typename Data>
void stackMenu(lasd::Stack<Data> &stk) {
    int choose = 0;
    do {
        std::cout << "---------------Menù Stack---------------" << std::endl;
        std::cout << "1) Inserimento." << std::endl;
        std::cout << "2) Rimozione." << std::endl;
        std::cout << "3) Lettura distruttiva." << std::endl;
        std::cout << "4) Lettura non distruttiva." << std::endl;
        std::cout << "5) Test di vuotezza." << std::endl;
        std::cout << "6) Size." << std::endl;
        std::cout << "7) Svuotamento dello struttura." << std::endl;
        std::cout << "0) Indietro." << std::endl;
        std::cout << "------------Scelga un'opzione------------" << std::endl;
        std::cin >> choose;

        switch (choose) {
            case 1:
                pushIn(stk);
                break;

            case 2:
                if(stk.Empty())
                    std::cout << "Lo Stack è vuoto." << std::endl;
                else
                    popOut(stk);
                break;

            case 3:
                if(stk.Empty())
                    std::cout << "Lo Stack è vuoto." << std::endl;
                else
                    topRemove(stk);
                break;
            
            case 4:
                if(stk.Empty())
                    std::cout << "Lo Stack è vuoto." << std::endl;
                else
                    topView(stk);
                break;
            
            case 5:
                if(stk.Empty()){
                    std::cout << "Lo Stack è vuoto." << std::endl;
                }else{
                    std::cout << "Lo Stack non è vuoto." << std::endl;
                }
                break;
            
            case 6:
                std::cout << "Size della struttura" << std::endl;
                std::cout << stk.Size() << std::endl;
                break;
            
            case 7:
                std::cout << "Clear della struttura" << std::endl;
                stk.Clear();
                break; 
            
        }

    } while (choose != 0);
}

template<typename Data>
void queueMenu(lasd::Queue<Data> &que) {
    int choose = 0;
    do {
        std::cout << "----------------Menù Queue----------------" << std::endl;
        std::cout << "1) Inserimento." << std::endl;
        std::cout << "2) Rimozione." << std::endl;
        std::cout << "3) Lettura distruttiva." << std::endl;
        std::cout << "4) Lettura non distruttiva." << std::endl;
        std::cout << "5) Test di vuotezza." << std::endl;
        std::cout << "6) Size." << std::endl;
        std::cout << "7) Svuotamento della struttura." << std::endl;
        std::cout << "0) Indietro." << std::endl;
        std::cout << "------------Scelga un'opzione------------" << std::endl;
        std::cin >> choose;

        switch (choose) {
            case 1:
                enqueueIn(que);
                break;

            case 2:
                if(que.Empty())
                    std::cout << "La Queue è vuota." << std::endl;
                else
                    dequeueOut(que);
                break;

            case 3:
                if(que.Empty())
                    std::cout << "La Queue è vuota." << std::endl;
                else
                    frontRemove(que);
                break;
            
            case 4:
                if(que.Empty())
                    std::cout << "La Queue è vuota." << std::endl;
                else
                    frontView(que);
                break;
            
            case 5:
                if(que.Empty()){
                    std::cout << "La Queue è Vuota." << std::endl;
                }else{
                    std::cout << "La Queue non è Vuota." << std::endl;
                }
                break;
            
            case 6:
                std::cout << "Size della struttura" << std::endl;
                std::cout << que.Size() << std::endl;
                break;
            
            case 7:
                std::cout << "Clear della struttura" << std::endl;
                que.Clear();
                break; 
            
        }

    } while (choose != 0);
}

 /* ************************************************************************** */

    //Selector

    int selectStruct() {
        int result = -1;
        while (result < 0 || result > 4) {
            std::cout << "Inserisci la struttura:"<<std::endl;
            std::cout << "0): StackVector, 1): StackQueue, 2): QueueVec, 3): QueueQueue;"<<std::endl;
            std::cin >> result;
        }
        return result;
    }

    int selectType() {
        int result = -1;
        while (result < 0 || result > 2) {
            std::cout << "Inserisci il tipo (0: int, 1: float, 2: string): ";
            std::cin >> result;
        }
        return result;
    }

    int selectSize() {
        int result = -1;
        while (result < 1 || result > 10) {
            std::cout << "Inserisci la quantità di dati per popolare la struttura (1-10): ";
            std::cin >> result;
        }
        return result;
    }

 /* ************************************************************************** */

    //Population Stack
    template<typename Data>
    void populateRandomStack(lasd::Stack<Data> &stk, int size) {
    
        for(Data d : generateRandomData<Data>(size))
            stk.Push(d);

    }

    //Population Queue
    template<typename Data>
    void populateRandomQueue(lasd::Queue<Data> &que, int size) {

        for(Data d : generateRandomData<Data>(size))
            que.Enqueue(d);
    }

 /* ************************************************************************** */

    //Insert STACK
    template<typename Data>
    void pushIn(lasd::Stack<Data> &stk){
        Data value;
        bool resta = false;
        do {
            std::cout << "Inserisci il valore che inserire in stack: ";
            std::cin >> value;
            
            stk.Push(value);

            std::cout << "Vuoi aggiungere altro? (y/n): ";

            char res;
            std::cin >> res;

            resta = (res == 'y');
        } while (resta);
    }

    //Insert QUEUE
    template<typename Data>
    void enqueueIn(lasd::Queue<Data> &que){
        Data value;
        bool resta = false;
        do {
            std::cout << "Inserisci il valore che inserire in Queue: ";
            std::cin >> value;
            
            que.Enqueue(value);
            
            std::cout << "Vuoi aggiungere altro? (y/n): ";

            char res;
            std::cin >> res;

            resta = (res == 'y');
        } while (resta);
    }


 /* ************************************************************************** */

    //Remove STACK
    template<typename Data>
    void popOut(lasd::Stack<Data> &stk){
        std::cout << "In corso: Pop "<<std::endl;

        stk.Pop();
            
        std::cout << "Pop avvenuto con successo." << std::endl;
    }

    //Remove QUEUE
    template<typename Data>
    void dequeueOut(lasd::Queue<Data> &que){
        std::cout << "In corso: Dequeue "<<std::endl;

        que.Dequeue();
            
        std::cout << "Dequeue avvenuto con successo." << std::endl;
    }

 /* ************************************************************************** */

    //Access STACK
    template<typename Data>
    void topView(lasd::Stack<Data> &stk) {
        std::cout << "In corso: TOP "<<std::endl;

        std::cout << stk.Top() << std::endl;

        std::cout << "TOP avvenuto con successo." << std::endl;
    }

    //Access QUEUE
    template<typename Data>
    void frontView(lasd::Queue<Data> &que){
        std::cout << "In corso: Head "<<std::endl;

        std::cout << que.Head() << std::endl;

        std::cout << "Head avvenuto con successo." << std::endl;

    }

 /* ************************************************************************** */

    //Access and Remove STACK
    template<typename Data>
    void topRemove(lasd::Stack<Data> &stk){
        std::cout << "In corso: Top and Pop "<<std::endl;

        std::cout << stk.TopNPop() << std::endl;

        std::cout << "Top and Pop avvenuto con successo." << std::endl;
    }

    //Access and Remove QUEUE
    template<typename Data>
    void frontRemove(lasd::Queue<Data> &que){
        std::cout << "In corso: Top and POP "<<std::endl;

        std::cout << que.HeadNDequeue() << std::endl;

        std::cout << "Front and Dequeue avvenuto con successo." << std::endl;

    }

 /* ************************************************************************** */

    //Other
    std::string generateString(int len) {
        std::default_random_engine generator(len);
        std::uniform_int_distribution<char> distribution('a', 'z');

        char str[len + 1];
        for (unsigned int i = 0; i < len; ++i) {
            str[i] = distribution(generator);
        }
        str[len] = '\0';
        return str;
    }

    template<typename Data>
    std::vector<Data> generateRandomData(int size) {}

    template<>
    std::vector<int> generateRandomData(int size) {

        std::cout << "--- Inizio popolazione random INT---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distx(0, 100);

        std::vector<int> vec;

        for (uint i = 0; i < size; ++i)
            vec.push_back(distx(generator));

        std::cout << "---Popolazione random INT completata---" << std::endl;

        return vec;
    }

    template<>
    std::vector<float> generateRandomData(int size) {

        std::cout << "---Inizio popolazione random FLOAT---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_real_distribution<double> distx(1.0, 100.0);

        std::vector<float> vec;

        for (uint i = 0; i < size; ++i) {
            std::cout << std::fixed << std::setprecision(2);
            vec.push_back(distx(generator));
        }

        std::cout << "---Popolazione random FLOAT completata---" << std::endl;

        return vec;
    }

    template<>
    std::vector<std::string> generateRandomData(int size) {

        std::cout << "---Inizio popolazione random STRING---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distx(0, 10);

        std::vector<std::string> vec;

        for (uint i = 0; i < size; ++i)
            vec.push_back(generateString(distx(generator)));

        std::cout << "---Popolazione random STRING completata---" << std::endl;

        return vec;
    }

 /* ************************************************************************** */