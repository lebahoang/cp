import sys

# def go(s1, s2):
#     n = len(s1)
#     dp = [[[False for k in range(n+1)] for j in range(n)] for i in range(n)]
#     for i in range(n):
#         for j in range(n):
#             if s1[i] == s2[j]:
#                 dp[i][j][1] = True

#     for k in range(2, n+1):
#         for i in range(n):
#             for j in range(n):
#                 if i+k <= n and j+k <= n:
#                     for kk in range(1, k):
#                         if (dp[i][j][kk] and dp[i+kk][j+kk][k-kk]) or (dp[i][j+k-kk][kk] and dp[i+kk][j][k-kk]):
#                             dp[i][j][k] = True


#     # for k in range(1, n+1):
#     #     for i in range(n):
#     #         for j in range(n):
#     #             print(i,j,k,dp[i][j][k])

#     return dp[0][0][n]

# def go(arr, i, l, r):
#     if i >= 0:
#         a = False
#         if i-1 >= 0:
#             if arr[i] > arr[i-1]:
#                 a = True
#         b = False
#         if i+1 < len(arr):
#             if arr[i] < arr[i+1]:
#                 b = True

#         if i == 0 and b:
#             return i
#         if i == len(arr)-1 and a:
#             return i
#         if a and b:
#             return i
#     if l > r:
#         return -1
#     mid = (l+r)//2
#     x = go(arr, mid, l, mid-1)
#     if x > -1:
#         return x
#     x = go(arr, mid, mid+1, r)
#     if x > -1:
#         return x
#     return -1

# def two(arr):
#     l = 0
#     r = len(arr)-1
#     x = go(arr, -1, l, r)
#     if x >= 0:
#         return arr[x]
#     return -1


# arr = [1,2,2,3,3,4,4,5,5]
# print(two(arr))

class FreqStack895:
    def __init__(self):
        self.n2f = {}
        self.f2n = {}
        self.maxf = []
        

    def push(self, x: int) -> None:
        f = -1
        if x not in self.n2f:
            self.n2f[x] = 1
            f = 1
        else:
            self.n2f[x] += 1
            f = self.n2f[x]

        if not self.maxf:
            self.maxf.append(f)
        else:
            if f > self.maxf[-1]: self.maxf.append(f)
        if f not in self.f2n:
            self.f2n[f] = [x]
        else:
            self.f2n[f].append(x)

    def pop(self) -> int:
        x = self.maxf[-1]
        n = self.f2n[x].pop(-1)
        if len(self.f2n[x]) == 0:
            self.maxf.pop(-1)
        self.n2f[n] -= 1
        if x-1 not in self.f2n:
            self.f2n[x-1] = [n]
        if len(self.f2n[x]) == 0:
            del self.f2n[x]
        return n

q = FreqStack895()
q.push(1)
q.push(2)
q.push(3)
q.push(4)
q.push(5)
q.push(6)
print(q.pop())
print(q.pop())
print(q.pop())
print(q.pop())


    



    



