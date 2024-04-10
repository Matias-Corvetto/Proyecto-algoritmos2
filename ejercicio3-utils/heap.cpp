#include <iostream>
#include "heapNode.cpp"

using namespace std;

template<class T>
class Heap {
private:
    HeapNode<T> **heapArray;
    int nextPos;
    int maxElements;

    void floatUp(int pos) {
        int parentPos = pos / 2;
        while (pos > 1 && this->heapArray[pos]->compare(this->heapArray[parentPos]) == 1) {
            swap(this->heapArray[pos], this->heapArray[parentPos]);
            pos = parentPos;
            parentPos = pos / 2;
        }
    }

    void sinkDown(int pos) {
        int leftChild = 2 * pos;
        int rightChild = 2 * pos + 1;
        int root = pos;

        if (leftChild < this->nextPos && this->heapArray[leftChild]->compare(this->heapArray[root]) == 1) {
            root = leftChild;
        }

        if (rightChild < this->nextPos && this->heapArray[rightChild]->compare(this->heapArray[root]) == 1) {
            root = rightChild;
        }

        if (root != pos) {
            swap(this->heapArray[pos], this->heapArray[root]);
            sinkDown(root);
        }
    }

public:
    Heap(int maxElements) {
        this->maxElements = maxElements;
        this->nextPos = 1;
        this->heapArray = new HeapNode<T> *[this->maxElements + 1];

        for (int i = 0; i < this->maxElements + 1; i++) {
            this->heapArray[i] = NULL;
        }
    }

    ~Heap() {
        int i = 1;
        while (i <= this->maxElements) {
            if (this->heapArray[i] != NULL) {
                delete this->heapArray[i];
                this->heapArray[i] = NULL;
            }
            i++;
        }
        delete[] this->heapArray;
    }

    void enqueue(HeapNode<T> *node) {
        this->heapArray[this->nextPos] = node;
        floatUp(this->nextPos);
        this->nextPos++;
    }

    void dequeue() {
        if (this->nextPos != 1 && this->nextPos == 2) {
            delete this->heapArray[1];
            this->heapArray[1] = NULL;
            this->nextPos--;
        } else if (this->nextPos != 1) {
            delete this->heapArray[1];
            this->heapArray[1] = this->heapArray[--this->nextPos];
            sinkDown(1);
        }
    }

    T getMax() {
        return this->heapArray[1]->data;
    }

    bool isEmpty() {
        return this->nextPos == 1;
    }
};