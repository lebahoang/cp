import sys


#  153846 * 4
def mul_op(i, x, k):
	j = 1
	num = [i]
	ss = i
	add = 0
	while j <= k:
		t = (i*x + add)%10
		if j == k:
			num.append(i*x + add)
		else:
			num.append(t)
			ss += t*10**(len(num)-1)

		add = (i*x+add-t)//10
		i = t
		j += 1
	return num[::-1], ss


# print(mul_op(6, 4, 6))

ss = 0
for k in range(2, 3):
	for i in range(1, 10):
		for j in range(1, 10):
			arr, s = mul_op(i, j, k)
			if arr[0] == arr[-1] and arr[1] > 0:
				# if j > 1: print(arr, arr[1:], j)
				print(arr, arr[1:], j)
				ss += s
print(ss)