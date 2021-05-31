#include <cstdio>
#include <iostream>
#include "tree_generator.h"
using namespace std;
using namespace tree_generator_by_ouuan;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined test.cpp && ./s.out

int main() {
    Tree t;
    t.complete(299990, 4, 0);
    t.chain(10, 0);
    t.shuffleNodes(1);
    t.shuffleEdges();
    cout << t;
}