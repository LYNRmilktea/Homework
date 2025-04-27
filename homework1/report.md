# 41043236 
# 41043257

作業一

## 解題說明

實作四種排序法，包括 Insertion Sort、Quick Sort、Merge Sort、Heap Sort。
每種排序法需有排序前、排序後的資料，且使用者可自行插入數字後再次排序。

### 解題策略

1.	Insertion Sort(插入排序)：一個元素從未排序的部分找到適當的位置，並插入到已排序的部分，直到所有元素都完成排序。
2.	Quick Sort(快速排序)：數列分割成左右兩部分，左部分的元素小於等於基準元素，右部分的元素大於等於基準元素，然後對每個子部分再進行同樣的操作。
3.	Merge Sort(合併排序)：將數列分割成兩個子數列，對每個子數列遞迴地進行排序，然後將兩個排序好的子數列合併起來。	
4.	Heap Sort(堆積排序)：將數列轉換成最大堆，然後反覆從頂部取出最大元素，並將堆的大小減少，直到排序完成。

## 程式實作

Insertion Sort 程式碼：

```cpp
#include <iostream>
#include <vector>
#include <random>
using namespace std;

void insertionSort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    vector<int> arr;
    vector<int> originalArr;
    int numCount;
    cout << "請輸入陣列大小:";
    cin >> numCount;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    for (int i = 0; i < numCount; i++) {
        int num = dis(gen);
        arr.push_back(num);
        originalArr.push_back(num);
    }

    cout << "未排序前: ";
    for (int num : originalArr) {
        cout << num << " ";
    }

    insertionSort(arr);

    cout << "\n排序後: ";
    for (int num : arr) {
        cout << num << " ";
    }
    int n;
    cout << "\n請輸入要插入的數字: ";
    cin >> n;
    arr.push_back(n);
    insertionSort(arr);
    cout << "排序後: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
```
Quick Sort 程式碼:

```cpp
#include <iostream>
#include <vector>
#include <random>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<int> arr;
    vector<int> originalArr;
    int numCount;

    cout << "請輸入陣列大小: ";
    cin >> numCount;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < numCount; i++) {
        int num = dis(gen);
        arr.push_back(num);
        originalArr.push_back(num);
    }

    cout << "未排序前: ";
    for (int num : originalArr) {
        cout << num << " ";
    }

    quickSort(arr, 0, arr.size() - 1);

    cout << "\n排序後: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    int newNum;
    cout << "請輸入要插入的數字: ";
    cin >> newNum;

    arr.push_back(newNum);
    quickSort(arr, 0, arr.size() - 1);

    cout << "插入後重新排序結果: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
```

Merge Sort 程式碼:

```cpp
#include <iostream>
#include <vector>
#include <random>
using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main() {
    vector<int> arr;
    vector<int> originalArr;
    int numCount;

    cout << "請輸入陣列大小: ";
    cin >> numCount;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < numCount; i++) {
        int num = dis(gen);
        arr.push_back(num);
        originalArr.push_back(num);
    }

    cout << "未排序前: ";
    for (int num : originalArr) {
        cout << num << " ";
    }

    mergeSort(arr, 0, arr.size() - 1);

    cout << "\n排序後: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    int newNum;
    cout << "請輸入要插入的數字: ";
    cin >> newNum;

    arr.push_back(newNum);
    mergeSort(arr, 0, arr.size() - 1);

    cout << "插入後重新排序結果: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
```

Heap Sort 程式碼:

```cpp
#include <iostream>
#include <vector>
#include <random>
using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    vector<int> arr;
    vector<int> originalArr;
    int numCount;

    cout << "請輸入陣列大小: ";
    cin >> numCount;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < numCount; i++) {
        int num = dis(gen);
        arr.push_back(num);
        originalArr.push_back(num);
    }

    cout << "未排序前: ";
    for (int num : originalArr) {
        cout << num << " ";
    }

    heapSort(arr);

    cout << "\n排序後: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    int newNum;
    cout << "請輸入要插入的數字: ";
    cin >> newNum;

    arr.push_back(newNum);
    heapSort(arr);

    cout << "插入後重新排序結果: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
```

## 效能分析

時間複雜度：
1.	Insertion Sort：O(n)，n為陣列長度(最壞的情況下則是O(n^2))。
2.	Quick Sort：正常快速排序下為O(nlogn)，n為陣列長度(最壞的情況下則是O(n^2))。
3.	Merge Sort：O(nlogn)，n為陣列長度
4.	Heap Sort：O(nlogn)，n為陣列長度
   
空間複雜度：
1.	Insertion Sort：O(1)，原地排序算法
2.	Quick Sort：O(logn)，遞迴的最大深度
3.	Merge Sort：O(n)，n為陣列長度，需要額外的空間來存儲合併過程中的暫時數據
4.	Heap Sort：O(1)，原地排序算法


## 測試與驗證

### 測試案例
Insertion Sort
![image](https://github.com/user-attachments/assets/0454707b-b1a6-4d5b-90c2-25c72b56c87a)

Quick Sort
![image](https://github.com/user-attachments/assets/e201728d-3a99-4c63-9ffb-9e11a332ac7d)

Merge Sort
![image](https://github.com/user-attachments/assets/6cbc5865-de97-4384-b50b-37debb366b1a)

Heap Sort
![image](https://github.com/user-attachments/assets/3f18782a-afa1-48a2-8e50-40a2c51e22dd)


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
