#include "test.hpp"

#include "../matrix/matrix.hpp"
#include "../matrix/vec/matrixvec.hpp"
#include "../matrix/csr/matrixcsr.hpp"

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
                //Inizializzazione
                exit = true;
            } while (!exit);
    }

     template<typename Data>
    void matrixMenu(lasd::Matrix<Data> &mat) {
        int choose = 0;

        do {
                std::cout << "---------------Menù Matrice---------------" << std::endl;
                std::cout << "1) Visualizzazione tramite Map." << std::endl;
                std::cout << "2) Controllo di esistenza." << std::endl;
                std::cout << "3) Punto 5 dei TEST." << std::endl;
                std::cout << "4) Punto 6 dei TEST." << std::endl;
                std::cout << "5) Lettura di una cella." << std::endl;
                std::cout << "6) Scrittura di una cella." << std::endl;
                std::cout << "7) Controllo di una cella." << std::endl;
                std::cout << "8) Resize Riga." << std::endl;
                std::cout << "9) Resize Colonna."<< std::endl;
                std::cout << "------------Scelga un'opzione------------" << std::endl;
                std::cin >> choose;
                
                switch (choose) {
                case 1:
                    
                    break;

                case 2:

                    break;

                case 3:
                    
                    break;
                
                case 4:
                    
                    break;
                
                case 5:
                    
                   break;
                
                case 6:

                    break;
                
                case 7:
                    
                    break; 
                
                case 8:
                    
                    break;

                case 9:

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
            std::cout << "0): MatrixVEC, 1): MatrixCSR;"<<std::endl;
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

    int selectSizeRow() {
        int result = -1;
        while (result < 1 || result > 10) {
            std::cout << "Inserisci il numero di righe per la matrice (1-10): ";
            std::cin >> result;
        }
        return result;
    }

    int selectSizeCol() {
        int result = -1;
        while (result < 1 || result > 10) {
            std::cout << "Inserisci il numero di colonne per la matrice (1-10): ";
            std::cin >> result;
        }
        return result;
    }

    int selectSize(ulong size) {
        int result = -1;
        while (result < 1 || result > size) {
            std::cout << "Inserisci la quantità di dati per popolare la struttura (1-"+std::to_string(size)+"): ";
            std::cin >> result;
        }
        return result;
    }


/* ************************************************************************** */
    
    //Populate
    template<typename Data>
    void populateRandomLinearContainer(lasd::List<Data> &lst, int initialSize) {
        for(Data d : generateRandomData<Data>(initialSize))
            lst.InsertAtBack(d);
    }

/* ************************************************************************** */

    //IfExist
    template<typename Data>
    void ifExists(const lasd::TestableContainer<Data> &bt) {
        Data value;
        bool resta = false;
        do {
            std::cout << "Inserisci il valore che vuoi controllare: ";
            std::cin >> value;

            std::string text = bt.Exists(value) ? ("L'elemento è nel albero.") : ("L'elemento non è nel albero.");

            std::cout << text << std::endl;

            std::cout << "Vuoi controllare un altro elemento? (y/n): ";

            char res;
            std::cin >> res;

            resta = (res == 'y');
        } while (resta);
    }

/* ************************************************************************** */

    //Parte 5: utilizzo di fold
    template<typename Data>
    void foldFunction(const Data &, const void *n, void *result) noexcept{
        int value = *((int *) n);
    }

    template<>
    void foldFunction(const int &data, const void *n, void *result) noexcept{
        if (data < *((int *) n))
            *((int *) result) *= data;
    }

    template<>
    void foldFunction(const float &data, const void *n, void *result) noexcept{
        if (data > *((int *) n))
            *((float *) result) += data;
    }

    template<>
    void foldFunction(const std::string &data, const void *n, void *result) noexcept{
        if (data.length() <= *((int *) n))
            ((std::string *) result)->append(data);
    }

    //Parte 6: function application
    template<typename Data>
    void applicationFunction(Data &dato, void*){}

    template<>
    void applicationFunction(int &dato, void*){
        dato = dato * 2;
    }

    template<>
    void applicationFunction(float &dato, void*){
        dato = pow(-dato,3);
    }

    template<>
    void applicationFunction(std::string &dato, void* str){
        dato = *((std::string *) str) + dato;
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
    void stampavalore(Data &dato, void*){
        std::cout<< dato << " ";
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

