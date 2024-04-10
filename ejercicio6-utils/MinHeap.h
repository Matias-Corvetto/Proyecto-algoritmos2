#ifndef HEAP_H
#define HEAP_H


template<class T>
class MinHeap {
private:
    T **heapArray;
    int nextPos;
    int maxElements;

    void floatUp(int pos);

    void sinkDown(int pos);

public:
    MinHeap(int maxElements);

    ~MinHeap();

    void enqueue(int pos, T dato);

    void dequeue();

    T getMin();

    bool isEmpty();
};

#endif
