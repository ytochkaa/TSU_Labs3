//2.1. Алгоритм Дейкстры поиска следующей перестановки
#include <iostream>
#include <algorithm>

using namespace std;

bool nextPermutation(int *arr, int size) {

    int i = size-2 ; // предпоследний эл-т
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }
    if (i < 0) { // последняя перестановка?
        return false;
    }
    int j = size - 1;
    while (arr[i] >= arr[j]) {
        j--;
    }
    swap(arr[i], arr[j]); // меняем местами
    return true;
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

void deykstri(int *arr2, int size) {

    sort(arr2, arr2 + size);
    printArray(arr2, size);

    while (nextPermutation(arr2, size)) {
        printArray(arr2, size);
    }
    delete[] arr2;
}

int main(){
    int size;
    cout << "enter size of array:" << endl;
    cin >> size;
    int *arr2 = new int[size];
    for (int i = 0; i < size; i++) {
        cout << " p[" << i << "]= ";
        cin >> arr2[i];
    }
    printArray(arr2, size);
    deykstri(arr2, size);
    return 0;
}


