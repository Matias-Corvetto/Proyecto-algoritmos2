#ifndef HEAPNODE_H
#define HEAPNODE_H

template<class T>
class HeapNode {
public:
    T data;
    int priority;
    int time;
    int arriveOrder;

    HeapNode(T data, int priority, int time, int arriveOrder);

    int compare(HeapNode<T> *node);
};

#endif
