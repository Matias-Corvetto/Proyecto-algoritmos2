#define LISTA

//Lista encadenada simple.
template <class T>
class Lista {
private:
    T data;
    Lista* sig;
public:
    Lista() {
        this->data = NULL;
        this->sig = NULL;
    }

    //Agrega nuevo nodo al principio de una lista.
    void add(T elem, Lista *&l) {
        if (this->data == NULL) {
            this->data = elem;
            this->sig = NULL;
        } else{
            Lista* nodo = new Lista();
            nodo->data = elem;
            nodo->sig = l;
            l = nodo;
        }
    }

    T getMayor(T (*comparador)(T, T)) {
        T max = NULL;
        Lista* aux = this;

        while (aux) {
            max = comparador(max, aux->data);
            aux = aux->sig;
        }

        return max;
    }

    T getData() {
        return this->data;
    }

    ~Lista() {
        Lista* aux = this;
        while (aux) {
            Lista* aBorrar = aux;
            aux = aux->sig;
            delete aBorrar;
        }
    }
};