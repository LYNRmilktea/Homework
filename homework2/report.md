# 41043236 
# 41043257

作業二

## 第一題

## 解題說明

題目要求實作兩個 C++ 類別：一個是MinPQ，定義了最小優先權佇列的基本操作；另一個是從 MinPQ 派生的 MinHeap 類別，實現了所有 MinPQ 函數。需要確保 MinHeap 中的每個函數的時間複雜度與對應的 MaxHeap 相同。這樣才可以保證 MinHeap 的效率與 MaxHeap 相當。


## 程式實作

MAXHEAP 程式碼：

```cpp
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
```
MINHEAP 程式碼:

```cpp
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

int min(int a, int b) {
    return (a < b) ? a : b;
}

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T& x) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;
    int heapSize;
    int capacity;

public:
    MinHeap(int theCapacity = 10);
    ~MinHeap();
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
MinHeap<T>::MinHeap(int theCapacity) {
    if (theCapacity < 1) throw runtime_error("Capacity must be >= 1");
    capacity = theCapacity;
    heapSize = 0;
    heap = new T[capacity + 1];
}

template <class T>
MinHeap<T>::~MinHeap() {
    delete[] heap;
}

template <class T>
void MinHeap<T>::Push(const T& e) {
    if (heapSize == capacity) {
        ChangeSize1D(heap, capacity, 2 * capacity);
        capacity *= 2;
    }
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > e) {
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }
    heap[currentNode] = e;
}

template <class T>
void MinHeap<T>::Pop() {
    if (IsEmpty()) throw runtime_error("Heap is empty. Cannot delete");
    T lastE = heap[heapSize--];
    int currentNode = 1;
    int child = 2;
    while (child <= heapSize) {
        if (child < heapSize && heap[child] > heap[child + 1]) child++;
        if (lastE <= heap[child]) break;
        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    heap[currentNode] = lastE;
}

template <class T>
const T& MinHeap<T>::Top() const {
    if (IsEmpty()) throw runtime_error("Heap is empty. No top element");
    return heap[1];
}

template <class T>
void MinHeap<T>::PrintHeap() const {
    for (int i = 1; i <= heapSize; ++i)
        cout << heap[i] << " ";
    cout << endl;
}

int main() {
    MinHeap<int> minHeap(10);
    minHeap.Push(10);
    minHeap.Push(14);
    minHeap.Push(17);
    minHeap.Push(20);
    minHeap.Push(30);
    minHeap.Push(21);
    minHeap.Push(44);

    cout << "Pop and print in order:" << endl;
    while (!minHeap.IsEmpty()) {
        cout << minHeap.Top() << " ";
        minHeap.Pop();
    }


    minHeap.Push(10);
    minHeap.Push(14);
    minHeap.Push(17);
    minHeap.Push(20);
    minHeap.Push(30);
    minHeap.Push(21);
    minHeap.Push(44);

    cout << endl << "Printheap Memory for debug:" << endl;
    minHeap.PrintHeap();

    return 0;
}
```

## 效能分析

時間複雜度：
MAXHEAP：O(nlogn)
MINHEAP：O(nlogn)
空間複雜度：
MAXHEAP：O(n)
MINHEAP：O(n)


## 測試與驗證

### 測試案例
MAXHEAP
![image](https://github.com/user-attachments/assets/171d3cc9-f371-44a8-8617-2b6e0f0c3001)

MINHEAP
![image](https://github.com/user-attachments/assets/2eb7fb8d-1427-4301-9850-81d26175ea32)

## 申論及開發報告

本次作業實作四種常見排序法：Insertion Sort、Quick Sort、Merge Sort、Heap Sort。

---

## 1. Insertion Sort

使用陣列（Array）作為資料結構，透過依序插入元素的方式模擬手動排序的過程。  
Insertion Sort 在資料量小或資料接近有序時特別有效，結構簡單，適合基本排序操作。

---

## 2. Quick Sort

採用分治法（Divide and Conquer）策略與遞迴（Recursion）實作，利用樞紐（pivot）分割陣列並遞迴排序。  
Quick Sort 平均時間複雜度為 O(n log n)，排序速度快。

---

## 3. Merge Sort

透過遞迴與分治，將資料分成兩半排序後合併，使用額外 O(n) 空間儲存暫存資料。  
Merge Sort 穩定且時間複雜度固定為 O(n log n)，適合資料量大且需要穩定排序的情況。

---

## 4. Heap Sort

用陣列建構最大堆（Max Heap）結構，反覆將最大元素取出並重新堆化（heapify）完成排序。  
Heap Sort 是原地排序法，空間複雜度低，適合需要節省空間且資料量大的場合。
