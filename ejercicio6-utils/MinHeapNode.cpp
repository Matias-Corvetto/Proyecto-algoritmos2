#include <iostream>

template<class T>
class HeapNode {
public:
    T data;
    int pos;

    HeapNode(T data, int pos) {
        this->data = data;
        this->pos = pos;
    }
};