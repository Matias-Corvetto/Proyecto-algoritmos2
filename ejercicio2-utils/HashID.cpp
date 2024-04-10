#include "Pelicula.cpp"
#include "HashGeneros.cpp"
#include <string>

using namespace std;

//Hash organizado por ID's, acelera el proceso de ingresar un nuevo puntaje.
class HashID {
private:
    Pelicula **data;
    int length;
    HashGeneros* generoRanking;

    int hashFunction(int id) {
        return id % this->length;
    }

    bool isPrimeNumber(int num) {
        if (num <= 1) {
            return false;
        } else {
            for (int i = 2; i <= num / 2; i++) {
                if (num % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }

    int nextPrimeNumber(int num) {
        while (!isPrimeNumber(++num));
        return num;
    }

public:
    HashID(int largo, int categorias) {
        this->generoRanking = new HashGeneros(categorias);
        this->length = nextPrimeNumber(largo);
        this->data = new Pelicula *[this->length];
        for (int i = 0; i < this->length; i++) {
            this->data[i] = NULL;
        }
    }

    //Registra un nuevo ID en su bucket, creando su instancia de Pelicula. También se ingresa a HashGeneros.
    void addFilm(int id, string genero) {
        int bucket = this->hashFunction(id) % this->length;
        while (this->data[bucket]) {
            bucket = (bucket + 1) % this->length;
        }
        this->data[bucket] = new Pelicula(id, genero);
        this->generoRanking->clasificarGenero(this->data[bucket]);
    }

    //Actualiza la calificacion de la Pelicula.
    void addRating(int id, int puntaje) {
        int bucket = this->hashFunction(id) % this->length;
        while (this->data[bucket]) {
            if (this->data[bucket]->getId() == id) {
                this->data[bucket]->calificacion(puntaje);
                return;
            } else {
                bucket = (bucket + 1) % this->length;
            }
        }
    }

    int getData(string genero) {
        return this->generoRanking->getDataMax(genero)->getId();
    }

    int getLength() {
        return this->length;
    }

    ~HashID() {
        for (int i = 0; i < this->length; i++){
            if(this->data[i]){
                delete this->data[i];
                this->data[i] = NULL;
            }
        }
        delete this->generoRanking;
        delete[] this->data;
    }
};