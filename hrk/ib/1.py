# ty = '11101'
# y = int(ty, 2)
# x = y
# while x > 0:
#     t = bin(x)[2:]
#     if len(t) < len(ty):
#         t = '0'*(len(ty)-len(t)) + t
#     print(x,t)
#     x = y & (x-1)

count = 0
n = 16
for i in range(1 << n):
    j = i
    while j > 0:
        count += 1
        j = i & (j-1)
print(count)
