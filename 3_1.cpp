#include <iostream>

/* Реализовать очередь с динамическим зацикленным буфером. */
using namespace std;
template <class T>
class Queue {
private:
    T *Data;
    size_t size;
    size_t head;
    size_t tail;
    const int increase = 2;
    void newBigData();
public:
    Queue();
    ~Queue();
    T Dequeue();
    void Enqueue(T data);
    bool isEmpty() const;
};

template <class T>
void Queue<T>::newBigData() {
    size_t newSize = size * increase;
    T *newData = new T[newSize];
    int newTail = 0;
    for(int i = head; i < size && i != tail; i++, newTail++) {
        newData[newTail] = Data[i];
        if(i == size - 1) {
            i = -1;
        }
    }
    head = 0;
    tail = newTail;
    delete[] Data;
    Data = newData;
    size = newSize;
}

template <class T>
bool Queue<T>::isEmpty() const{
    return head == 0 && tail == 0;
}

template <class T>
T Queue<T>::Dequeue() {
    if (head != tail) {
        size_t index = head;
        if (head != size - 1) {
            head++;
        } else {
            head = 0;
        }
        return Data[index];
    }
    return -1;
}

template <class T>
void Queue<T>::Enqueue(T data) {
    if((tail + 1) % size != head) {
        Data[tail % size] = data;
        tail = (tail + 1) % size;
    }else{
        newBigData();
        Enqueue(data);
    }
}

template <class T>
Queue<T>::Queue() {
    Data = new T[10];
    size = 10;
    head = 0;
    tail = 0;
}
template <class T>
Queue<T>::~Queue() {
    delete[] Data;
}

int main() {
    Queue<int> queue;
    int n = 0;
    cin >> n;
    bool result = true;
    for(int i = 0; i < n; i++) {
        int command = 0;
        int data;
        cin >> command >> data;
        if(!result) {
            continue;
        }
        switch(command) {
            case 2:
                if (queue.isEmpty()){
                    result = result && data == -1;
                } else{
                    result = result && queue.Dequeue() == data;
                }
                break;
            case 3:
                queue.Enqueue(data);
                break;
        }
    }
    cout << (result ? "YES" : "NO");
    return 0;
}

