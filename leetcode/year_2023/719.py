import random
import heapq
def solve1(arr, k):
    arr = sorted(arr)
    # print(arr, k)
    q = []
    heapq.heapify(q)
    c = 0
    n = len(arr)
    for i in range(1, n):
        heapq.heappush(q, (arr[i] - arr[i-1], i-1, i))
    while c <= k:
        c += 1
        it = heapq.heappop(q)
        val, i, j = it
        # print(i, j, val)
        if c == k:
            return val
        if j+1 < n:
            heapq.heappush(q, (arr[j+1] - arr[i], i, j+1))
    return -1

def count(arr, n, i, val):
    if i < n-1 and arr[n-1]-arr[i] <= val:
        return n-i-1
    if i+1 < n and arr[i+1]-arr[i] > val:
        return 0
    l = i
    r = n-1
    while l <= r:
        mid = (l+r)//2
        # print('debug', mid)
        if arr[mid]-arr[i] <= val and arr[mid+1]-arr[i] > val:
            return mid-i
        elif arr[mid]-arr[i] > val:
            r = mid-1
        else:
            l = mid+1
    return 0
def solve(arr, k):
    arr = sorted(arr)
    n = len(arr)
    ans = -1
    l = 0
    r = arr[n-1] - arr[0]
    while l <= r:
        mid = (l+r)//2
        cnt = 0
        for i in range(n-1):
            x = count(arr, n, i, mid)
            print(mid, i, x)
            cnt += x
        print(mid, cnt)
        if cnt >= k:
            ans = mid
            r = mid-1
        elif cnt < k:
            l = mid+1
    return ans

arr = [0,1,2]
k = 2
# n = 10000
# arr = [random.randint(0, 1000000) for _ in range(n)]
# k = n*(n-1)//2

print(solve(arr, k))
# print(count([1,1,3], 3, 2, 0))
