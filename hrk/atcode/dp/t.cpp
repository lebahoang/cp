#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <string>
#include <queue>
#include <cstring>

using namespace std;
// bool go(vector<vector<int>>& matrix, int target, int n, int m, int a, int b, int c, int d) {
//     printf("%d %d %d %d\n", a, b, c, d);
//     if (a > b || c > d) return false; 
//     int midRow = (a+b)/2;
//     int midCol = (c+d)/2;
//     if (a == b && c == d && matrix[midRow][midCol] != target) return false;
//     if (matrix[midRow][midCol] == target) return true;
//     else if (matrix[midRow][midCol] > target) {
//         if (go(matrix, target, n, m, a, b, c, midCol-1)) return true;
//         return go(matrix, target, n, m, a, midRow-1, midCol, d);
//     }
//     if (go(matrix, target, n, m, midRow+1, b, c, midCol)) return true;
//     return go(matrix, target, n, m, a, b, midCol+1, d);
// }
// bool solve(vector<vector<int>>& matrix, int target) {
//     int n = matrix.size();
//     if (n == 0) return false;
//     int m = matrix[0].size();
//     return go(matrix, target, n, m, 0, n-1, 0, m-1);
// }
int main() {
    // vector<vector<int>> m = {
    //     {1,4,7,11,15},
    //     {2,5,8,12,19},
    //     {3,6,9,16,22},
    //     {10,13,14,17,24},
    //     {18,21,23,26,30}
    // };
    // vector<vector<int>> m = {
    //     {1,3,5,7,9},
    //     {2,4,6,8,10},
    //     {11,13,15,17,19},
    //     {12,14,16,18,20},
    //     {21,22,23,24,25}
    // };
    // int target = 261;
    // printf("%d\n", solve(m, target));
}