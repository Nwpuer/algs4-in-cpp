#pragma once 
#include <vector>
#include <string> 
#include <stdexcept>
#include <iostream>


class WeightedQuickUnionUF {
private:
    std::vector<size_t> id;
    size_t count;
    std::vector<size_t> sz;
public: 
    WeightedQuickUnionUF(size_t n):count(n) {
        id.reserve(n);//improve the performance
        for (size_t i = 0; i < n; ++i)
            id.push_back(i);
        sz.reserve(n);
        for (size_t i = 0; i < n; ++i)
            sz.push_back(1);
    }
    WeightedQuickUnionUF(const WeightedQuickUnionUF &) = default;
    WeightedQuickUnionUF &operator=(const WeightedQuickUnionUF &) = default;
    WeightedQuickUnionUF(WeightedQuickUnionUF &&) noexcept = default;
    WeightedQuickUnionUF &operator=(WeightedQuickUnionUF &&) = default;
    ~WeightedQuickUnionUF() = default;

    size_t Count() const {
        return count;
    }

    bool Connected(size_t p, size_t q) const {
        return Find(p) == Find(q);
    }

    size_t Find(size_t p) const {
        Validate(p);
        while (p != id[p])
            p = id[p];
        return p;
    }

    void Union(size_t p, size_t q) {
        Validate(p);
        Validate(q);

        auto pRoot = Find(p);
        auto qRoot = Find(q);

        if (pRoot == qRoot) return;

        if (sz[pRoot] < sz[qRoot]) {
            id[pRoot] = qRoot;
            sz[pRoot] += sz[qRoot];
        }
        else {
            id[qRoot] = pRoot;
            sz[pRoot] += sz[qRoot];
        }
        --count;
    }

private: 
    void Validate(size_t p) const {
        if (p >= id.size())
            throw std::out_of_range("index out of range");
    }

public:
    static void MainTest() {
        size_t n;
        std::cin >> n;
        WeightedQuickUnionUF uf(n);
        size_t p, q;
        while (std::cin >> p >> q) {
            if (uf.Connected(p, q)) continue;
            uf.Union(p, q);
            std::cout << p << " " << q << std::endl;
        }
        std::cout << uf.Count() << " components" << std::endl;
    }
};
