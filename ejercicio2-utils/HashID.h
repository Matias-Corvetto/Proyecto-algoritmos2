#ifndef HASHID_H
#define HASHID_H
#include "Pelicula.cpp"
#include "HashGeneros.cpp"
#include <string>

template<class T>
class HashID {
private:
    Pelicula **data;
    int length;
    HashGeneros CategoryString;

    int hashFunction(int id);

    bool isPrimeNumber(int num);

    int nextPrimeNumber(int num);

public:3
    HashID(int largo, int categorias);

    void addFilm(int id, string genero);

    void addRating(int id, int puntaje);

    int getData(string genero)

    int getLength();

    ~HashID();
};

#endif
