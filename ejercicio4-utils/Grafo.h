#include <iostream>
#include "Lista.cpp"

using namespace std;

template <class T>
class Grafo {
private:
    int cantVertices;
    int tope;
    T** vertices;
    Lista<int>** ListaAdy;

    buscarVertice(T origen, int & posOrigen, T destino, int & posDestino);

    int buscarElemSinIncidenciasOrden(int* cantInicidencias);

public:
    Grafo(int tope);

    void agregarVertice(T vertice);

    void agregarArista(T origen, T destino);

    Lista<T>* ordenTopologico(bool & tieneCiclo);

    ~Grafo();
};
