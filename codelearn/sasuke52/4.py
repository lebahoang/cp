def getMin(arr):
    minV = -1
    for i in arr:
        if i == -1: continue
        if minV == -1 or minV > i:
            minV = i
    return minV
def one(x):
    # 1 = 2+3
    if x[1] <= x[2]+x[3]:
        if x[1] >= x[2]: return x[1]
        x[2] = x[2]-x[1]
        # pack a pair
        a = (x[2]-x[2]%2)
        if x[2]%2 != 0:
            if x[4] >= 1:
                a += 1
            else:
                a = -1
        # pack a triple
        b = ((x[2]-x[2]%3)//3)*2
        if x[2]%3 == 2:
            b += 2
        elif x[2]%3 == 1:
            if x[4] >= 1:
                b += 1
            else:
                b = -1
        t = getMin([a,b])
        if t != -1: return x[1]+t
        return -1

    x[1] = x[1]-x[2]-x[3]
    a = x[2]+x[3]+((x[1]-x[1]%3)//3)*2
    if x[1]%3 == 1:
        if x[4] >= 2: a += 2
        a = -1
    elif x[1]%3 == 2:
        if x[4] >= 1: a += 2
        a = -1
    
    b = x[2]+x[3]+((x[1]-x[1]%4)//4)*3
    if x[1]%4 == 3:
        b += 2
    elif x[1]%4 == 2:
        if x[4] >= 1: b += 2
        else: b = -1
    elif x[1]%4 == 1:
        if x[4] >= 2: b += 2
        else: b = -1
    return getMin([a,b])

def two(x):
    # 2 = 1+4
    if x[2] <= x[1]+x[4]:
        if x[2] >= x[1]: return x[2]
        x[1] = x[1]-x[2]
        
        a = x[2]+((x[1]-x[1]%3)//3)*2
        if x[1]%3 == 1:
            if x[3] >= 1:
                a += 1
            else:
                a = -1
        elif x[1]%3 == 2:
            if x[3] >= 2: a += 2
            elif x[4] >= 1: a += 2
            elif x[3] == 1 and x[4] >= 2: a += 3
            else: a = -1
        
        b = x[2]+((x[1]-x[1]%4)//4)*3
        if x[1]%4 == 3:
            b += 2
        elif x[1]%4 == 2:
            if x[3] >= 2: b += 2
            elif x[4] >= 1: b += 2
            elif x[3] == 1 and x[4] >= 2: b += 3
            else: b = -1
        elif x[1]%4 == 1:
            if x[3] >= 1: b += 1
            else: b = -1
        return getMin([a,b])

    rs = x[1]+x[4]
    x[2] = x[2]-x[1]-x[4]
    # pack a pair
    a = (x[2]-x[2]%2)
    if x[2]%2 != 0:
        if x[3] >= 2:
            a += 2
        else:
            a = -1
    # pack a triple
    b = ((x[2]-x[2]%3)//3)*2
    if x[2]%3 == 2:
        b += 2
    elif x[2]%3 == 1:
        if x[3] >= 2:
            b += 2
        else:
            b = -1
    t = getMin([a,b])
    if t > -1:
        return rs+t
    return -1

def moveCandy(candy):
    x = [0 for _ in range(5)]
    for i in candy:
        x[i] += 1
    print(x)
    xx = x[:]
    a = one(x)
    b = two(xx)
    print('a', a, 'b', b)
    return getMin([a,b])
    

# print(moveCandy([1,2,2,4,3]))
# print(moveCandy([1,1,3,1,1,1,1,1,3]))
print(moveCandy([4,1,1,1,1]))
#print(moveCandy(
#[2,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,4,2,1,1,1,1,1,1,3,1,3,1,3,3,1,3,1,1,1,1,1,1,1,1,1,4,1,1,1,3,1,3,1,2,2,1,1,3,1,1,1,1,1,1,1,2,1,3,1,1,1,1,1,1,1,1,1,3,3,3,1,1,1,3,1,1,1,3,1,1,1,1,2,1,1,1,1,3,2,3,3,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,1,3,1,2,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1,4,1,1,3,1,3,1,2,1,1,2,1,3,3,1,1,1,1,1,1,1,1,3,1,1,4,1,3,3,1,3,3,3,2,1,1,3,3,1,1,4,3,1,1,2,1,1,1,1,1,3,1,1,4,1,3,1,1,1,1,3,1,2,1,4,1,1,1,4,1,1,3,1,1,3,1,1,3,1,1,1,1,2,1,3,3,1,3,1,3,1,1,1,1,3,3,1,3,3,4,1,1,1,1,1,1,1,1,1,1,1,4,3,3,1,3,3,1,2,3,4,1,1,1,1,1,1,3,2,3,1,1,1,1,1,1,1,2,1,1,3,1,1,1,1,1,3,1,1,1,1,1,1,3,4,4,1,1,1,3,1,1,1,1,3,4,1,1,1,1,3,1,1,1,1,1,2,1,1,1,4,4,1,1,1,1,4,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,1,4,1,3,3,3,3,3,1,3,3,3,3,3,1,1,3,1,3,1,1,2,1,3,1,1,1,3,1,3,3,1,1,1,3,3,1,1,1,1,1,1,1,1,3,1,1,3,3,1,1,3,1,3,1,1,3,3,1,1,1,3,1,1,2,1,3,1,1,1,1,2,1,1,1,1,1,4,1,1,3,1,1,1,4,1,1,3,3,1,1,1,1,1,1,1,1,3,1,3,1,3,1,1,1,1,1,1,1,4,2,1,1,1,1,1,1,1,1,2,1,3,1,1,1,1,1,1,2,1,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,3,1,3,2,1,1,1,1,1,3,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,3,3,1,1,2,3,1,1,2,1,3,3,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,2,1,3,2,3,1,4,1,1,1,1,1,1,1,3,1,1,1,3,2,1,1,1,3,1,2,4,2,1,1,3,1,1,4,1,3,1,1,1,1,3,1,4,1,3,4,3,1,1,1,2,1,1,2,1,1,3,4,1,1,1,1,1,1,1,3,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,3,3,3,1,1,4,3,1,3,2,1,4,1,1,3,1,2,4,1,1,1,3,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,1,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1,1,4,3,1,3,1,1,3,2,1,1,4,1,1,1,1,4,1,1,3,4,1,4,1,1,1,3,1,1,1,4,1,4,1,1,2,4,1,1,1,1,1,1,1]))
# print(moveCandy([3,1,1,1,1,1,1,3,4,1,1,3,3,3,3,1,3,1,4,1,1,1,1,3,1,3,1,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,3,1,1,1,1,1,1,1,1,1,3]))
    