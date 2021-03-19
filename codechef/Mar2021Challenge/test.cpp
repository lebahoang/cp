#include <iostream>
#include "treegenerator.h"
using namespace std;
using namespace tree_generator_by_ouuan;
int main() {
    int t = 1;
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        int n = 500000;
        int k = 2;
        printf("%d %d\n", n, k);
        Tree t(n);
        t.shuffleNodes(1);
        cout << t << endl;
    }
    
    return 0;
}