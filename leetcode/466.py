# def find_occurences(s1, s2):
#     n = len(s1)
#     m = len(s2)
#     used = [False for i in range(n)]
#     c = 0
#     for i in range(n):
#         if s1[i] == s2[0]:
#             t = 0
#             for j in range(i, n):
#                 if not used[j] and s1[j] == s2[t]:
#                     t += 1
#                     used[j] = True
#                 if t == m:
#                     break
#             if t == m: c += 1
#     return c

def find_occurences(s1, s2):
    n = len(s1)
    m = len(s2)
    c = 0
    i = 0
    while i < n:
        if s1[i] == s2[0]:
            t = 0
            for j in range(i, n):
                if s1[j] == s2[t]:
                    t += 1
                if t == m:
                    i = j+1
                    break
            if t == m:
                c += 1
            else:
                i += 1
        else:
            i += 1
    return c

def s2_chars(s2):
    c = 0
    cur = ''
    for i in s2:
        if cur == '':
            cur = i
        elif i != cur:
            return -1
        c += 1
    return c
def count_s2_char_in_s1(s1, char):
    c = 0
    for i in s1:
        if i == char: c += 1
    return c

def solve466(s1, n1, s2, n2):
    if s2 == '': return 1
    if s2_chars(s2) != -1:
        y = len(s2)
        x = count_s2_char_in_s1(s1, s2[0])
        if (n1*x) % (y*n2) == 0:
            return (n1*x) // (y*n2)
        k = (n1*x) % (y*n2)
        return (n1*x-k)//(y*n2)
    c = find_occurences(s1, s2)
    if c == 0:
        return 0
    if n1*c % n2 == 0:
        return n1*c//n2
    else:
        return (n1*c-(n1*c%n2))//n2


# s1 = 'acb'
# n1 = 4
# s2 = 'ab'
# n2 = 2
# print(solve466(s1, n1, s2, n2))

for i in range(2, 22):
    print(i, find_occurences('baba'*i, 'baab'))

# print(find_occurences('baba'*2, 'baab'))
# print(find_occurences('baba'*3, 'baab'))
# print(find_occurences('baba'*4, 'baab'))
# print(find_occurences('baba'*5, 'baab'))
# print(find_occurences('baba'*6, 'baab'))
# print(find_occurences('baba'*7, 'baab'))
# print(find_occurences('baba'*8, 'baab'))
# print(find_occurences('baba'*9, 'baab'))
# print(find_occurences('baba'*10, 'baab'))
# print(find_occurences('baba'*11, 'baab'))
# print(find_occurences('baba'*12, 'baab'))
