import sys
import math



alphabet = 'A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z'
alphabet = alphabet.replace(' ', '').split(',')
T = int(sys.stdin.readline())
for case in range(T):
    n, l = map(int,sys.stdin.readline().strip().split(' '))
    arr = list(map(int,sys.stdin.readline().strip().split(' ')))
    bet = {}
    text = [-1]*(l+1)
    for i in range(l-1):
        k = math.gcd(arr[i], arr[i+1])
        if k == arr[i]:
            kk = int(k**0.5)
            if kk**2 == k:
                k = kk
            else:
                continue
        bet[k] = 1
        text[i+1] = k
        if i == 0:
            bet[arr[i]//k] = 1
            text[0] = arr[i]//k
        elif i == l-2:
            bet[arr[i+1]//k] = 1
            text[-1] = arr[i+1]//k
    # print('len bet', len(bet.keys()), sorted(list(bet.keys())))
    # print(text)
    # print(bet)
    while True:
        flag = False
        for i in range(l):
            if text[i] == -1 and text[i+1] == -1:
                flag = True
            if text[i] == -1 and text[i+1] != -1:
                text[i] = arr[i]//text[i+1]
                bet[text[i]] = 1
            elif text[i] != -1 and text[i+1] == -1:
                text[i+1] = arr[i]//text[i]
                bet[text[i+1]] = 1
        if not flag: break

    # print('------')
    # print('len bet', len(bet.keys()), sorted(list(bet.keys())))
    # print(text)
    # print(bet)

    keys = sorted(list(bet.keys()))
    for i, letter in enumerate(alphabet):
        bet[keys[i]] = letter
    rs = ''
    for t in text:
        rs += bet[t]
    print('Case #{:d}: {}'.format(case+1, rs))
