def isNotDigit(c):
    arr = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0']
    if c not in arr:
        return True
    return False
def solve(start, a):
    rs = ''
    k = 0
    ind = start
    while ind < len(a):
        i = a[ind]
        if not isNotDigit(i):
            ind += 1
            continue
        elif i == '[':
            t = ''
            j = ind-1
            while True:
                if isNotDigit(a[j]):
                    break
                t = a[j] + t
                j -= 1
            k = int(t)
            string, next_ind = solve(ind+1, a)
            rs += string*k
            ind = next_ind
        elif i == ']':
            return rs, ind+1
        else:
            rs += i
            ind += 1
    return rs, ind+1

print(solve(0, '3[ab]3[c]eee'))
print(solve(0, 'avdssd'))