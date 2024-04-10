#include <iostream>
#include <string>
#include "ejercicio4-utils/Grafo.cpp"

using namespace std;

int main() {

    int numUbicaciones;
    cin >> numUbicaciones;
    int numConexiones;
    cin >> numConexiones;
    Grafo<int>* grafo = new Grafo<int>(numUbicaciones);
    for (int i = 1; i < numUbicaciones+1; i++) {
        grafo->agregarVertice(i);
    }
    for (int i = 0; i < numConexiones; i++) {
        int A;
        cin >> A;
        int B;
        cin >> B;
        int C;
        cin >> C;
        grafo->agregarAristaNoDirigido(A, B, C);
    }
    int* ACM = grafo->prim();
    int suma = 0;
    for (int i = 0; i < numUbicaciones; i++) {
        suma += ACM[i];
    }
    cout << suma << endl;

		delete grafo;
		return 0;
}   