def dfs(pt, rem, count, lenc, coins, res):
    if rem <= 0:
        res = min(res, count)
        return res
    if rem%coins[pt] == 0:
        res = min(res, count + rem//coins[pt])
        return res
    for i in range(pt, lenc):
        if coins[i] <= rem < coins[i] * (res-count): # if hope still exists
            res = dfs(i, rem-coins[i], count+1, lenc, coins, res)
    return res

def min_money(amount, coins):
    import sys
    sys.setrecursionlimit(10000)
    coins.sort(reverse = True)
    lenc, res = len(coins), 2**31-1
    
    for i in range(lenc):
        res = dfs(i, amount, 0, lenc, coins, res)
    return res if res < 2**31-1 else 0

print(min_money(100000000,[3,5,7]))