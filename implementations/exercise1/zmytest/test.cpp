#include "test.hpp"

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
                int size = selectSize();

                if (selectedStruct == 0) {
                    if (selectedType == 0) {
                        lasd::Vector<int> v(size);
                        populationRandomVector(v);
                        vectorMenu(v);

                    } else if (selectedType == 1) {
                        lasd::Vector<float> v(size);
                        populationRandomVector(v);
                        vectorMenu(v);

                    } else if (selectedType == 2) {
                        lasd::Vector<std::string> v(size);
                        populationRandomVector(v);
                        vectorMenu(v);
                        
                    }

                } else if (selectedStruct == 1) {
                    if (selectedType == 0) {
                        lasd::List<int> list;
                        populationRandomList(list, size);
                        listMenu(list);
                        
                    } else if (selectedType == 1) {
                        lasd::List<float> list;
                        populationRandomList(list, size);
                        listMenu(list);
                        
                    } else if (selectedType == 2) {
                        lasd::List<std::string> list;
                        populationRandomList(list, size);
                        listMenu(list);
                        
                    }
                }

                exit = true;
            } while (!exit);

    }

 /* ************************************************************************** */

    //Vector menù
    template<typename Data>
    void vectorMenu(lasd::Vector<Data> &container) {
        int choose = 0;
        do {
            std::cout << "---------------Menù Vector---------------" << std::endl;
            std::cout << "1) Visualizza vettore." << std::endl;
            std::cout << "2) Popola il vettore random." << std::endl;
            std::cout << "3) Mostra Front, Back o indice specifico." << std::endl;
            std::cout << "4) Controllo di esistenza." << std::endl;
            std::cout << "5) Fold calculation (punto 6)." << std::endl;
            std::cout << "6) Applica funzioni (punto 7)." << std::endl;
            std::cout << "7) Ridimensiona vettore." << std::endl;
            std::cout << "0) Indietro." << std::endl;
            std::cout << "------------Scelga un'opzione------------" << std::endl;
            std::cin >> choose;

            switch (choose) {
                case 1:
                    std::cout << "---Visualizzazione elementi---" << std::endl;
                    container.MapPreOrder(&stampavalore<Data>, nullptr);
                    std::cout << std::endl;
                    break;

                case 2:
                    populationRandomVector(container);
                    break;

                case 3:
                    visualizzaFrontBackIndex(container);
                    break;

                case 4:
                    ifExists(container);
                    break;

                case 5:
                    if (container.Empty()) {
                        std::cout << "Il container è vuoto.";
                    } else {
                        int n;
                        std::cout << "Inserisci il valore di n per la funzione (dipende dal tipo di vettore creato): ";
                        std::cin >> n;

                        //Varie implementazioni parametriche (dava problemi).

                        //Data result;
                        //container.FoldPreOrder(&foldFunction<Data>, &n, &result);
                        //std::cout << "Risultato: " << result << std::endl;

                        if(isInt(container[0])){
                            int result=0;
                            container.FoldPreOrder(&foldFunction<Data>, &n, &result);
                            std::cout << "Risultato: " << result << std::endl;

                        }else if(isFloat(container[0])){
                            float result=1;
                            container.FoldPreOrder(&foldFunction<Data>, &n, &result);
                            std::cout << "Risultato: " << result << std::endl;

                        }else if(isString(container[0])){
                            std::string result="";
                            container.FoldPreOrder(&foldFunction<Data>, &n, &result);
                            std::cout << "Risultato: " << result << std::endl;
                        }
                    }
                    break;

                case 6:
                    std::cout << "---Verranno applicate modifiche a tutti gli elementi (dipende dal tipo di vettore)---" << std::endl;
                    container.MapPostOrder(&applicationFunction<Data>, nullptr);
                    std::cout << "---Modifiche apportate (visualizzare la struttura per vederle)---" << std::endl;
                    break;

                case 7:
                    int n;
                    do {
                        std::cout << "Inserisci la nuova grandezza del vettore: ";
                        std::cin >> n;
                    } while (n <= 0);
                    container.Resize(n);
                    std::cout << "Hai ridimensionato il vettore. Size: " << n << std::endl;
                    break;
            }

        } while (choose != 0);

        container.Clear();

    }

    //List menù
    template<typename Data>
    void listMenu(lasd::List<Data> &container) {
        int choose = -1;
            do {
                std::cout << "----------------Menù List----------------" << std::endl;
                std::cout << "1) Visualizza lista." << std::endl;
                std::cout << "2) Popola il vettore random." << std::endl;
                std::cout << "3) Mostra Front, Back o indice specifico." << std::endl;
                std::cout << "4) Controllo di esistenza." << std::endl;
                std::cout << "5) Fold calculation (punto 6)." << std::endl;
                std::cout << "6) Applica funzioni (punto 7)." << std::endl;
                std::cout << "7) Inserisci in testa." << std::endl;
                std::cout << "8) Inserisci in coda." << std::endl;
                std::cout << "9) Rimuovi e leggi." << std::endl;
                std::cout << "0) Indietro." << std::endl;
                std::cout << "------------Scelga un'opzione------------" << std::endl;
                std::cin >> choose;

                switch (choose) {
                    case 1:
                        std::cout << "---Visualizzazione elementi---" << std::endl;
                        container.MapPreOrder(&stampavalore<Data>, nullptr);
                        std::cout << std::endl;
                        break;

                    case 2:
                        int newRand;
                        std::cout << "Quanti nodi random vuoi generare?" << std::endl;
                        std::cin >> newRand;

                        populationRandomList(container, newRand);
                        break;

                    case 3:
                        visualizzaFrontBackIndex(container);
                        break;

                    case 4:
                        ifExists(container);
                        break;

                    case 5:
                        if (container.Empty()) {
                            std::cout << "Il container è vuoto.";
                        } else {
                            int n;
                            std::cout << "Inserisci il valore di n per la funzione (dipende dal tipo di lista creata): ";
                            std::cin >> n;

                            //Varie implementazioni parametriche (dava problemi).

                            //Data result;
                            //container.FoldPreOrder(&foldFunction<Data>, &n, &result);
                            //std::cout << "Risultato: " << result << std::endl;

                            if(isInt(container.Front())){
                                int result=0;
                                container.FoldPreOrder(&foldFunction<Data>, &n, &result);
                                std::cout << "Risultato: " << result << std::endl;

                            }else if(isFloat(container.Front())){
                                float result=1;
                                container.FoldPreOrder(&foldFunction<Data>, &n, &result);
                                std::cout << "Risultato: " << result << std::endl;

                            }else if(isString(container.Front())){
                                std::string result="";
                                container.FoldPreOrder(&foldFunction<Data>, &n, &result);
                                std::cout << "Risultato: " << result << std::endl;

                            }
                        }
                        break;

                    case 6:
                        std::cout << "---Verranno applicate modifiche a tutti gli elementi (dipende dal tipo di lista)---" << std::endl;
                        container.MapPostOrder(&applicationFunction<Data>, nullptr);
                        std::cout << "---Modifiche apportate (visualizzare la struttura per vederle)---" << std::endl;
                        break;

                    case 7: {
                        Data value;

                        std::cout << "Inserisci elemento da inserire:" << std::endl;
                        std::cin >> value;
                        
                        container.InsertAtFront(value);
                        std::cout << "Elemento inserito in testa." << std::endl;
                        break;
                    }

                    case 8: {
                        Data value;

                        std::cout << "Inserisci elemento da inserire:" << std::endl;
                        std::cin >> value;
                        
                        container.InsertAtBack(value);
                        std::cout << "Elemento inserito in coda." << std::endl;
                        break;
                    }

                    case 9: {
                        if (container.Empty()) {
                            std::cout << "Il container è vuoto." << std::endl;
                        } else {
                            const Data &data = container.FrontNRemove();
                            std::cout << "Dato rimosso: " << data << std::endl << std::endl;
                        }
                        break;
                    }

                }

            } while (choose != 0);

            container.Clear();
    }

 /* ************************************************************************** */

    //Selector

    int selectStruct() {
        int result = -1;
        while (result < 0 || result > 1) {
            std::cout << "Inserisci la struttura (0: vector, 1: list): ";
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
            std::cout << "Inserisci la grandezza iniziale del container. Min: 1, Max: 100: ";
            std::cin >> result;
        }
        return result;
    }

 /* ************************************************************************** */

    //Population Vector
    template<typename Data>
    void populationRandomVector(lasd::Vector<Data> &data) {}

    template<>
    void populationRandomVector(lasd::Vector<int> &data) {

        std::cout << "--- Inizio popolazione random INT---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distx(0, 100);

        for (uint i = 0; i < data.Size(); ++i) {
            data[i] = distx(generator);
        }
        std::cout << "---Popolazione random INT completata---" << std::endl;
    }

    template<>
    void populationRandomVector(lasd::Vector<float> &data) {
        
        std::cout << "---Inizio popolazione random FLOAT---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_real_distribution<double> distx(1.0, 100.0);

        for (uint i = 0; i < data.Size(); ++i) {
            std::cout << std::fixed << std::setprecision(2);
            data[i] = distx(generator);
        }
        std::cout << "---Popolazione random FLOAT completata---" << std::endl;
    }

    template<>
    void populationRandomVector(lasd::Vector<std::string> &data) {

        std::cout << "---Inizio popolazione random STRING---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distx(0, 10);

        for (uint i = 0; i < data.Size(); ++i) {
            data[i] = generateString(distx(generator));
        }
        std::cout << "---Popolazione random STRING completata---" << std::endl;
    }

 /* ************************************************************************** */

    //Population List
    template<typename Data>
    void populationRandomList(lasd::List<Data> &container, int size) {}

    template<>
    void populationRandomList(lasd::List<int> &container, int size) {
        
        std::cout << "--- Inizio popolazione random INT---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distx(0, 100);

        for (uint i = 0; i < size; ++i) {
            container.InsertAtBack(distx(generator));
        }

        std::cout << "---Popolazione random INT completata---" << std::endl;
    }

    template<>
    void populationRandomList(lasd::List<float> &container, int size) {
        
        std::cout << "--- Inizio popolazione random FLOAT---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_real_distribution<double> distx(1.0, 100.0);

        for (uint i = 0; i < size; ++i) {
            std::cout << std::fixed << std::setprecision(2);
            container.InsertAtBack(distx(generator));
        }

        std::cout << "---Popolazione random FLOAT completata---" << std::endl;
    }

    template<>
    void populationRandomList(lasd::List<std::string> &container, int size) {

        std::cout << "--- Inizio popolazione random STRING---" << std::endl;
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<int> distx(0, 10);
        
        for (uint i = 0; i < size; ++i) {
            container.InsertAtBack(generateString(distx(generator)));
        }

        std::cout << "---Popolazione random STRING completata---" << std::endl;
    }

 /* ************************************************************************** */

    //Fron/Back/Index access
    template<typename Data>
    void visualizzaFrontBackIndex(const lasd::LinearContainer<Data> &container) {
        if (container.Empty()) {
            std::cout << "Container vuoto." << std::endl;
            return;
        }

        int type = -1;
        while (type < 0 || type > 2) {
            std::cout << "Visualizza: Front (0), Back(1), indice (2): ";
            std::cin >> type;
        }
            if (type == 0) {
                std::cout << "Elemento Front: " << container.Front() << std::endl;
            } else if (type == 1) {
                std::cout << "Elemento Back: " << container.Back() << std::endl;
            } else if (type == 2) {
                int index = -1;
                while (index < 0 || index >= container.Size()) {
                    std::cout << "Inserisci l'indice: (0 - " << (container.Size() - 1) << "): ";
                    std::cin >> index;
                }
                std::cout << "Valore contenuto (indice: " << index << "): " << container[index] << std::endl;
            }
    }

 /* ************************************************************************** */

    template<typename Data>
    void ifExists(const lasd::TestableContainer<Data> &container) {
        Data value;
        bool resta = false;
        do {
            std::cout << "Inserisci il valore che vuoi controllare: ";
            std::cin >> value;

            std::string text = container.Exists(value) ? ("L'elemento è nel container.") : ("L'elemento non è nel container.");

            std::cout << text << std::endl;

            std::cout << "Vuoi controllare un altro elemento? (y/n): ";

            char res;
            std::cin >> res;

            resta = (res == 'y');
        } while (resta);
    }

 /* ************************************************************************** */

    //Parte 6: utilizzo di fold
    template<typename Data>
    void foldFunction(const Data &, const void *n, void *result) noexcept {
        int value = *((int *) n);
    }

    template<>
    void foldFunction(const int &data, const void *n, void *result) noexcept {
        //int value = *((int *) n);
        if (data < *((int *) n))
            *((int *) result) += data;
    }

    template<>
    void foldFunction(const float &data, const void *n, void *result) noexcept {
        //int value = *((int *) n);
        if (data > *((int *) n))
            *((float *) result) *= data;
    }

    template<>
    void foldFunction(const std::string &data, const void *n, void *result) noexcept {
        //int value = *((int *) n);
        if (data.length() <= *((int *) n))
            ((std::string *) result)->append(data);
    }

    //Parte 7: function application
    template<typename Data>
    void applicationFunction(Data &dato, void*) {}

    template<>
    void applicationFunction(int &dato, void*) {
        dato = dato * 2;
    }

    template<>
    void applicationFunction(float &dato, void*) {
        dato = dato * dato;
    }

    template<>
    void applicationFunction(std::string &dato, void*) {
        auto &str = dato;
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        dato = str;
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
    void stampavalore(Data &dato, void*) {
        std::cout<< dato << " ";
    }

 /* ************************************************************************** */