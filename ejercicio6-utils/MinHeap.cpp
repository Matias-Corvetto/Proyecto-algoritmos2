#include <iostream>
#include "MinHeapNode.cpp"

using namespace std;

template <class T>
class MinHeap
{
private:
	HeapNode<T> **heapArray;
	int nextPos;
	int maxElements;

	void floatUp(int pos)
	{
		int parentPos = pos / 2;
		while (pos > 1 && this->heapArray[pos]->data < this->heapArray[parentPos]->data)
		{
			swap(this->heapArray[pos], this->heapArray[parentPos]);
			pos = parentPos;
			parentPos = pos / 2;
		}
	}

	void sinkDown(int pos)
	{
		int leftChild = 2 * pos;
		int rightChild = 2 * pos + 1;
		int root = pos;

		if (leftChild < this->nextPos && this->heapArray[leftChild]->data < this->heapArray[root]->data)
		{
			root = leftChild;
		}

		if (rightChild < this->nextPos && this->heapArray[rightChild]->data < this->heapArray[root]->data)
		{
			root = rightChild;
		}

		if (root != pos)
		{
			swap(this->heapArray[pos], this->heapArray[root]);
			sinkDown(root);
		}
	}

public:
	MinHeap(int maxElements)
	{
		this->maxElements = maxElements;
		this->nextPos = 1;
		this->heapArray = new HeapNode<T> *[this->maxElements + 1];

		for (int i = 0; i < this->maxElements + 1; i++)
		{
			this->heapArray[i] = NULL;
		}
	}

	~MinHeap()
	{
		for (int i = 1; i < nextPos; ++i)
		{
			delete heapArray[i];
		}
		delete[] this->heapArray;
	}

	void enqueue(T dato, int pos)
	{
		HeapNode<T> *node = new HeapNode<T>(dato, pos);
		this->heapArray[this->nextPos] = node;
		floatUp(this->nextPos);
		this->nextPos++;
	}

	void dequeue()
	{
		if (this->nextPos != 1 && this->nextPos == 2)
		{
			delete this->heapArray[1];
			this->heapArray[1] = 0;
			this->nextPos--;
		}
		else if (this->nextPos != 1)
		{
			delete this->heapArray[1];
			this->heapArray[1] = this->heapArray[--this->nextPos];
			sinkDown(1);
		}
	}

	T getMin()
	{
		return this->heapArray[1]->data;
	}

	T getMinPos()
	{
		return this->heapArray[1]->pos;
	}

	bool isEmpty()
	{
		return this->nextPos == 1;
	}
};