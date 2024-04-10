using namespace std;

template<class T>
class ClosedHash {
private:
    T **data;
    int **occurrences;
    int length;

    int (*hashFunction)(T);

    bool isPrimeNumber(int num) {
        if (num <= 1) {
            return false;
        } else {
            for (int i = 2; i <= num / 2; i++) {
                if (num % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }

    int nextPrimeNumber(int num) {
        while (!isPrimeNumber(++num));
        return num;
    }

public:
    ClosedHash(int large, int (*hashFunction)(T)) {
        this->length = nextPrimeNumber(large);
        this->data = new T *[this->length];
        this->occurrences = new int *[this->length];
        for (int i = 0; i < this->length; i++) {
            this->data[i] = NULL;
            this->occurrences[i] = NULL;
        }
        this->hashFunction = hashFunction;
    }

    void add(T data) {
        int bucket = this->hashFunction(data) % this->length;
        while (this->data[bucket]) {
            if (*this->data[bucket] == data) {
                (*this->occurrences[bucket])++;
                return;
            } else {
                bucket = (bucket + 1) % this->length;
            }
        }
        this->data[bucket] = new T(data);
        this->occurrences[bucket] = new int(1);
    }

    T **getData() {
        return this->data;
    }

    int **getOccurrences() {
        return this->occurrences;
    }

    int getLength() {
        return this->length;
    }

    ~ClosedHash() {
        for (int i = 0; i < this->length; i++){
            if(this->data[i]){
                delete this->data[i];
                delete this->occurrences[i];
                this->data[i] = NULL;
                this->occurrences[i] = NULL;
            }
        }
        delete[] this->data;
        delete[] this->occurrences;
    }
};