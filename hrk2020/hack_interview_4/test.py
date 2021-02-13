import numpy as npy
def C(n,m):
    if n < m: return 1.0
    return n*(n-1)/2.0
dp = [[0.0 for _ in range(10)] for _ in range(10)]
np = [[0.0 for _ in range(10)] for _ in range(10)]
ans = [[0.0 for _ in range(10)] for _ in range(10)]

# 3 2.77465280
# P = 0.678
# np[0][0] = 0
# np[0][1] = 
# np[1][0]
# np[2][0]
# np[0][2]
# np[2][1]
# np[1][2]
# np[2][2]


P = 0.5
# 1

# 2
# np[1][1] = 0.0
# np[0][1] = (1 + np[1][1])*(2/C(3,2) * P)
# np[1][0] = (1 + np[1][1])*(2/C(3,2) * (1-P))
# np[0][0] = (1 + np[0][1])*(1-P) + (1 + np[1][0])*P

# ans[1][1] = (1 + np[1][1])*(1/C(3,2))*(1-P) + (1 + np[1][1])*(1/C(3,2))*P
# ans[0][1] = (1 + np[0][1])*(1/C(2,2))*P
# ans[1][0] = (1 + np[1][0])*(1/C(2,2))*(1-P)
# ans[0][0] = 0.0

np[0][0] = 0
np[0][1] = (1+np[0][0])*(1-P) + P
np[1][0] = (1+np[0][0])*(P) + (1-P)
np[1][1] = (1+np[1][0])*(2/C(3,2)*(1-P)) + (1+np[0][1])*(2/C(3,2)*P) + 1/C(3,2)*P + 1/C(3,2)*(1-P)
print(np[1][1])

# print(np)
# print(ans)
# print('{:.8f}'.format(npy.sum(ans) + np[0][0]))


