# a = 'aaacbbbbcdddddddddddd'
# b = 'aaatbbbbcdddddddddd'

# la = len(a)
# lb = len(b)
# dp = [[0 for j in range(lb)] for i in range(la)]

# for i in range(la):
#   for j in range(lb):
#     if a[i] == b[j]:
#       dp[i][j] = 1
#       if i-1 >= 0 and j-1 >= 0:
#         dp[i][j] += dp[i-1][j-1]

# max = 0
# maxInd = ()
# for i in range(la):
#   for j in range(lb):
#     if max < dp[i][j]:
#       max = dp[i][j]
#       maxInd = (i,j)


# print(max)
# print(maxInd)
# print(a[maxInd[0]-max+1: maxInd[0]+1], b[maxInd[1]-max+1: maxInd[1]+1])


def get(substr):
    import json
    import urllib.request as request
    contents = request.urlopen('https://jsonmock.hackerrank.com/api/movies/search/?Title={}'.
                format(substr)).read()
    contents = json.loads(contents)
    total_pages = int(contents['total_pages'])
    i = 1
    rs = []
    while i <= total_pages:
        contents = request.urlopen('https://jsonmock.hackerrank.com/api/movies/search/?Title={}&page={:d}'.
                format(substr, i)).read()
        contents = json.loads(contents)
        data = contents['data']
        for r in data:
            rs.append(r['Title'])
        i += 1
    return sorted(rs)

print(get('spiderman'))
