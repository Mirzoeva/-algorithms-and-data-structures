#include <iostream>
#include <vector>

struct Customer {
    int in;
    int out;
    Customer(int in, int out) :
            in(in),
            out(out)
    {}
};

bool operator <(Customer first, Customer second) {
    if (first.out < second.out) {
        return true;
    } else if (first.out == second.out) {
        if (first.in <= second.in) {
            return true;
        }
    }
    return false;
}

template <typename T>
void swap(std::vector<T>& array, int a, int b){
    Customer buf = array[a];
    array[a] = array[b];
    array[b] = buf;
}

template <typename T>
void ShiftDown(std::vector<T>& array, int i, int border){
    int curIndex, Child1, Child2;
    while (i < border){
        curIndex = i;
        Child1 = 2*i + 1;
        Child2 = 2*i + 2;
        if (Child1 < border && array[curIndex] < array[Child1]) {
            curIndex = Child1;
        }
        if (Child2 < border && array[curIndex] < array[Child2]) {
            curIndex = Child2;
        }
        if (curIndex == i) return;
        swap(array, i, curIndex);
        i = curIndex;
    }
}
void HeapSort(std::vector<Customer>& arr) {
    int i = (arr.size() / 2) - 1;
    while (i >= 0) {
        ShiftDown(arr, i, arr.size());
        i--;
    }
    int last = arr.size() - 1;
    while (last > 0){
        swap(arr, 0, last);
        ShiftDown(arr, 0, last);
        last--;
    }
}

template <typename T>
int Calc(int n, std::vector<T> array){
    int result = 0;
    int inBorder = -1, outBorder = -1;
    for (int i = 0; i < n; i++) {
        Customer buf = array[i];
        if (buf.in > outBorder) {
            result = result + 2;
            inBorder = buf.out - 1;
            outBorder = buf.out;
        } else if (buf.in == outBorder) {
            result++;
            inBorder = outBorder;
            outBorder = buf.out;
        } else if (buf.in > inBorder && buf.out > outBorder) {
            result++;
            inBorder = outBorder;
            outBorder = buf.out;
        } else if (buf.in > inBorder && buf.in < outBorder) {
            result++;
            inBorder = buf.out;
        }
    }
    return result;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Customer> array;
    for (int i = 0; i < n; i++) {
        int in = 0, out = 0;
        std::cin >> in >> out;
        Customer curCustomer(in, out);
        array.push_back(curCustomer);
    }
    HeapSort(array);
    std::cout <<  Calc(n, array);
    return 0;
}
