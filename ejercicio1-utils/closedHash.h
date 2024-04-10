#ifndef CLOSEDHASH_H
#define CLOSEDHASH_H

template<class T>
class ClosedHash {
private:
    T **data;
    int **occurrences;
    int length;

    int (*hashFunction)(T);

    bool isPrimeNumber(int num);

    int nextPrimeNumber(int num);

public:
    ClosedHash(int length, int (*hashFunction)(T));

    void add(T data);

    T **getData();

    int **getOccurrences();

    int getLength();

    ~ClosedHash();
    };

#endif
