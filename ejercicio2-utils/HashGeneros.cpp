#include "Lista.cpp"
#include "Pelicula.cpp"

using namespace std;

//Funcion comparadora de peliculas en HashGeneros
Pelicula* comparador(Pelicula* a, Pelicula* b) {
    if (a == NULL) {
        return b;
    } else if (b == NULL) {
        return a;
    } else {
        if (a->getPromedio() > b->getPromedio()) {
            return a;
        } else if (a->getPromedio() < b->getPromedio()) {
            return b;
        } else {
            if (a->getId() < b->getId()){
                return a;
            } else {
                return b;
            }
        }
    }
}

//Hash organizado por Generos, acelera el proceso de buscar el mayor promedio.
class HashGeneros {
private:
    Lista<Pelicula*> **data;
    int length;

    int stringHash(string str) {
        unsigned int strSum = 0;

        for (char character: str) {
            strSum += character++;
        }
        return strSum;
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
    HashGeneros(int large) {
        this->length = nextPrimeNumber(large);
        this->data = new Lista<Pelicula*>*[this->length];
        for (int i = 0; i < this->length; i++) {
            this->data[i] = NULL;
        }
    }

    //Clasifica (agrega) una Pelicula en el bucket de su Genero correspondiente.
    void clasificarGenero(Pelicula* peli) {
        int bucket = stringHash(peli->getGenero()) % this->length;
        while (this->data[bucket]) {
            if (this->data[bucket]->getData()->getGenero() == peli->getGenero()) {
                this->data[bucket]->add(peli, this->data[bucket]);
                return;
            } else {
                bucket = (bucket + 1) % this->length;
            }
        }

        this->data[bucket] = new Lista<Pelicula*>();
        this->data[bucket]->add(peli, this->data[bucket]);
    }

    //Devuelve Pelicula con mayor clasificación.
    Pelicula* getDataMax(string genero) {
        int bucket = stringHash(genero) % this->length;
        while (this->data[bucket]) {
            if (this->data[bucket]->getData()->getGenero() == genero) {
                Pelicula* max = this->data[bucket]->getMayor(comparador);
                return max;
            } else {
                bucket = (bucket + 1) % this->length;
            }
        }
    }

    int getLength() {
        return this->length;
    }

    ~HashGeneros() {
        for (int i = 0; i < this->length; i++){
            if(this->data[i]){
                delete this->data[i];
                this->data[i] = NULL;
            }
        }
        delete[] this->data;
    }
};