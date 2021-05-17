#include "test.hpp"

#include "../stack/lst/stacklst.hpp"
#include "../queue/lst/queuelst.hpp"

#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"

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
                        lasd::List<int> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::BinaryTreeVec<int> BTVint(lst);
                        binaryTreeMenu(BTVint);

                    } else if (selectedType == 1) {
                        lasd::List<float> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::BinaryTreeVec<float> BTVfloat(lst);
                        binaryTreeMenu(BTVfloat);

                    } else if (selectedType == 2) {
                        lasd::List<std::string> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::BinaryTreeVec<std::string> BTVstr(lst);
                        binaryTreeMenu(BTVstr);
                        
                    }
                } else if (selectedStruct == 1) {
                    if (selectedType == 0) {
                        lasd::List<int> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::BinaryTreeLnk<int> BTLint(lst);
                        binaryTreeMenu(BTLint);

                    } else if (selectedType == 1) {
                        lasd::List<float> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::BinaryTreeLnk<float> BTLfloat(lst);
                        binaryTreeMenu(BTLfloat);
                        
                    } else if (selectedType == 2) {
                        lasd::List<std::string> lst;
                        populateRandomLinearContainer(lst,selectedSize);
                        lasd::BinaryTreeLnk<std::string> BTLstr(lst);
                        binaryTreeMenu(BTLstr);
                    }
                }
                exit = true;
            } while (!exit);
    }

    //Menù
    template<typename Data>
    void binaryTreeMenu(lasd::BinaryTree<Data> &bt) {
        int choose = 0;
        struct lasd::BinaryTree<Data>::Node* tmp = &bt.Root();

        do {
                std::cout << "---------------Menù BinaryTree---------------" << std::endl;
                std::cout << "1) Visualizzazione tramite Map." << std::endl;
                std::cout << "2) Controllo di esistenza." << std::endl;
                std::cout << "3) Punto 5 dei TEST." << std::endl;
                std::cout << "4) Punto 6 dei TEST." << std::endl;
                std::cout << "------------------Menù Nodo------------------" << std::endl;
                std::cout << "5) Visualizza elemento." << std::endl;
                std::cout << "6) Modifica elemento." << std::endl;
                std::cout << "7) Scendi sul sinistro (se esiste)." << std::endl;
                std::cout << "8) Scendi sul destro (se esiste)." << std::endl;
                std::cout << "--------------------Altro--------------------" << std::endl;
                std::cout << "9)Iterator. " << std::endl;
                std::cout << "10)Clear." << std::endl;
                std::cout << "--------------------Reset--------------------" << std::endl;
                std::cout << "11) Reset puntatore nodo corrente." << std::endl;
                std::cout << "0) Indietro." << std::endl;
                std::cout << "------------Scelga un'opzione------------" << std::endl;
                std::cin >> choose;
                
                switch (choose) {
                case 1:
                    if(!bt.Empty()) {
                        visualizzaBT(bt);
                        std::cout << std::endl;
                    }else
                        std::cout << "L'albero è vuoto" << std::endl;
                    break;

                case 2:
                    ifExists(bt);
                    break;

                case 3:
                    if (bt.Empty()) {
                        std::cout << "L'albero è vuoto." << std::endl;
                    } else {
                        int n;
                        std::cout << "Inserisci il valore di n per la funzione (dipende dal tipo di albero creato): ";
                        std::cin >> n;

                        if(isInt(bt.Root().Element())){
                            int result=1;
                            bt.FoldPreOrder(&foldFunction<Data>, &n, &result);
                            std::cout << "Risultato: " << result << std::endl;

                        }else if(isFloat(bt.Root().Element())){
                            float result=1;
                            bt.FoldPreOrder(&foldFunction<Data>, &n, &result);
                            std::cout << "Risultato: " << result << std::endl;

                        }else if(isString(bt.Root().Element())){
                            std::string result="";
                            bt.FoldPreOrder(&foldFunction<Data>, &n, &result);
                            std::cout << "Risultato: " << result << std::endl;
                        }
                    }
                    break;
                
                case 4:
                    if (bt.Empty()) {
                        std::cout << "L'albero è vuoto." << std::endl;
                    } else {
                        std::cout << "---Verranno applicate modifiche a tutti gli elementi (dipende dal tipo di albero)---" << std::endl;
                        if(isString(bt.Root().Element())){
                            std::cout << "Inserisci la stringa da concatenare: ";
                            std::string input;
                            std::cin >> input;
                            bt.MapPreOrder(&applicationFunction<Data>, &input);
                        }else{
                            bt.MapPreOrder(&applicationFunction<Data>, nullptr);
                        }
                        std::cout << "---Modifiche apportate (visualizzare la struttura per vederle)---" << std::endl;
                    }
                    break;
                
                case 5:
                    if (bt.Empty()) {
                        std::cout << "L'albero è vuoto." << std::endl;
                    } else {
                        std::cout << "L'elemento corrente è: " << tmp->Element() << std::endl;
                    }
                   break;
                
                case 6:
                    if (bt.Empty()) {
                        std::cout << "L'albero è vuoto." << std::endl;
                    } else {
                        Data change;
                        std::cout << "L'elemento corrente è: " << bt.Root().Element() << std::endl;
                        std::cout << "Come vorresti modificarlo?" << std::endl;
                        std::cin >> change;
                        tmp->Element() = change;
                    }
                    break;
                
                case 7:
                    if (bt.Empty()) {
                        std::cout << "L'albero è vuoto." << std::endl;
                    } else {
                        if(tmp->HasLeftChild()){
                            std::cout << "Spostamento sul sinistro." << std::endl;
                            tmp = &tmp->LeftChild();
                        }else
                            std::cout << "Non ha il sinistro." << std::endl;
                    }
                    break; 
                
                case 8:
                    if (bt.Empty()) {
                        std::cout << "L'albero è vuoto." << std::endl;
                    } else {
                        if(tmp->HasRightChild()){
                            std::cout << "Spostamento sul destro." << std::endl;
                            tmp = &tmp->RightChild();
                        }else
                            std::cout << "Non ha il destro." << std::endl;
                    }
                    break; 

                case 9:
                    if (bt.Empty())
                        std::cout << "L'albero è vuoto." << std::endl;
                    else {
                        int result = -1;
                        while (result < 0 || result > 3) {
                            std::cout << "Inserisci l'iterator che vuoi eseguire: " << std::endl;
                            std::cout << "0) PreOrder;" << std::endl;
                            std::cout << "1) InOrder;" << std::endl;
                            std::cout << "2) PostOder;" << std::endl;
                            std::cout << "3) Ampiezza;" << std::endl;
                            std::cin >> result;
                        }

                        if(result==0){
                            lasd::BTPreOrderIterator<Data> iter(bt);
                            usaIterator(iter);
                        }else if(result==1){
                            lasd::BTInOrderIterator<Data> iter(bt);
                            usaIterator(iter);
                        }else if(result==2){
                            lasd::BTPostOrderIterator<Data> iter(bt);
                            usaIterator(iter);
                        }else if(result==3){
                            lasd::BTBreadthIterator<Data> iter(bt);
                            usaIterator(iter);
                        }
                    }
                    break;

                case 10:
                    std::cout << "---Clear dell'albero iniziata---" << std::endl;
                    bt.Clear();
                    tmp = nullptr;
                    std::cout << "---Clear dell'albero terminata---" << std::endl;
                    break;

                case 11:
                    if (bt.Empty())
                        std::cout << "L'albero è vuoto." << std::endl;
                    else {
                        std::cout << "---Reset---" << std::endl;
                        tmp = &bt.Root();
                    }
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
            std::cout << "0): Vector BT, 1): Linked BT;"<<std::endl;
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
        while (result < 1 || result > 100) {
            std::cout << "Inserisci la quantità di dati per popolare la struttura (1-100): ";
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

    //Exist
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

    //Visite
    template<typename Data>
    void visualizzaBT(lasd::BinaryTree<Data> &bt){
        int result = -1;
        while (result < 0 || result > 4) {
            std::cout << "Inserisci il tipo di visita: ";
            std::cout << "0): PreOrder, 1): InOrder, 2): PostOrder, 3): Ampiezza;"<<std::endl;
            std::cin >> result;
        }
        switch (result) {
            case 0:
                bt.MapPreOrder(&stampavalore<Data>, nullptr);
                break;

            case 1:
                bt.MapInOrder(&stampavalore<Data>, nullptr);
                break;

            case 2:
                bt.MapPostOrder(&stampavalore<Data>, nullptr);
                break;

            case 3:
                bt.MapBreadth(&stampavalore<Data>, nullptr);
                break;
        }
    }

    //Iterator
    template<typename Data>
    void usaIterator(lasd::ForwardIterator<Data> &iter) {

        int scelta = -1;

        do{
            std::cout << "Inserisci l'iterator che vuoi eseguire: " << std::endl;
            std::cout << "0) Elimina iteratore;" << std::endl;
            std::cout << "1) Operatore *;" << std::endl;
            std::cout << "2) Operatore ++;" << std::endl;
            std::cout << "3) Controllo Terminazione;" << std::endl;
            std::cin >> scelta;
            
            if(scelta==0){
                std::cout << "Iteratore distrutto." << std::endl;
            }else if(scelta==1){
                std::cout << "Nodo corrente: " << *iter << std::endl;
            }else if(scelta==2){
                std::cout << "Operatore ++ " << std::endl;
                if(iter.Terminated())
                    std::cout << "L'iteratore è terminato." << std::endl;
                else{
                    ++iter;
                    std::cout << "Nuovo Nodo corrente: " << *iter << std::endl;
                }
            }else if(scelta==3){
                std::cout << "Terminato: " << iter.Terminated() << std::endl;
            }

        }while (scelta!=0);
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
        dato = dato * 3;
    }

    template<>
    void applicationFunction(float &dato, void*){
        dato = pow(dato,3);
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