# 41043236 
# 41043257

作業二

# 第一題

## 解題說明

題目要求實作兩個 C++ 類別：一個是MinPQ，定義了最小優先權佇列的基本操作；另一個是從 MinPQ 派生的 MinHeap 類別，實現了所有 MinPQ 函數。需要確保 MinHeap 中的每個函數的時間複雜度與對應的 MaxHeap 相同。這樣才可以保證 MinHeap 的效率與 MaxHeap 相當。

### 解題策略

MaxHeap（最大堆）：
　將數列元素依序插入最大堆結構中，每次插入元素後透過上浮操作維持「父節點 ≥ 子節點」的堆序性。接著從堆頂反覆取出最大元素並下沉堆尾元素，持續調整堆結構直到堆為空

MinHeap（最小堆）：
　將數列元素依序插入最小堆結構中，每次插入元素後透過上浮操作維持「父節點 ≤ 子節點」的堆序性。從堆頂反覆取出最小元素並下沉堆尾元素以維持最小堆特性
 
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


## 第二題

## 解題說明

模擬隨機插入值到一個初始為空的二元搜索樹中，然後測量樹的高度並將其除以 log2n。需要對 n = 100、500、1000、2000、3000、10,000 執行此操作，然後繪製函數圖表。最後，驗證比率是否大約為 2。


## 程式實作

BST 程式碼：

```cpp
#include <iostream>
#include <utility>
#include <stack>
#include <random>
#include <cmath>
#include <iomanip>
using namespace std;

template <class K, class E>
class Dictionary {
public:
	virtual bool IsEmpty() const = 0;
	virtual pair<K, E>* Get(const K&) = 0;
	virtual void Insert(const pair<K, E>&) = 0;
	virtual void Delete(const K&) = 0;
};

template <class K, class E>
class BST : public Dictionary<K, E> {
private:
	struct TreeNode {
		pair<K, E> data;
		TreeNode* leftChild;
		TreeNode* rightChild;
		int leftSize;
		TreeNode(const pair<K, E>& thePair)
			: data(thePair), leftChild(nullptr), rightChild(nullptr), leftSize(0) {
		}
	};

	TreeNode* root;
	pair<K, E>* Get(TreeNode*, const K&) const;
	void Insert(TreeNode*&, const pair<K, E>&);
	int calculateHeight(TreeNode* root) const;
	TreeNode* Delete(TreeNode*&, const K&, bool& deletedLeft);

public:
	BST() : root(nullptr) {}
	~BST();
	bool IsEmpty() const { return root == nullptr; }
	pair<K, E>* Get(const K&);
	pair<K, E>* RankGet(int);
	void Insert(const pair<K, E>&);
	void Delete(const K&);
	int Height() const { return calculateHeight(root); }
	int Size(TreeNode*) const;
	TreeNode* GetRoot() const { return root; }
};

template <class K, class E>
BST<K, E>::~BST() {
	stack<TreeNode*> s;
	TreeNode* current = root;
	while (current || !s.empty()) {
		while (current) {
			s.push(current);
			current = current->leftChild;
		}
		current = s.top(); s.pop();
		TreeNode* temp = current;
		current = current->rightChild;
		delete temp;
	}
}

template <class K, class E>
pair<K, E>* BST<K, E>::Get(const K& k) {
	return Get(root, k);
}

template <class K, class E>
pair<K, E>* BST<K, E>::Get(TreeNode* p, const K& k) const {
	if (!p) return nullptr;
	if (k < p->data.first) return Get(p->leftChild, k);
	if (k > p->data.first) return Get(p->rightChild, k);
	return &p->data;
}

template <class K, class E>
pair<K, E>* BST<K, E>::RankGet(int r) {
	TreeNode* currentNode = root;
	while (currentNode) {
		if (r < currentNode->leftSize) {
			currentNode = currentNode->leftChild;
		}
		else if (r > currentNode->leftSize) {
			r -= currentNode->leftSize + 1;
			currentNode = currentNode->rightChild;
		}
		else {
			return &(currentNode->data);
		}
	}
	return nullptr;
}

template <class K, class E>
void BST<K, E>::Insert(const pair<K, E>& thePair) {
	TreeNode* p = root;
	TreeNode* pp = nullptr;
	while (p) {
		pp = p;
		if (thePair.first < p->data.first) {
			p->leftSize++;
			p = p->leftChild;
		}
		else if (thePair.first > p->data.first) {
			p = p->rightChild;
		}
		else {
			p->data.second = thePair.second;
			return;
		}
	}
	TreeNode* newNode = new TreeNode(thePair);
	if (!root) root = newNode;
	else if (thePair.first < pp->data.first) pp->leftChild = newNode;
	else pp->rightChild = newNode;
}

template <class K, class E>
void BST<K, E>::Delete(const K& k) {
	bool deletedLeft = false;
	root = Delete(root, k, deletedLeft);
}

template <class K, class E>
typename BST<K, E>::TreeNode* BST<K, E>::Delete(TreeNode*& node, const K& k, bool& deletedLeft) {
	if (!node) return nullptr;

	if (k < node->data.first) {
		node->leftChild = Delete(node->leftChild, k, deletedLeft);
		if (deletedLeft) node->leftSize--;
	}
	else if (k > node->data.first) {
		node->rightChild = Delete(node->rightChild, k, deletedLeft);
	}
	else {
		deletedLeft = true;
		if (!node->leftChild) {
			TreeNode* temp = node->rightChild;
			delete node;
			return temp;
		}
		else if (!node->rightChild) {
			TreeNode* temp = node->leftChild;
			delete node;
			return temp;
		}
		else {
			TreeNode* s = node->leftChild;
			TreeNode* sp = node;
			while (s->rightChild) {
				sp = s;
				s = s->rightChild;
			}
			node->data = s->data;
			bool dummy = false;
			node->leftChild = Delete(node->leftChild, s->data.first, dummy);
			node->leftSize--;
		}
	}
	return node;
}

template <class K, class E>
int BST<K, E>::Size(TreeNode* node) const {
	if (!node) return 0;
	return Size(node->leftChild) + Size(node->rightChild) + 1;
}

template <class K, class E>
int BST<K, E>::calculateHeight(TreeNode* root) const {
	if (!root) return 0;
	int leftHeight = calculateHeight(root->leftChild);
	int rightHeight = calculateHeight(root->rightChild);
	return max(leftHeight, rightHeight) + 1;
}

int main() {
	const int testSizes[] = { 100, 500, 1000, 2000, 3000, 4000, 5000, 10000 };
	const int numTests = sizeof(testSizes) / sizeof(testSizes[0]);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, 1000000);

	cout << left << setw(10) << "n" << setw(15) << "height" << setw(20) << "log2(n)" << setw(20) << "height / log2(n)" << endl;
	cout << fixed << setprecision(4);

	for (int i = 0; i < numTests; ++i) {
		int n = testSizes[i];
		BST<int, int> bst;
		for (int j = 0; j < n; ++j) {
			int key = dist(gen);
			bst.Insert(make_pair(key, 0));
		}
		int height = bst.Height();
		double log2n = log2(n);
		double ratio = height / log2n;
		cout << setw(10) << n << setw(15) << height << setw(20) << log2n << setw(20) << ratio << endl;
	}

	return 0;
}
```

## 效能分析

時間複雜度：
BST:若資料為亂數插入為平均 O(logn) 若資料為升序或降序插入，BST 退化為鏈表，效率最差為 O(n)
空間複雜度：
BST:O(n)

## 測試與驗證

### 測試案例
![image](https://github.com/user-attachments/assets/f5bdbfad-bfd8-414a-9045-2042df41eccf)
![output](https://github.com/user-attachments/assets/6b80fb61-42ae-4cf9-8937-6da635b5f5d0)

## 申論及開發報告

本題實作一種樹狀資料結構：Binary Search Tree（BST），為常見的查找與排序結構，可應用於搜尋、排名查找、動態資料集維護等場景

---

## 1. BST

使用指標串接的二元樹結構，每個節點皆含有 key-value 配對，並遵守「左小右大」的排序原則。插入新節點時，依照 key 遞迴或迴圈判斷插入位置；刪除節點時，依據其子樹數量進行相應處理（包含替換前驅節點）。
