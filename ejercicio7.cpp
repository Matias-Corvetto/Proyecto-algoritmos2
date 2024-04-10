#include <iostream>

int countDigits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

void merge(int* digits, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* leftDigits = new int[n1];
    int* rightDigits = new int[n2];

    for (int i = 0; i < n1; i++) {
        leftDigits[i] = digits[left + i];
    }

    for (int j = 0; j < n2; j++) {
        rightDigits[j] = digits[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftDigits[i] < rightDigits[j]) {
            digits[k] = leftDigits[i];
            i++;
        } else {
            digits[k] = rightDigits[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        digits[k] = leftDigits[i];
        i++;
        k++;
    }

    while (j < n2) {
        digits[k] = rightDigits[j];
        j++;
        k++;
    }

    delete[] leftDigits;
    delete[] rightDigits;
}

void mergeSort(int* digits, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(digits, left, mid);
        mergeSort(digits, mid + 1, right);

        merge(digits, left, mid, right);
    }
}

int main() {
    int n;
    std::cin >> n;

    int amountDigits = countDigits(n);
    
    int* digits = new int[amountDigits];
    
    for (int i = amountDigits - 1; i >= 0; i--) {
        digits[i] = n % 10;
        n /= 10;
    }
    
    mergeSort(digits, 0, amountDigits - 1);
    
    int n1 = 0, n2 = 0;
    for (int i = 0; i < amountDigits; i++) {
        if (i % 2 == 0) {
            n1 = n1 * 10 + digits[i];
        } else {
            n2 = n2 * 10 + digits[i];
        }
    }
    
    int sum = n1 + n2;

    std::cout << sum << std::endl;

    return 0;
}
