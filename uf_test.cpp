#include <iostream>
#include <fstream>
#include "quick_find_uf.h"
#include "quick_union_uf.h"
#include "weighted_quick_union_uf.h"

int main() {
    std::ifstream in("../data/tinyUF.txt");
    std::cin.rdbuf(in.rdbuf());

    //QuickFindUF::MainTest();
    //QuickUnionUF::MainTest();
    WeightedQuickUnionUF::MainTest();
}

