#ifndef HEAP_H
#define HEAP_H

#include "heapNode.cpp"

template<class T>
class Heap {
private:
    HeapNode<T> **heapArray;
    int nextPos;
    int maxElements;

    void floatUp(int pos);

    void sinkDown(int pos);

public:
    Heap(int maxElements);

    ~Heap();

    void enqueue(HeapNode<T> *node);

    void dequeue();

    T getMax();

    bool isEmpty();
};

#endif
