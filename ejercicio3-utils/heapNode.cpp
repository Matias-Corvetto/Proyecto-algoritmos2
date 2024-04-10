#include <iostream>

template<class T>
class HeapNode {
public:
    T data;
    int priority;
    int time;
    int arriveOrder;

    HeapNode(T data, int priority, int time, int arriveOrder) {
        this->data = data;
        this->priority = priority;
        this->time = time;
        this->arriveOrder = arriveOrder;
    }

    int compare(HeapNode<T> *node) {
        if (this->priority > node->priority) {
            return 1;
        } else if (this->priority < node->priority) {
            return -1;
        } else {
            if (this->time < node->time) {
                return 1;
            } else if (this->time > node->time) {
                return -1;
            } else {
                if (this->arriveOrder < node->arriveOrder) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }
};