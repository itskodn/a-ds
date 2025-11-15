#include <iostream>
#include <vector>
#include <algorithm>

void InsertionSort(std::vector<int>& array, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int value = array[i];
        int k = i - 1;
        while (k >= l && array[k] > value) {
            array[k + 1] = array[k];
            k -= 1;
        }
        array[k + 1] = value;
    }
}

void Merge(std::vector<int>& array, int l, int mid, int r) {
    int size = r - l + 1;
    int* temp = new int[size];
    int i = l;
    int j = mid + 1;
    int k = 0;    
    while (i <= mid && j <= r) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = array[i++];
    }
    
    while (j <= r) {
        temp[k++] = array[j++];
    }
    for (int m = 0; m < size; m++) {
        array[l + m] = temp[m];
    }
    
    delete[] temp;
}

void MergeAndInsertionSort(std::vector<int>& array, int l, int r) {
    if ((r - l + 1) <= 15) {
        InsertionSort(array, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    MergeAndInsertionSort(array, l, mid);
    MergeAndInsertionSort(array, mid + 1, r);
    Merge(array, l, mid, r);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }
    MergeAndInsertionSort(vec, 0, n - 1);
    for (int i = 0; i < n; i++) {
        std::cout << vec[i] << " ";
    }
    return 0;
}