#include <iostream>

long long int getByte(long long number, int n) {
    return number >> (8 * n) & 255;
}

void sorting(long long *array, int size, const int n) {
    int counters[256] = {0};
    long long int index = 0;
    for(int i = 0; i < size; i++) {
        index = getByte(array[i], n);
        counters[index]++;
    }
    for(int i = 1; i < 256; i++) {
        counters[i] += counters[i - 1]; // считаем индексы
    }
    auto *buf = new long long[size];
    for(int i = size - 1; i > -1; i--) {
        index = getByte(array[i], n);
        buf[--counters[index]] = array[i]; // заполняем массив
    }
    for(int i = 0; i < size; i++) {
        array[i] = buf[i];
    }
    delete[] buf;
}
void LSDSort(long long *array, int size) {
    int allByte = sizeof(long long);
    for(int byte = 0; byte < allByte; byte++) {
        sorting(array, size, byte);
    }
}
int main() {
    int n = 0;
    std::cin >> n;
    auto *array = new long long[n];
    for(size_t i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    LSDSort(array, n);
    for(size_t i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    delete[] array;
    return 0;
}
