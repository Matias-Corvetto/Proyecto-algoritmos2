#ifndef LISTA
#define LISTA

template<class T>
class NodoLista {
    public:
        T dato;
        NodoLista<T>* sig;
        NodoLista<T>* ant;

        NodoLista(T dato);

        NodoLista(NodoLista<T>* ant, T dato, NodoLista<T>* sig);
};

//Lista encadenada simple.
template <class T>
class Lista {
private:
    NodoLista<T>* ppio;
    NodoLista<T>* fin;
    int largo;
public:
    Lista();

    //Agrega nuevo nodo al principio de la lista.
    void addPpio(T elem);

    //Agrega nuevo nodo al final de la lista.
    void addFin(T elem);

    //Retorna true si existe un dato igual a elem en la lista.
    bool existe(T elem);

    //Devuelve el dato al inicio de la lista.
    T getPpio();

    //Devuelve el dato al final de la lista.
    T getFin();

    //Devuelve el dato en la posición i.
    T getPos(int i);

    //Devuelve el largo de la lista.
    int getLargo();

    ~Lista();
};

#endif