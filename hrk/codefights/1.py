import sys

def find(startInd, string):
	result = ''
	i = startInd
	while i < len(string):
		if string[i] != '(' and string[i] != ')':
			result += string[i]
			i += 1
		else:
			if string[i] == '(':
				temp, j = find(i+1, string)
				result += temp[::-1]
				i = j
			else:
				return result, i+1
	return result, i

def reverseInParentheses(str):
	if str is None: return ''
	finalString, i = find(0, str)
	return finalString

#print reverseInParentheses('foo(bar(baz))blim')
print reverseInParentheses('aa(b(kk(cd)kk)bbbb(cd))hhh')

