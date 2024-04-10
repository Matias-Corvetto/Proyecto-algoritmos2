#ifndef PELICULA
#define PELICULA
#include <string>

using namespace std;

//Clase para organizar Peliculas fácilmente.
class Pelicula {
private:
    int id;
    int sumaCal;
    int cant;
    string genero;

public:
    Pelicula(int id, string genero) {
        this->id = id;
        this->cant = 0;
        this->sumaCal = 0;
        this->genero = genero;
    }

    void calificacion(int puntaje) {
        this->cant++;
        this->sumaCal += puntaje;
    }

    float getPromedio() {
        if (this->cant > 0) {
            float suma = this->sumaCal;
            float cant = this->cant;
            return suma/cant;
        }
        return 0;
    }

    int getId() {
        return this->id;
    }

    string getGenero() {
        return this->genero;
    }
};

#endif