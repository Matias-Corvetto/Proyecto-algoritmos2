#include <iostream>
#include <string>
#include "ejercicio1-utils/closedHash.cpp"

using namespace std;

int stringHash(string str) {
    unsigned int strSum = 0;

    for (char character: str) {
        strSum += character++;
    }
    return strSum;
}

template<class T>
void merge(T **foods, int **occurr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T **leftFoods = new T *[n1];
    T **rightFoods = new T *[n2];
    int **leftOccurr = new int *[n1];
    int **rightOccurr = new int *[n2];

    for (int i = 0; i < n1; i++) {
        leftFoods[i] = foods[left + i];
        leftOccurr[i] = occurr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightFoods[j] = foods[mid + 1 + j];
        rightOccurr[j] = occurr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (!leftOccurr[i] && !rightOccurr[j]) {
            foods[k] = NULL;
            occurr[k] = NULL;
            i++;
            j++;
        } else if (!rightOccurr[j]
                   || (leftOccurr[i] && (*leftOccurr[i] > *rightOccurr[j]))
                   || (leftOccurr[i] && (*leftOccurr[i] == *rightOccurr[j]) && (*leftFoods[i] < *rightFoods[j]))) {
            foods[k] = leftFoods[i];
            occurr[k] = leftOccurr[i];
            i++;
        } else {
            foods[k] = rightFoods[j];
            occurr[k] = rightOccurr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        foods[k] = leftFoods[i];
        occurr[k] = leftOccurr[i];
        i++;
        k++;
    }

    while (j < n2) {
        foods[k] = rightFoods[j];
        occurr[k] = rightOccurr[j];
        j++;
        k++;
    }

    delete[] leftFoods;
    delete[] rightFoods;
    delete[] leftOccurr;
    delete[] rightOccurr;
}

template<class T>
void mergeSort(T **foods, int **occurrences, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(foods, occurrences, left, mid);
        mergeSort(foods, occurrences, mid + 1, right);

        merge(foods, occurrences, left, mid, right);
    }
}

int main() {
    int ordersAmount;
    cin >> ordersAmount;

    ClosedHash<string>* hash = new ClosedHash<string>(ordersAmount, stringHash);

    string order;
    for (int i = 0; i < ordersAmount; i++) {
        cin >> order;
        hash->add(order);
    }

    mergeSort(hash->getData(), hash->getOccurrences(), 0, hash->getLength() - 1);

    for (int i = 0; i < hash->getLength(); i++) {
        if (hash->getData()[i]) {
            cout << *hash->getData()[i] << endl;
        }
    }

    delete hash;

    return 0;
}