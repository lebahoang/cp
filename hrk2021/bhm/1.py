a = [2,3,4,5,6,10,13,17]
l = 10
for x in a:
    y = bin(x)[2:]
    if len(y) < l:
        y = '0'*(l-len(y)) + y
    print(y)