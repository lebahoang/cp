def solve(a, k):
    n = len(a)
    s = [[-1, -1] for _ in range(n)]
    stack = []
    for i in range(n):
        while stack:
            if a[i] > a[stack[-1]]:
                break
            else:
                stack.pop(-1)
        if stack:
            s[i][0] = stack[-1]+1
        else:
            s[i][0] = 0
        stack.append(i)
    
    stack = []
    for i in range(n-1, -1, -1):
        while stack:
            if a[i] > a[stack[-1]]:
                break
            else:
                stack.pop(-1)
        if stack:
            s[i][1] = stack[-1]-1
        else:
            s[i][1] = n-1
        stack.append(i)
    # print(s)
    ans = 0
    for ind in range(n):
        i, j = s[ind]
        if i <= k and k <= j:
            ans = max(ans, a[ind]*(j-i+1))
    return ans

# a = [1,4,3,7,4,5]
# k = 3
a = [5,5,4,5,4,1,1,1]
k = 0
print(solve(a, k))