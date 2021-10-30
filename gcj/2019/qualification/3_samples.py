import sys

keys = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103]
alphabet = 'A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z'
alphabet = alphabet.replace(' ', '').split(',')

k = []
text = []
while len(k) <= 100:
    # for j, letter in enumerate(alphabet):
    #     k.append(keys[j])
    for j, letter in enumerate(alphabet):
        k.append(keys[j])
        k.append(keys[j])
        k.append(keys[j])
        k.append(keys[j])
        k.append(keys[j])
        k.append(keys[j])
        k.append(keys[j])

    # i = 0
    # while i < 25:
    #     a = alphabet[i]
    #     b = alphabet[i+1]
    #     text.append(a)
    #     text.append(b)
    #     text.append(a)
    #     k.append(keys[i])
    #     k.append(keys[i+1])
    #     k.append(keys[i])
    #     i += 2
    if len(k) > 100: break

l = []
for i in range(len(k)-1):
    l.append(k[i]*k[i+1])

print('1')
print('103', len(l))
print(' '.join([str(x) for x in l]))
print(''.join(text))


