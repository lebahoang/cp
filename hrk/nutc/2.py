def resolvePrices(count, total, priceListStr):
    # Write your code here
    def do(ind, curC, curTotal, count, total, arr, rs):
        if ind == len(arr):
            print(ind, rs, ind, curTotal, curC, 'lll')
            if curTotal == total and curC == count:
                return True, rs
            else:
                return False, []

        rs.append(arr[ind])
        ok, t1 = do(ind+1, curC+1, curTotal+arr[ind], count, total, arr, rs)
        if ok: return ok, t1
        rs.pop(-1)
        if ind == 0:
            rs = [arr[ind]*1000]
        else:
            x = (curTotal - rs[-1]) + (rs[-1]*1000 + arr[ind])
            rs = rs[:-1] + [rs[-1]*1000 + arr[ind]]
        ok, t2 = do(ind+1, curC, x, count, total, arr, rs)
        if ok: return ok, t2
        return False, []

    arr = list(map(int, priceListStr.split(',')))
    ok, rs = do(0, 0, 0, count, total, arr, [])
    return rs

# print(resolvePrices(2, 124245, '123,456,789'))
# print(resolvePrices(3, 358812, '123,456,789,234,567'))
# print(resolvePrices(1, 19801720, '19,801,720'))
print(resolvePrices(2, 72254368, '19,801,72,234,567'))

    



