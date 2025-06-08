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

本題實作二種堆積結構：MaxHeap 與 MinHeap，皆為優先佇列常見應用之一，並可作為 Heap Sort 的基礎。

---

## 1. MAXHEAP

使用陣列作為二元堆的儲存結構，並以「最大堆」邏輯維護：父節點必大於或等於子節點。插入時會使用上浮，刪除堆頂時會使用下沉來維持堆序性。
MaxHeap 適合用於即時追蹤最大值的應用場景，如排行榜或最大資源指派問題。
整體時間複雜度為 O(nlogn)，空間複雜度為 O(n)。

---

## 2. MINHEAP

邏輯上與 MaxHeap 相似，但調整為「最小堆」：父節點小於或等於子節點。其插入與刪除操作也分別使用上浮與下沉邏輯。
MinHeap 常用於任務排程、Dijkstra 最短路徑等需要即時取得最小元素的場景。
同樣具備 O(nlogn) 的排序效率與 O(n) 的空間使用特性。

