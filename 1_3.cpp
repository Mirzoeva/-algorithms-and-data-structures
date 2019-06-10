#include <iostream>
#include <typeinfo>
#include <vector>
#include <assert.h>

/* Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. 
Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. 
Время работы O(n + m).
 n, m ≤ 100000.
*/

int look(int* aArray, int* bArray, int sizeA, int sizeB, int sum){
    int count = 0;
    int index_a = 1;
    int index_b = 1;
    for (int j = sizeB-1, i = 0; j >= 0 && i < sizeA; j -= index_b , i += index_a) {
            if (bArray[j] + aArray[i] == sum) {
                count++;
                index_a = 1;
                index_b = 1;
            }
            if (bArray[j] + aArray[i] < sum) {
                index_b = 0;
            }
            if (bArray[j] + aArray[i] > sum) {
                index_a = 0;
                index_b = 1;
            }
    }
    return count;

}

int main() {
    unsigned int sizeA, sizeB;
    signed int sum;
    std::cin >> sizeA;
    if (sizeA < 0){
        return 0;
    }
    int* aArray = (int*) malloc(sizeA * sizeof(int));
    for (int i = 0; i < sizeA; i++){
        std::cin >> aArray[i];
    }
    std::cin >> sizeB;
    if (sizeB < 0){
        free(aArray);
        return 0;
    }
    int* bArray = (int*) malloc(sizeB * sizeof(int));
    for (int i = 0; i < sizeB; i++){
        std::cin >> bArray[i];
    }
    std::cin >> sum;
    if (typeid(sum) != typeid(int)){
        free(aArray);
        free(bArray);
        return 0;
    }
    int k = 0;
    int count = look(aArray, bArray, sizeA, sizeB, sum);
    free(aArray);
    free(bArray);
    std::cout << count << std::endl;
    return 0;
}


