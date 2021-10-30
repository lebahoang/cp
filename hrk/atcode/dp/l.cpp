#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
using ll = long long;

ll total[3005][3005];
ll dpmax[3005][3005];
int arr[3005];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        dpmax[i][i] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (j-1 >= i) {
                total[i][j] = total[i][j-1] + arr[j];
            } else {
                total[i][j] = arr[j];
            }  
        }
    }
    for (int i = 0; i < n; i++) {
        if (i+1 < n) {
            dpmax[i][i+1] = max(arr[i], arr[i+1]);
        }
    }
    for (int k = 2; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (i+k < n) {
                dpmax[i][i+k] = max(arr[i]+total[i+1][i+k]-dpmax[i+1][i+k], arr[i+k]+total[i][i+k-1]-dpmax[i][i+k-1]);
            }
        }
    }
    
    // printf("%lld %lld", dpmax[0][n-1], dpmax[0][n-1]-(total[0][n-1]-dpmax[0][n-1]));
    printf("%lld", dpmax[0][n-1]-(total[0][n-1]-dpmax[0][n-1]));
    return 0;
}