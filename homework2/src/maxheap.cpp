#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

int min(int a, int b) {
    return (a < b) ? a : b;
}

template <class T>
class MaxPQ {
public:
    virtual ~MaxPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T& x) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MaxHeap : public MaxPQ<T> {
private:
    T* heap;
    int heapSize;
    int capacity;

public:
    MaxHeap(int theCapacity = 10);
    ~MaxHeap();
    void Push(const T& e);
    void Pop();
    const T& Top() const;
    bool IsEmpty() const { return heapSize == 0; }
    int Size() const { return heapSize; }
    void PrintHeap() const;
};

template <class T>
void ChangeSize1D(T*& a, int oldSize, int newSize) {
    if (newSize < 0) throw runtime_error("New length must be >= 0");
    T* temp = new T[newSize + 1];
    int number = min(oldSize, newSize);
    copy(a, a + number + 1, temp);
    delete[] a;
    a = temp;
}

template <class T>
MaxHeap<T>::MaxHeap(int theCapacity) {
    if (theCapacity < 1) throw runtime_error("Capacity must be >= 1");
    capacity = theCapacity;
    heapSize = 0;
    heap = new T[capacity + 1];
}

template <class T>
MaxHeap<T>::~MaxHeap() {
    delete[] heap;
}

template <class T>
void MaxHeap<T>::Push(const T& e) {
    if (heapSize == capacity) {
        ChangeSize1D(heap, capacity, 2 * capacity);
        capacity *= 2;
    }
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] < e) {
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }
    heap[currentNode] = e;
}

template <class T>
void MaxHeap<T>::Pop() {
    if (IsEmpty()) throw runtime_error("Heap is empty. Cannot delete");
    T lastE = heap[heapSize--];
    int currentNode = 1;
    int child = 2;
    while (child <= heapSize) {
        if (child < heapSize && heap[child] < heap[child + 1]) child++;
        if (lastE >= heap[child]) break;
        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    heap[currentNode] = lastE;
}

template <class T>
const T& MaxHeap<T>::Top() const {
    if (IsEmpty()) throw runtime_error("Heap is empty. No top element");
    return heap[1];
}

template <class T>
void MaxHeap<T>::PrintHeap() const {
    for (int i = 1; i <= heapSize; ++i)
        cout << heap[i] << " ";
    cout << endl;
}

int main() {
    MaxHeap<int> maxHeap(10);
    maxHeap.Push(100);
    maxHeap.Push(70);
    maxHeap.Push(80);
    maxHeap.Push(20);
    maxHeap.Push(30);
    maxHeap.Push(20);
    maxHeap.Push(50);

    cout << "Pop and print in order:" << endl;
    while (!maxHeap.IsEmpty()) {
        cout << maxHeap.Top() << " ";
        maxHeap.Pop();
    }
    cout << endl;


    maxHeap.Push(100);
    maxHeap.Push(70);
    maxHeap.Push(80);
    maxHeap.Push(20);
    maxHeap.Push(30);
    maxHeap.Push(20);
    maxHeap.Push(50);

    cout << "Printheap Memory for debug:" << endl;
    maxHeap.PrintHeap();
    return 0;
}
