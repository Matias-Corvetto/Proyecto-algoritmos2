#include <iostream>
#include "ejercicio3-utils/heap.cpp"

using namespace std;

int main() {
    int patientsAmount;
    cin >> patientsAmount;

    Heap<int> *heap = new Heap<int>(patientsAmount);

    for (int i = 0; i < patientsAmount; i++) {
        int patient;
        cin >> patient;

        int time;
        cin >> time;

        int priority;
        cin >> priority;

        HeapNode<int> *patientNode = new HeapNode<int>(patient, priority, time, i + 1);
        heap->enqueue(patientNode);
    }

    while (!heap->isEmpty()) {
        cout << heap->getMax() << endl;
        heap->dequeue();
    }

    return 0;
}