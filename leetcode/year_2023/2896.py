def cost(a, b, x, arr):
    if arr[b]-1 != arr[a]:
        return min(x, arr[b]-arr[a])
    return 1

def run(i, j, x, arr, dp):
    if dp[i][j] > -1:
        return dp[i][j]
    if i+1 == j:
        dp[i][j] = cost(i,j,x,arr)
        return dp[i][j]
    val = cost(i, j, x, arr) + run(i+1, j-1, x, arr, dp)
    for k in range(i+1, j-1):
        if (k-i+1)%2 == 0 and (j-(k+1)+1)%2 == 0:
            val = min(val, run(i, k, x, arr, dp) + run(k+1, j, x, arr, dp))
    dp[i][j] = val
    return dp[i][j]

def solve(s1, s2, x):
    arr = []
    n = len(s1)
    for i in range(n):
        if s1[i] != s2[i]:
            arr.append(i)
    l = len(arr)
    if l%2 == 1:
        return -1
    # print(arr)
    dp = [[-1 for _ in range(l)] for _ in range(l)]
    run(0, l-1, x, arr, dp)
    # print(dp)
    return dp[0][l-1]

print(solve('11000101010101010100101010111000', '11000001110101010100101010111110', 20))
# print(solve('110010111000001011111111111101010101010100110100101010000101110010101010101010100101010111000', '110000111000001011111111111101010101010101000100101010000101110010101010101010100101010111000', 20))
# print(solve('1011110', '0111101', 20))
# print(solve("101111110110010100", "010001111100000100", 3))

# s1 = '1101110000010101010100001011100101010111000'
# s2 = '1000001000001110101010101010100101010111110'
# ss1 = s1[:28]
# ss2 = s2[:28]
# print(ss1, ss2)
# print(solve(ss1, ss2, 20))