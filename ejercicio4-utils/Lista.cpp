#ifndef LISTA
#define LISTA

template <class T>
class NodoLista {
public:
    T dato;
    NodoLista<T> *sig;
    NodoLista<T> *ant;

    NodoLista(T dato) {
        this->dato = dato;
        this->sig = NULL;
        this->ant = NULL;
	}

    NodoLista(NodoLista<T> *ant, T dato, NodoLista<T> *sig) {
        this->dato = dato;
        this->sig = sig;
        this->ant = ant;
    }
};

// Lista encadenada simple.
template <class T>
class Lista {
private:
    NodoLista<T> *ppio;
    NodoLista<T> *fin;
    int largo;

public:
    Lista() {
        this->ppio = NULL;
        this->fin = NULL;
        this->largo = 0;
    }

    // Agrega nuevo nodo al principio de la lista.
    void addPpio(T elem) {
        this->ppio = new NodoLista<T>(NULL, elem, this->ppio);
        if (!this->fin) {
            this->fin = this->ppio;
        } else {
            this->ppio->sig->ant = this->ppio;
        }
        this->largo++;
    }

    // Agrega nuevo nodo al final de la lista.
    void addFin(T elem) {
        this->fin = new NodoLista<T>(this->fin, elem, nullptr);
        if (!this->ppio) {
            this->ppio = this->fin;
        } else {
            this->fin->ant->sig = this->fin;
        }
        this->largo++;
    }

    bool existe(T elem) {
        bool ret = false;
        NodoLista<T> *aux = this->ppio;
        while (aux != nullptr && !ret) {
            ret = aux->dato == elem;
            aux = aux->sig;
        }

        return ret;
    }

    // Devuelve el dato al inicio de la lista.
    T getPpio() {
        return this->ppio->dato;
    }

    NodoLista<T>* getNodoPpio() {
        return this->ppio;
    }

    // Devuelve el dato al final de la lista.
    T getFin() {
        return this->fin->dato;
    }

    T getPos(int i) {
        NodoLista<T> *aux = this->ppio;
        while (i-- > 0 && aux != NULL) {
            aux = aux->sig;
        }
        return aux->dato;
    }

    int getLargo() {
        return this->largo;
    }

    bool esVacia() {
        return this->largo == 0;
    }

    void borrarPpio() {
        if (this->ppio) {
            NodoLista<T> *aux = this->ppio;
            this->ppio = this->ppio->sig;
            if (this->ppio) {
                this->ppio->ant = NULL;
            } else {
				this->fin = NULL;
			}
            delete aux;
            this->largo--;
        }
    }

	Lista<T>* clonar() {
		Lista<T>* ret = new Lista<T>();
		NodoLista<T>* aux = this->ppio;
		while (aux != NULL) {
			ret->addFin(aux->dato);
			aux = aux->sig;
		}
		return ret;
	}

    void borrarFin() {
        if (this->fin) {
            NodoLista<T> *aux = this->fin;
            this->fin = this->fin->ant;
            if (this->fin) {
                this->fin->sig = NULL;
            } else {
                this->ppio = NULL;
            }
            delete aux;
            this->largo--;
        }
    }

	void eliminar(T elem) {
		NodoLista<T> *aux = this->ppio;
		while (aux != NULL && aux->dato != elem) {
			aux = aux->sig;
		}
	}

    ~Lista() {
        NodoLista<T> *aux = this->ppio;
        while (aux) {
            NodoLista<T> *aBorrar = aux;
            aux = aux->sig;
            delete aBorrar;
            aBorrar = NULL;
        }
    }
};

#endif