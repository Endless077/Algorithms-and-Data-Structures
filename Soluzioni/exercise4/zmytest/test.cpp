#include "test.hpp"

#include "../bst/bst.hpp"

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
                int selectedType = selectType();
                int selectedSize = selectSize();

                if (selectedType == 0) {
                    lasd::List<int> lst;
                    populateRandomLinearContainer(lst,selectedSize);
                    lasd::BST<int> bst(lst);
                    bstMenu(bst);
                }else if(selectedType == 1){
                    lasd::List<float> lst;
                    populateRandomLinearContainer(lst,selectedSize);
                    lasd::BST<float> bst(lst);
                    bstMenu(bst);
                }else if(selectedType == 2){
                    lasd::List<std::string> lst;
                    populateRandomLinearContainer(lst,selectedSize);
                    lasd::BST<std::string> bst(lst);
                    bstMenu(bst);
                }
            exit = true;
            }while (!exit);
    }

    //Menù
    template<typename Data>
    void bstMenu(lasd::BST<Data> &bt) {
        int choose = 0;

        do {
                std::cout << "-----------------Menù BST-----------------" << std::endl;
                std::cout << "1) Visualizzazione tramite Map." << std::endl;
                std::cout << "2) Controllo di esistenza." << std::endl;
                std::cout << "3) Calcolo delle funzioni." << std::endl;
                std::cout << "4) Inserimento di un elemento." << std::endl;
                std::cout << "5) Rimozione di un elemento." << std::endl;
                std::cout << "6) Minimo e Massimo." << std::endl;
                std::cout << "7) Predecessor e Successor." << std::endl;
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
                    insertIn(bt);
                    break;
                
                case 5:
                    removeOut(bt);
                   break;
                
                case 6:
                    if (bt.Empty()) {
                        std::cout << "L'albero è vuoto." << std::endl;
                    } else {
                        menuMaxMin(bt);
                    }
                    break;
                
                case 7:
                    if (bt.Empty()) {
                        std::cout << "L'albero è vuoto." << std::endl;
                    } else {
                        menuPreSuc(bt);
                    }
                    break; 

            }

        } while (choose != 0);
    }


 /* ************************************************************************** */

    //Selector

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

    //Visualizza l'albero corrente (MAP)
    template<typename Data>
    void visualizzaBT(lasd::BST<Data> &bt){
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

    //Applica funzione all'albero (FOLD)
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

 /* ************************************************************************** */

    //Insert
    template<typename Data>
    void insertIn(lasd::BST<Data> &bt) {
        Data insertData;
        std::cout << "Inserisci l'elemento che vuoi inserire nell'albero: " << std::endl;
        std::cin >> insertData;

        std::cout << "Se l'elemento è già presente non verrà inserito." << std::endl;
        bt.Insert(insertData);
    }

    //Remove
    template<typename Data>
    void removeOut(lasd::BST<Data> &bt) {
        Data removeData;
        std::cout << "Inserisci l'elemento che vuoi rimuovere dall'albero: " << std::endl;
        std::cin >> removeData;

        std::cout << "Se l'elemento non è presente non verrà fatta alcuna rimozione." << std::endl;
        bt.Remove(removeData);
    }

    //Max/Min
    template<typename Data>
    void menuMaxMin(lasd::BST<Data> &bt) {
        int choose = 0;
        std::cout << "---------------Menù Min/Max---------------" << std::endl;
        std::cout << "1) Lettura Minimo." << std::endl;
        std::cout << "2) Lettura Massimo." << std::endl;
        std::cout << "3) Lettura distruttiva Minimo." << std::endl;
        std::cout << "4) Lettura distruttiva Massimo." << std::endl;
        std::cout << "5) Distruggi Minimo." << std::endl;
        std::cout << "6) Distruggi Massimo." << std::endl;
        std::cout << "------------Scelga un'opzione------------" << std::endl;
        std::cin >> choose;

        switch (choose)
        {
        case 1:
            try
            {
                std::cout << "Il minimo è: " << bt.Min() << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        
        case 2:
            try
            {
                std::cout << "Il massimo è: " << bt.Max() << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        
        case 3:
            try
            {
                std::cout << "Il minimo che è stato eliminato è: " << bt.MinNRemove() << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;

        case 4:
            try
            {
                std::cout << "Il minimo che è stato eliminato è: " << bt.MaxNRemove() << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;

        case 5:
            try
            {
                std::cout << "Eliminazione del minimo." << std::endl;
                bt.RemoveMin();
                std::cout << "Eliminazione completata." << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;

        case 6:
            try
            {
                std::cout << "Eliminazione del massimo." << std::endl;
                bt.RemoveMax();
                std::cout << "Eliminazione completata." << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;

        }
    }

    //Predecessor/Successor
    template<typename Data>
    void menuPreSuc(lasd::BST<Data> &bt) {
        int choose = 0;
        std::cout << "--------Menù Predecessor/Successor--------" << std::endl;
        std::cout << "1) Lettura Predecessor." << std::endl;
        std::cout << "2) Lettura Successor." << std::endl;
        std::cout << "3) Lettura distruttiva Predecessor." << std::endl;
        std::cout << "4) Lettura distruttiva Successor." << std::endl;
        std::cout << "5) Distruggi Predecessor." << std::endl;
        std::cout << "6) Distruggi Successor." << std::endl;
        std::cout << "------------Scelga un'opzione------------" << std::endl;
        std::cin >> choose;
        
        Data search;
        std::cout << "Selezionare l'elemento su cui cercare:" << std::endl;
        std::cin >> search;
        
        switch (choose)
        {
        case 1:
            try
            {
                std::cout << "Il predecessor di " << search << " è: " << bt.Predecessor(search) << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        
        case 2:
            try
            {
                std::cout << "Il successor di " << search << " è: " << bt.Successor(search) << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        
        case 3:
            try
            {
                std::cout << "Il predecessor che è stato eliminato di " << search << " è: ";
                std::cout << bt.PredecessorNRemove(search) << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;

        case 4:
            try
            {
                std::cout << "Il predecessor che è stato eliminato di " << search << " è: ";
                std::cout << bt.SuccessorNRemove(search) << std::endl;
            }   
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;

        case 5:
            try
            {
                std::cout << "Eliminazione del predecessore di " << search << std::endl;
                bt.RemovePredecessor(search);
                std::cout << "Eliminazione completata." << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;

        case 6:
            try
            {
                std::cout << "Eliminazione del successore di " << search << std::endl;
                bt.RemoveSuccessor(search);
                std::cout << "Eliminazione completata." << std::endl;
            }
            catch(const std::length_error& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        }
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