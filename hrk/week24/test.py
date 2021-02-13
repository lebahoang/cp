import random

alphabet = 'A B C D E F G H I J K L M N O P Q R S T U V W X Y Z'
alphabet = alphabet.replace(' ', '').lower()
q = 3
print(q)
for _ in range(q):
	n = 50
	print(n)
	for _ in range(n):
		a = []
		for _ in range(20):
  			a.append(alphabet[random.randint(0, 25)])
		print(''.join(a))
