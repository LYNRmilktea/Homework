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
    cout << "�п�J�}�C�j�p:";
    cin >> numCount;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    for (int i = 0; i < numCount; i++) {
        int num = dis(gen);
        arr.push_back(num);
        originalArr.push_back(num);
    }

    cout << "���Ƨǫe: ";
    for (int num : originalArr) {
        cout << num << " ";
    }

    insertionSort(arr);

    cout << "\n�Ƨǫ�: ";
    for (int num : arr) {
        cout << num << " ";
    }
    int n;
    cout << "\n�п�J�n���J���Ʀr: ";
    cin >> n;
    arr.push_back(n);
    insertionSort(arr);
    cout << "�Ƨǫ�: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
