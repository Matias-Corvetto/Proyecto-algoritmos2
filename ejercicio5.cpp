#include <iostream>
#include "ejercicio4-utils/Grafo.cpp"

using namespace std;

int main() {
    int planetsAmount;
    cin >> planetsAmount;

    int portalsAmount;
    cin >> portalsAmount;

    Grafo<int>* graph = new Grafo<int>(planetsAmount);
    
    for(int i = 1; i < planetsAmount+1; i++) {
        graph->agregarVertice(i);
    }

    for (int i = 0; i < portalsAmount; i++) {
        int vertex1;
        cin >> vertex1;

        int vertex2;
        cin >> vertex2;

        int cost;
        cin >> cost;

        graph->agregarArista(vertex1, vertex2, cost);
    }

    int from;
    cin >> from;

    int to;
    cin >> to;

    cout << graph->dijkstra(from, to) << endl;

    return 0;
}