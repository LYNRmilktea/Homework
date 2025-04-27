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
