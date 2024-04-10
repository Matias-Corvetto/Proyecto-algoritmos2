#ifndef PELICULA_H
#define PELICULA_H
#include <string>

using namespace std;

class Pelicula {
private:
    int id;
    int sumaCal;
    int cant;
    string genero;

public:
    Pelicula(int id, string genero);

    void calificacion(int puntaje);

    float getPromedio();

    int getId();

    char getGenero();
};

#endif