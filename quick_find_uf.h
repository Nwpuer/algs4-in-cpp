#pragma once 
#include <vector>
#include <string> 
#include <stdexcept>
#include <iostream>


class QuickFindUF {
private:
    std::vector<size_t> id;
    size_t count;
public: 
    QuickFindUF(size_t n):count(n) {
        id.reserve(n);//improve the performance
        for (size_t i = 0; i < n; ++i)
            id.push_back(i);
    }
    QuickFindUF(const QuickFindUF &) = default;
    QuickFindUF &operator=(const QuickFindUF &) = default;
    QuickFindUF(QuickFindUF &&) noexcept = default;
    QuickFindUF &operator=(QuickFindUF &&) = default;
    ~QuickFindUF() = default;

    size_t Count() const {
        return count;
    }

    bool Connected(size_t p, size_t q) const {
        return Find(p) == Find(q);
    }

    size_t Find(size_t p) const {
        Validate(p);
        return id[p];
    }

    void Union(size_t p, size_t q) {
        Validate(p);
        Validate(q);

        auto pID = id[p];
        auto qID = id[q];

        if (pID == qID) return;

        for (size_t i = 0; i < id.size(); ++i) 
            if (id[i] == pID) 
                id[i] = qID;
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
        QuickFindUF uf(n);
        size_t p, q;
        while (std::cin >> p >> q) {
            if (uf.Connected(p, q)) continue;
            uf.Union(p, q);
            std::cout << p << " " << q << std::endl;
        }
        std::cout << uf.Count() << " components" << std::endl;
    }
};