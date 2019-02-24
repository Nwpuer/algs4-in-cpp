#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <random>
#include <chrono>


//chapter 2.1***************************************
template<typename T>
void show(std::vector<T> a) {
    for (int i = 0; i < a.size(); ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}

template<typename T>
bool isSorted(std::vector<T> a) {
    for (int i = 1; i < a.size(); ++i)
        if (a[i] < a[i-1])
            return false;
    return true;
}

template<typename T>
void SelectionSort(std::vector<T> &a) {
    using std::swap;
    auto N = a.size();
    for (size_t i = 0; i < N; ++i) {
        size_t min = i;
        for (size_t j = i+1; j < N; ++j)
            if(a[j] < a[min])
                min = j;
        swap(a[i], a[min]);
    }
}

template<typename T>
void InsertionSort(std::vector<T> &a) {
    using std::swap;
    auto N = a.size();
    for (size_t i = 1; i < N; ++i) 
        for (size_t j = i; j > 0 && a[j] < a[j-1]; --j)
            swap(a[j], a[j-1]);
}

template<typename T>
void ShellSort(std::vector<T> &a) {
    using std::swap;
    auto N = a.size();
    size_t h = 1;
    while (h < N/3)
        h = h * 3 + 1;
    while (h >= 1) {
        for (auto i = h; i < N; ++i)
            for (auto j = i; j >= h && a[j] < a[j-h]; j -= h)
                swap(a[j], a[j-h]);
        h = h/3;
    }
}


//chapter 2.2***************************************
template<typename T>
void MergeSort_helper(std::vector<T> &a, size_t lo, size_t hi, std::vector<T> &aux);
template<typename T>
void merge(std::vector<T> &a, size_t lo, size_t mid, size_t hi, std::vector<T> &aux);
template<typename T>
void InsertionSort(std::vector<T> &a, size_t lo, size_t hi);

template<typename T>
void MergeSort(std::vector<T> &a) {
    std::vector<T> aux(a.size(), T());//把aux创建在这里是比较合适的，如果放在MergeSort_helper或者merge中的话，因为会反复调用，那么创建aux会成为整个算法耗时最多的部分
    MergeSort_helper(a, 0, a.size()-1, aux);
}

template<typename T>
void MergeSort_helper(std::vector<T> &a, size_t lo, size_t hi, std::vector<T> &aux) {
    if (hi <= lo) return;
    if (hi - lo < 15) //improvement 2.2.2.1
        InsertionSort(a, lo, hi);
    size_t mid = lo + (hi - lo)/2;
    MergeSort_helper(a, lo, mid, aux);
    MergeSort_helper(a, mid+1, hi, aux);
    merge(a, lo, mid, hi, aux);
}

template<typename T>
void merge(std::vector<T> &a, size_t lo, size_t mid, size_t hi, std::vector<T> &aux) {
    if (a[mid] <= a[mid+1]) return;//improvement2.2.2.2
    for (auto k = lo; k <= hi; ++k)//每次只用到了aux的lo～hi的那一部分，并不是aux全都用了
        aux[k] = a[k];
    auto i = lo;
    auto j = mid+1;
    for (auto k = lo; k <= hi; ++k) {
        if (i > mid) a[k] = aux[j++];
        else if (j > hi) a[k] = aux[i++];
        else if (aux[j] < aux[i]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }
}

template<typename T>
void InsertionSort(std::vector<T> &a, size_t lo, size_t hi) {
    using std::swap;
    for (auto i = lo+1; i <= hi; ++i) 
        for (auto j = i; j > lo && a[j] < a[j-1]; --j)
            swap(a[j], a[j-1]);
}

template<typename T>
void MergeSortBU(std::vector<T> &a) {
    auto N = a.size();
    std::vector<T> aux(N, T());
    for (size_t sz = 1; sz < N; sz *= 2) 
        for (size_t lo = 0; lo < N - sz; lo += sz*2)
            merge(a, lo, lo+sz-1, std::min(lo+sz+sz-1, N-1), aux);//x - lo + 1 = 2*sz-->x = lo + 2*sz - 1
}

//chapter 2.3***************************************
template<typename T>
void QuickSort_helper(std::vector<T> &a, size_t lo, size_t hi);
template<typename T> 
size_t partition(std::vector<T> &a, size_t lo, size_t hi);
template<typename T>
void QuickSort3way_helper(std::vector<T> &a, size_t lo, size_t hi);

template<typename T>
void QuickSort(std::vector<T> &a) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(a.begin(), a.end(), std::default_random_engine(seed));
    //QuickSort_helper(a, 0, a.size()-1);
    QuickSort3way_helper(a, 0, a.size()-1);
}

template<typename T>
void QuickSort_helper(std::vector<T> &a, size_t lo, size_t hi) {
    if (hi <= lo + 15) {
        InsertionSort(a, lo, hi);//improvment2.3.3.1
        return;
    }
    auto j = partition(a, lo, hi);
    QuickSort_helper(a, lo, j-1);
    QuickSort_helper(a, j+1, hi);
}

template<typename T>
void QuickSort3way_helper(std::vector<T> &a, size_t lo, size_t hi) {//对于有大量重复值的情况，使用该函数更好
    using std::swap;
    if (hi <= lo + 15) {
        InsertionSort(a, lo, hi);
        return;
    }
    size_t lt = lo, i = lo+1, gt = hi;
    auto v = a[lo];
    while (i <= gt) {
        if (a[i] < v) swap(a[lt++], a[i++]);
        else if (a[i] > v) swap(a[i], a[gt--]);
        else ++i;
    }
    QuickSort3way_helper(a, lo, lt-1);
    QuickSort3way_helper(a, gt+1, hi);
}

template<typename T> 
size_t partition(std::vector<T> &a, size_t lo, size_t hi) {
    using std::swap;
    auto i = lo;
    auto j = hi+1;
    auto v = a[lo];
    while(true) {
        while(a[++i] < v) 
            if (i == hi) break;
        while(v < a[--j]) 
            if (j == lo) break;
        if (i >= j) break;
        swap(a[i], a[j]);
    }
    swap(a[lo], a[j]);//因为i最终会指向大于（等于）v的数，j最终会指向小于（等于）v的数，所以和j指向的数交换，即把小的数放到第一个是合适的，因为要左边全小于（等于）v
    return j;
}


//chapter 2.4***************************************
template<typename T>
void sink(std::vector<T> &a, int k, int N);

template<typename T>
void HeapSort(std::vector<T> &a) {//这里的排序的下标从1开始的，下标为0的元素未参与排序，所以不能再用前面的isSorted()来判断是否排序成功
    using std::swap;
    auto N = a.size();
    for (int k = N/2; k >= 1; --k)
        sink(a, k, N);
    while (N > 1) {
        swap(a[1], a[N--]);
        sink(a, 1, N);
    }
}

template<typename T>
void sink(std::vector<T> &a, int k, int N) {
    using std::swap;
    while (2*k <= N) {
        int j = 2*k;
        if (j < N && a[j] < a[j+1]) ++j;
        if (!(a[k] < a[j])) break;
        swap(a[k], a[j]);
        k = j;
    }
}

template<typename T>
class MaxPQ {
private:
    //具体实现待补充，主要是内存的管理方式和java不太一样，写出来和书上代码相差较大，可以参照stl的实现方式
    //但是主体部分还是清晰的，插入就使用上浮swim()，删除就把第一个和最后一个互换，大小减一，然后下沉sink()
};

