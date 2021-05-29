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
                int selectedStruct = selectStruct();
                int selectedType = selectType();
                int numRow = selectSizeRow();
                int numCol = selectSizeCol();
                int selectedSize = selectSize(numRow*numCol);

                if (selectedStruct == 0) {
                    if (selectedType == 0) {
                        lasd::List<int> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::MatrixVec<int> mat(numRow,numCol);
                        populateRandomMatrix(mat,lst);
                        matrixMenu(mat);

                    } else if (selectedType == 1) {
                        lasd::List<float> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::MatrixVec<float> mat(numRow,numCol);
                        populateRandomMatrix(mat,lst);
                        matrixMenu(mat);

                    } else if (selectedType == 2) {
                        lasd::List<std::string> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::MatrixVec<std::string> mat(numRow,numCol);
                        populateRandomMatrix(mat,lst);
                        matrixMenu(mat);

                    }
                } else if (selectedStruct == 1) {
                    if (selectedType == 0) {
                        lasd::List<int> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::MatrixCSR<int> mat(numRow,numCol);
                        populateRandomMatrix(mat,lst);
                        matrixMenu(mat);

                    } else if (selectedType == 1) {
                        lasd::List<float> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::MatrixCSR<float> mat(numRow,numCol);
                        populateRandomMatrix(mat,lst);
                        matrixMenu(mat);

                    } else if (selectedType == 2) {
                        lasd::List<std::string> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::MatrixCSR<std::string> mat(numRow,numCol);
                        populateRandomMatrix(mat,lst);
                        matrixMenu(mat);

                    }
                }
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
                std::cout << "9) Resize Colonna." << std::endl;
                std::cout << "0)Indietro." << std::endl;
                std::cout << "------------Scelga un'opzione------------" << std::endl;
                std::cin >> choose;
                
                switch (choose) {
                    case 1:
                        if(!mat.Empty()) {
                            visualizzaMatrix(mat);
                            std::cout << std::endl;
                        }else
                            std::cout << "La matrice è vuota." << std::endl;
                        break;

                    case 2:
                        ifExists(mat);
                        break;

                    case 3:
                        if (mat.Empty()) {
                            std::cout << "La matrice è vuota." << std::endl;
                        } else {
                            int n;
                            std::cout << "Inserisci il valore di n per la funzione (dipende dal tipo di matrice creata): ";
                            std::cin >> n;

                            if(isInt(mat(0,0))){
                                int result=1;
                                mat.FoldPreOrder(&foldFunction<Data>, &n, &result);
                                std::cout << "Risultato: " << result << std::endl;

                            }else if(isFloat(mat(0,0))){
                                float result=1;
                                mat.FoldPreOrder(&foldFunction<Data>, &n, &result);
                                std::cout << "Risultato: " << result << std::endl;

                            }else if(isString(mat(0,0))){
                                std::string result="";
                                mat.FoldPreOrder(&foldFunction<Data>, &n, &result);
                                std::cout << "Risultato: " << result << std::endl;
                            }
                        }
                        break;
                    
                    case 4:
                        if (mat.Empty()) {
                            std::cout << "La matrice è vuota." << std::endl;
                        } else {
                            std::cout << "---Verranno applicate modifiche a tutti gli elementi (dipende dal tipo di matrice)---" << std::endl;
                            if(isString(mat(0,0))){
                                std::cout << "Inserisci la stringa da concatenare: ";
                                std::string input;
                                std::cin >> input;
                                mat.MapPreOrder(&applicationFunction<Data>, &input);
                            }else{
                                mat.MapPreOrder(&applicationFunction<Data>, nullptr);
                            }
                            std::cout << "---Modifiche apportate (visualizzare la struttura per vederle)---" << std::endl;
                        }
                        break;
                    
                    case 5:
                        ifExistsCell(mat);
                        break;

                    case 6:
                        getCell(mat);
                        break;
                    
                    case 7:
                        ulong rowResize;
                        std::cout << "Scegli di quanto vuoi fare la resize delle righe, attualmente: "+std::to_string(mat.RowNumber()) << std::endl;
                        std::cin >> rowResize;
                        if(rowResize >= 0)
                            mat.RowResize(rowResize);
                        else
                            std::cout << "Scegliere un numero intero positivo (0 compreso)." << std::endl;
                        break; 
                    
                    case 8:
                        ulong colResize;
                        std::cout << "Scegli di quanto vuoi fare la resize delle colonne, attualmente: "+std::to_string(mat.ColumnNumber()) << std::endl;
                        std::cin >> colResize;
                        if(rowResize >= 0)
                            mat.ColumnResize(colResize);
                        else
                            std::cout << "Scegliere un numero intero positivo (0 compreso)." << std::endl;
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
            std::cout << "0): MatrixVec, 1): MatrixCSR;"<<std::endl;
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

    template<typename Data>
    void populateRandomMatrix(lasd::Matrix<Data> &mat, lasd::List<Data> &lst) {

        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distRow(0, mat.RowNumber()-1);
        std::uniform_int_distribution<int> distCol(0, mat.ColumnNumber()-1);

        mat(0,0) = lst[0];

        for (int i = 0; i < lst.Size(); i++)
            mat(distRow(generator),distCol(generator)) = lst[i];
        
    }

/* ************************************************************************** */

    //Visualizzazione
    template<typename Data>
    void visualizzaMatrix(lasd::Matrix<Data> &mat) {
        int result = -1;
        while (result < 0 || result > 4) {
            std::cout << "Inserisci il tipo di visita: ";
            std::cout << "0): PreOrder, 1): PostOrder;"<<std::endl;
            std::cin >> result;
        }
        switch (result) {
            case 0:
                mat.MapPreOrder(&stampavalore<Data>, nullptr);
                break;

            case 1:
                mat.MapPostOrder(&stampavalore<Data>, nullptr);
                break;
        }
    }

    //GetCell
    template<typename Data>
    void getCell(lasd::Matrix<Data> &mat) {
        int row;
        int col;
        std::cout << "Inserisci le coordinate della cella da leggere:" << std::endl;
        std::cout << "Righe:";
        std::cin >> row;
        std::cout << std::endl;
        std::cout << "Colonne:";
        std::cin >> col;
        if(mat.ExistsCell(row,col)) {
            std::cout << "L'elemento a riga "+std::to_string(row)+" e colonna "+std::to_string(col)+" è: " << std::endl;
            std::cout << mat(row,col) << std::endl;
        }else
            std::cout << "La cella non esiste." << std::endl;
    }

    //IfExist Cell
    template<typename Data>
    void ifExistsCell(const lasd::Matrix<Data> &mat) {
        int row;
        int col;
        std::cout << "Inserisci le coordinate della cella da controllare:" << std::endl;
        std::cout << "Righe:";
        std::cin >> row;
        std::cout << std::endl;
        std::cout << "Colonne:";
        std::cin >> col;
        if(mat.ExistsCell(row,col))
            std::cout << "La cella a riga "+std::to_string(row)+" e colonna "+std::to_string(col)+" esiste." << std::endl;
        else
            std::cout << "La cella non esiste." << std::endl;
    }

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