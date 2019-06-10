#include <iostream>
#include <vector>

template<class T>
void median(std::vector<T> &array, int beginAr, int endAr) {
    int middle = (beginAr + endAr)/ 2;
    if (array[beginAr] < array[middle])
        std::swap (array[beginAr], array[middle]);
    if (array[middle] > array[endAr])
        std::swap (array[middle], array[endAr]);
    if (array[beginAr] > array[endAr])
        std::swap (array[beginAr], array[endAr]);
}
int partition (std::vector <int> &array, int begin, int endA) {
    median(array, begin, endA);
    int i = endA, j = endA;
    while (j > begin) {
        if (array[j] > array[begin] && j > begin) {
            std::swap(array[j], array[i]);
            i--;
        }
        j--;
    }
    std::swap (array[begin], array[i]);
    return i;
}

template<class T>
int kStat (std::vector<T>& a, int left, int right, int k) {
    int l = left, r = right, index = -1;
    while (index != k){
        index = partition (a, l, r);
        if (index < k)
            l = index + 1;
        else
            r = index - 1;
    }
    return a[k];
}
int main () {
    int n = 0;
    std::cin >> n;
    if (n <= 0)
        return 0;
    int k = 0;
    std::cin >> k;
    if (k < 0)
        return 0;
    std::vector<int> array(n, 0);
    int val = 0;
    for (int i = 0; i < n ; i++) {
        std::cin >> val;
        array[i] = val;
    }
    std::cout << kStat(array, 0, n - 1, k);
}
