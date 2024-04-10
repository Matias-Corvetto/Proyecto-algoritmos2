#define LISTA

template <class T>
class Lista {
private:
    T data;
    Lista* sig;

public:
    Lista();

    void add(T elem, Lista *&l);

    T getMayor(T (*comparador)(T, T));

    T getData();

    ~Lista();
};