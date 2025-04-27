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

    cout << "�п�J�}�C�j�p: ";
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

    heapSort(arr);

    cout << "\n�Ƨǫ�: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    int newNum;
    cout << "�п�J�n���J���Ʀr: ";
    cin >> newNum;

    arr.push_back(newNum);
    heapSort(arr);

    cout << "���J�᭫�s�Ƨǵ��G: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
