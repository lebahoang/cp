# import sys

# total = 0
# c = 0
# n = int(sys.stdin.readline())
# for _ in range(n):
# 	r = int(sys.stdin.readline())
# 	if r >= 90:
# 		total += r
# 		c += 1

# a = '{:.3f}'.format(float(total) / float(c))
# #a = '12.000'
# arr = a.split('.')
# one = int(arr[0])
# two = int(arr[1][0:2])

# x = int(arr[1][2])
# if x >= 5:
# 	two += 1
# if two == 100:
# 	one += 1
# 	two = '00'
# else:
# 	two = str(two)
# 	if two < '10':
# 		two = '0'+two
# print("{:d}.{:s}".format(one, two))


import numpy as np

a = np.random.randint(1, 1000, size = (3,4))
b = np.random.randint(1, 1000, size = (3,4))
c = np.outer(a,b)
print(c.shape)
print(c)


