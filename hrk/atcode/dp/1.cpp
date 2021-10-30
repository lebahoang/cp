#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 2e5+5;
int n,q;
int a[MAX];

int search1(int v, int l, int r) {
    // printf("ssss %d %d\n", l, r);
    if (l > r) {
        return -1;
    }
    int mid = (l+r)/2;
    if ((mid-1 >= 0 && a[mid-1] < v && a[mid] >= v) || (mid-1 < 0 && a[mid] >= v)) {
        return mid;
    }
    if (a[mid] < v) {
        return search1(v, mid+1, r);
    }
    return search1(v, l, mid-1);
}
int search2(int v, int l, int r) {
    // printf("ssss %d %d\n", l, r);
    if (l > r) {
        return -1;
    }
    int mid = (l+r)/2;
    if ((mid+1 < n && a[mid+1] > v && a[mid] <= v) || (mid+1 >= n && a[mid] <= v)){
        return mid;
    }
    if (a[mid+1] <= v) {
        return search2(v, mid+1, r);
    }
    return search2(v, l, mid-1);
}
int solve(int l, int r) {
    int x = search2(r,0,n-1);
    int y = search1(l,0,n-1);
    // printf("%d %d\n", x, y);
    if (x == -1 || y == -1) {
        return 0;
    }
    return x-y+1;
}
int main()
{
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a+n);
    int l, r;
    for (int i = 0; i < q; i++) {
        cin >> l >> r;
        cout << solve(l, r) << "\n";
    }

    return 0;
}
