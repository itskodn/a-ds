#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <string>

class ArrayGenerator {
public:
    std::vector<int> RandomArray() {
        int size = 100000;
        int min_ = 0;
        int max_ = 6000;
        std::vector<int> vec(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min_, max_);
        for (int i = 0; i < size; i++) {
            vec[i] = distrib(gen);
        }
        return vec;
    }
    
    std::vector<int> ReverseSorted() {
        int size = 100000;
        std::vector<int> vec(size);
        for (int i = 0; i < size; i++) {
            vec[i] = size - i;
        }
        return vec;
    }
    
    std::vector<int> AlmostSorted() {
        int size = 100000;
        int s = 100;
        std::vector<int> vec(size);
        for (int i = 0; i < size; i++) {
            vec[i] = i;
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, size - 1);
        
        for (int i = 0; i < s; i++) {
            int ind1 = distrib(gen);
            int ind2 = distrib(gen);
            std::swap(vec[ind1], vec[ind2]);
        }
        return vec;
    }
    
    std::vector<int> subarray(const std::vector<int>& source, int size) {
        return std::vector<int>(source.begin(), source.begin() + size);
    }
};

void insertionSort(std::vector<int>& arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int value = arr[i];
        int k = i - 1;
        while (k >= l && arr[k] > value) {
            arr[k + 1] = arr[k];
            k--;
        }
        arr[k + 1] = value;
    }
}

void merge(std::vector<int>& arr, int l, int mid, int r) {
    int size = r - l + 1;
    int* temp = new int[size];
    
    int i = l, j = mid + 1, k = 0;
    
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= r) {
        temp[k++] = arr[j++];
    }
    for (int m = 0; m < size; m++) {
        arr[l + m] = temp[m];
    }
    
    delete[] temp;
}

void standardMergeSort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    standardMergeSort(arr, l, mid);
    standardMergeSort(arr, mid + 1, r);
    
    if (arr[mid] <= arr[mid + 1]) {
        return;
    }
    
    merge(arr, l, mid, r);
}

void hybridMergeSort(std::vector<int>& arr, int l, int r, int base) {
    if ((r - l + 1) <= base) {
        insertionSort(arr, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    hybridMergeSort(arr, l, mid, base);
    hybridMergeSort(arr, mid + 1, r, base);
    
    if (arr[mid] <= arr[mid + 1]) {
        return;
    }
    
    merge(arr, l, mid, r);
}

class SortTester {
public:
    double testStandardMergeSort(const std::vector<int>& arr, int repetitions = 3) {
        return testSorting(arr, 0, 0, repetitions);
    }
    
    double testHybridMergeSort(const std::vector<int>& arr, int base, int repetitions = 3) {
        return testSorting(arr, 1, base, repetitions);
    }
    
private:
    double testSorting(const std::vector<int>& arr, int algorithmType, int base, int repeat) {
        std::vector<long long> times;
        
        for (int i = 0; i < repeat; i++) {
            std::vector<int> copy_array = arr;  
            auto start = std::chrono::high_resolution_clock::now();
            if (algorithmType == 0) {
                standardMergeSort(copy_array, 0, copy_array.size() - 1);
            } else {
                hybridMergeSort(copy_array, 0, copy_array.size() - 1, base);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            times.push_back(duration.count());
        }
        
        std::sort(times.begin(), times.end());
        return static_cast<double>(times[times.size() / 2]);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    ArrayGenerator generator;
    SortTester tester;
    std::vector<int> bases = {5, 10, 15, 20, 30, 50};
    
    auto random = generator.RandomArray();
    auto reverse = generator.ReverseSorted();
    auto almost = generator.AlmostSorted();
    
    
    std::ofstream out1("mergesort_random.txt");
    std::ofstream out2("mergesort_reversed.txt");
    std::ofstream out3("mergesort_almost_sorted.txt");
    std::ofstream out4("merge&insertion_random.txt");
    std::ofstream out5("merge&insertion_reversed.txt");
    std::ofstream out6("merge&insertion_almost_sorted.txt");
    
    for (int size = 500; size <= 100000; size += 100) {
        std::vector<int> random_array = generator.subarray(random, size);
        std::vector<int> reversed_array = generator.subarray(reverse, size);
        std::vector<int> almost_sorted_array = generator.subarray(almost, size);
        
        double random_time = tester.testStandardMergeSort(random_array, 3);
        double reversed_time = tester.testStandardMergeSort(reversed_array, 3);
        double nearly_time = tester.testStandardMergeSort(almost_sorted_array, 3);
        
        out1 << size << " " << random_time << "\n";
        out2 << size << " " << reversed_time << "\n";
        out3 << size << " " << nearly_time << "\n";
        
        out4 << size;
        out5 << size;
        out6 << size;
        
        for (int b : bases) {
            double random_time = tester.testHybridMergeSort(random_array, b, 3);
            double reversed_time = tester.testHybridMergeSort(reversed_array, b, 3);
            double nearly_time = tester.testHybridMergeSort(almost_sorted_array, b, 3);
            
            out4 << " " << random_time;
            out5 << " " << reversed_time;
            out6 << " " << nearly_time;
        }
        out4 << "\n";
        out5 << "\n";
        out6 << "\n";
    }
    
    out1.close(); out2.close(); out3.close();
    out4.close(); out5.close(); out6.close();
    
    std::cout << "Тестирование завершено!" << std::endl;
    return 0;
}