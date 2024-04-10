#ifndef HASHGENEROS_H
#define HASHGENEROS_H
#include "Pelicula.cpp"
#include "Lista.cpp"

Pelicula* comparador(Pelicula* a, Pelicula* b);

class HashGeneros {
private:
    Lista<Pelicula*> **valores;
    int length;

    int stringHash(string str);

    bool isPrimeNumber(int num);
    
    int nextPrimeNumber(int num);

public:
    HashGeneros(int large);

    void clasificarGenero(Pelicula* peli);

    Pelicula* getDataMax(string genero);

    int getLength();

    ~HashGeneros();
};

#endif
