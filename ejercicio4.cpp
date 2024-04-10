#include <iostream>
#include <string>
#include "ejercicio4-utils/Grafo.cpp"
#include "ejercicio4-utils/Lista.cpp"

using namespace std;

int main() {

    int cantPlatos;
    cin >> cantPlatos;

    int CantDependeciasPlatos;
    cin >> CantDependeciasPlatos;

    Grafo<string>* grafo = new Grafo<string>(cantPlatos);

    for (int i = 0; i < cantPlatos; i++) {
        string plato;
        cin >> plato;
        grafo->agregarVertice(plato);
    }

    for (int i = 0; i < CantDependeciasPlatos; i++) {
        string platoA;
        cin >> platoA;

        string platoB;
        cin >> platoB;

        grafo->agregarArista(platoA, platoB, 0);
    }

    bool esCiclo = false;
    Lista<string>* lista = grafo->ordenTopologico(esCiclo);

    if (esCiclo) {
        cout << "CICLO DETECTADO" << endl;  
    } else {
        int largoLista = lista->getLargo();
        for (int i = 0; i < largoLista; i++) {
            cout << lista->getPos(i) << endl;
        }
    }

    delete lista;
    delete grafo;
}