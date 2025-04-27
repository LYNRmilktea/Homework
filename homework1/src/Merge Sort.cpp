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

    mergeSort(arr, 0, arr.size() - 1);

    cout << "\n�Ƨǫ�: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    int newNum;
    cout << "�п�J�n���J���Ʀr: ";
    cin >> newNum;

    arr.push_back(newNum);
    mergeSort(arr, 0, arr.size() - 1);

    cout << "���J�᭫�s�Ƨǵ��G: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
