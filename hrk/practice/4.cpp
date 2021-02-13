#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

// void maxSubarray(vector<int> a, int& i, int& j, int& val) {
//     int x, y, t;
//     x = 0;
//     y = 0;
//     t = a[0];
//     i = x;
//     j = y;
//     val = t;
//     for (int k = 1; k < a.size(); k++) {
//         if (t < 0) {
//             x = k;
//             y = k;
//             t = a[k];
//             if (t >= val) {
//                 val = t;
//                 i = x;
//                 j = y;
//             }
//         } else {
//             y = k;
//             t = t+a[k];
//             if (t >= val) {
//                 val = t;
//                 i = x;
//                 j = y;
//             }
//         }
//     }
// }

// void minSubarray(vector<int> a, int& i, int& j, int& val) {
//     int x, y, t;
//     x = 0;
//     y = 0;
//     t = a[0];
//     i = x;
//     j = y;
//     val = t;
//     for (int k = 1; k < a.size(); k++) {
//         if (t > 0) {
//             x = k;
//             y = k;
//             t = a[k];
//             if (t <= val) {
//                 val = t;
//                 i = x;
//                 j = y;
//             }
//         } else {
//             y = k;
//             t = t+a[k];
//             if (t <= val) {
//                 val = t;
//                 i = x;
//                 j = y;
//             }
//         }
//     }
// }

// int goforward(vector<int> a, int val, int i, int j) {
//     int maxV = val;
//     int k = j+1;
//     int tval = val;
//     while (true) {
//         if (k == a.size()) k = 0;
//         if (k == i) break;
//         tval += a[k];
//         if (tval > maxV) maxV = tval;
//         k++;
//     }
//     return maxV;
// }

// int gobackward(vector<int> a, int val, int i, int j) {
//     int maxV = val;
//     int k = i-1;
//     int tval = val;
//     while (true) {
//         if (k == -1) k = a.size()-1;
//         if (k == j) break;
//         tval += a[k];
//         if (tval > maxV) maxV = tval;
//         k--;
//     }
//     return maxV;
// }

// int solve(vector<int> A) {
//     if (A.size() == 1) return A[0];
//     int sumA = 0;
//     for (int i = 0; i < A.size(); i++) sumA += A[i];
//     int maxi, maxj, maxVal;
//     maxVal = -1e9;
//     maxSubarray(A, maxi, maxj, maxVal);
//     // printf("%d %d %d\n", maxi, maxj ,maxVal);

//     int mini, minj, minVal;
//     minVal = 1e9;
//     minSubarray(A, mini, minj, minVal);
//     // printf("%d %d %d\n", mini, minj, minVal);

//     int ans = 0;
//     if (maxi == 0 && maxj == A.size()-1) {
//         if (minVal < 0) ans = maxVal - minVal;
//         else ans = maxVal;
//     } else {
//         ans = max(goforward(A, maxVal, maxi, maxj), gobackward(A, maxVal, maxi, maxj));
//         if (minVal < 0 && ans > 0) ans = max(ans, sumA-minVal);
//     }
//     return ans;
// }

// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// };

// void solve(vector<int>& preorder, vector<TreeNode*>& nodes) {
//     int step = 1;
//     stack<TreeNode*> s;
//     s.push(nodes[0]);
//     int i = 1;
//     while(i < preorder.size()) {
//         printf("IIIII %d\n", i);
//         TreeNode* x = s.top();
//         if (preorder[i] < x->val) {
//             x->left = nodes[i];
//             s.push(nodes[i]);
//         } else if (preorder[i] > x->val) {
//             while (true) {
//                 s.pop();
//                 if (s.empty() || preorder[i] < s.top()->val) {
//                     x->right = nodes[i];
//                     break;
//                 }
//                 x = s.top();
//             }
//             s.push(nodes[i]);
//         }
//         i++;
//     }
// }

int solve(vector<int>& a, vector<int>& b) {
    int n = a.size();
    int m = b.size();
    int dp[n][m];
    memset(dp, 0, sizeof(dp));
    int rs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i-1 >= 0) {
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
            }
            if (j-1 >= 0) {
                dp[i][j] = max(dp[i][j], dp[i][j-1]);
            }
            if (a[i] == b[j]) {
                if (i-1 >= 0 && j-1 >= 0) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
                } else {
                    dp[i][j] = max(dp[i][j], 1);
                }    
            }
            rs = max(rs, dp[i][j]); 
        }
    }
    return rs;
}
int main() {
    // vector<int> A = {2,-2,2,7,8,0};
    // vector<int> A = {-5,-2,5,6,-2,-7,0,2,8};
    // vector<int> A = {8,-1,-3,8,-6,-9,2,4};
    // vector<int> A = {2,10,-9,-9,0,8,-2,-2,8,9};
    // vector<int> A = {-2, -3, -1};
    // int ans = solve(A);
    // printf("%d\n", ans);

    // vector<int> preorder = {3,1,2};
    // vector<int> preorder = {1,2,3};
    // vector<int> preorder = {4,5,14,20};
    // vector<int> preorder = {19,4,8,11};
    // vector<int> preorder = {8,5,1,7,10,12};
    // vector<TreeNode*> nodes;
    // for (int i = 0; i < preorder.size(); i++) {
    //     TreeNode* n = new TreeNode{preorder[i], NULL, NULL};
    //     nodes.push_back(n);
    // }
    // for (int i = 0; i < preorder.size(); i++) {
    //     printf("%d\n", nodes[i]->val);
    // }
    // solve(preorder, nodes);
    // TreeNode* root = nodes[0];
    // printf("%d\n", root->right->val);

    // vector<int> A = {1,4,2};
    // vector<int> B = {1,2,4};
    // vector<int> A = {2,5,1,2,5};
    // vector<int> B = {10,5,2,1,5,2};
    // vector<int> A = {1,3,7,1,7,5};
    // vector<int> B = {1,9,2,5,1};
    vector<int> A = {2};
    vector<int> B = {2,2};

    printf("%d\n", solve(A, B));
    return 0;
}