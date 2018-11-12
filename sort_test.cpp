#include <iostream>
#include <vector>
#include "sort.h"

int main() {
    std::vector<int> vi;
    for (int i = 0; i < 100000; ++i)
        vi.push_back(rand());
    auto start = clock();
    //SelectionSort<int>(vi);
    //MergeSort<int>(vi);
    //MergeSortBU<int>(vi);
    QuickSort<int>(vi);
    auto end = clock();
    std::cout << "is sorted? : " << (isSorted<int>(vi) ? "yes" : "no") << std::endl;
    std::cout << "time: " << ((double)end - start)/CLOCKS_PER_SEC << "s" << std::endl;
}