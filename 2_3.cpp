#include <iostream>
#include <typeinfo>
#include <vector>
#include <assert.h>
/* Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. 
A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение. 
Требуемое время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.. 
В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
 n, k ≤ 10000.
*/
std::vector<int> look(int* aArray, int* bArray, int sizeA, int sizeB, int* count){
    std:: vector<int> result(0);
    int index_b = 1, index_a = 1;
    for (int j = 0, i = 0; j < sizeB && i < sizeA; j+= index_b, i+= index_a) {
            if (aArray[i] == bArray[j]) {
                (*count)++;
                result.push_back(aArray[i]);
                index_a = 1;
                index_b = 1;
            }
            if (aArray[i] > bArray[j]) {
                index_a = 0;
                index_b = 1;
            }
            if (aArray[i] < bArray[j]) {
                index_b = 0;
                index_a = 1;
            }
    }
    return result;
}

int main() {
    unsigned int sizeA, sizeB;
    std::cin >> sizeA;
    if (sizeA < 0){
        return 0;
    }
    std::cin >> sizeB;
    if (sizeB < 0){
        return 0;
    }
    int* aArray = (int*) malloc(sizeA * sizeof(int));
    for (int i = 0; i < sizeA; i++){
        std::cin >> aArray[i];
    }
    int* bArray = (int*) malloc(sizeB * sizeof(int));
    for (int i = 0; i < sizeB; i++){
        std::cin >> bArray[i];
    }
    int count = 0;
    std::vector<int> result = look(aArray, bArray, sizeA, sizeB, &count);
    for (int i = 0; i < result.size(); i++){
        std::cout << result[i] << " ";
    }
    free(aArray);
    free(bArray);
    result.clear();
    return 0;
}



