def compute(arr):
    rs = 0
    s = []
    for x in arr:
        if type(x) is int:
            if s and type(s[-1]) is str:
                s.pop(-1)
                y = s.pop(-1)
                s.append(x*y)
            else:
                s.append(x)
        else:
            s.append(x)
    for x in s:
        rs += x
    return rs

def op(a, b, op):
    if op == '+': return a+b
    return a*b
def f(i, j, s, dp):
    if len(dp[i][j].keys()) > 0:
        return dp[i][j]
    if i == j:
        dp[i][j] = {int(s[i]): 1}
        return dp[i][j]
    rs = {}
    for k in range(i, j-1):
        if s[k] == '+' or s[k] == '*':
            continue
        x = f(i,k,s,dp)
        y = f(k+2,j,s,dp)
        for a in x.keys():
            for b in y.keys():
                rs[op(a,b,s[k+1])] = 1
    dp[i][j] = rs
    return dp[i][j]           

def solve(s, arr):
    a = s.split('*')
    temp = []
    for i in a:
        b = [int(k) for k in i.split('+')]
        if temp:
            temp.append('*')
        temp.extend(b)
    right = compute(temp)
    n = len(s)
    dp = [[{} for _ in range(n)] for _ in range(n)]
    wrong = f(0, n-1, s, dp)
    if right in wrong:
        del wrong[right]
    # print(right, wrong)
    ans = 0
    arr = sorted(arr)
    cnt = 0
    cur = -1
    for i in arr:
        if cur == -1 or cur != i:
            if cur > -1:
                if cur == right:
                    ans += 5*cnt
                elif cur in wrong:
                    ans += 2*cnt
            cur = i
            cnt = 1
        else:
            cnt += 1
    if cur == right:
        ans += 5*cnt
    elif cur in wrong:
        ans += 2*cnt
    print(ans)
    return ans


# print(generate_all_sum([4346]))
# print(compute([7,3,'*',1,'*',2]))
solve("4*8*4+4*4*4+4*4+8*8+4*4+8*4+8*8", [42,17,13,66,32,547,21,90,13,33,45,66,34,21,13,13,13,46,21,177,18,13,18,16,16,678,13,42,66,13,18,18,777,21,924,13,268,13,13,13,25,62,45,33,888,779,13,206,48,13,34,17])
# solve('6+0*1', [12,9,6,4,8,6])
# solve("2*1+2+2+2+2*8*3+3+3*7*7+4+3+1+1", [1,215,3,4,341,32,5,6,6])