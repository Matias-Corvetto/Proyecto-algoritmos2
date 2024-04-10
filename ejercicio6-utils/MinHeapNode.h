#ifndef HEAPNODE_H
#define HEAPNODE_H

template<class T>
class MinHeapNode {
public:
    T data;
    int pos;

    MinHeapNode(T data, int pos);

		int getPos();

		T getData();
};

#endif
