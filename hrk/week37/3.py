import sys

t = int(sys.stdin.readline())
for _ in range(t):
	arr = list(map(int, sys.stdin.readline().strip().split(' ')))
	brr = []
	for i in arr:
		if i > 0:
			brr.append(i)
	if len(brr) <= 1:
		print(0)
	else:
		brr[0] -= 1
		total = sum(brr)
		for i in range(len(brr)):
			if brr[i]/total > 0.5:
				brr[i] -= (total - 2*(total - brr[i]))
		print(sum(brr)//2)