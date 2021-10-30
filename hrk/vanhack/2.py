import sys

def foo(rules):
	def union_xy(x, y):
		xy = x.split(',')
		t = []
		for i in y.split(','):
			f = 0
			for j in x.split(','):
				if i == j:
					f = 1
			if f == 0:
				t.append(i)
		xy.extend(t)
		xy = sorted(xy)
		return ','.join(xy)

	def is_support(set_of_attrs, record_attrs):
		for set_of_attr in set_of_attrs:
			f = 0
			for record_attr in record_attrs:
				if set_of_attr == record_attr:
					f = 1
			if f == 0:
				return False
		return True


	d = {}
	for r in rules:
		a,b = r.replace('{', '').replace('}', '').split('=>')
		ab = union_xy(a,b)
		a = ','.join(sorted(a.split(',')))
		if ab not in d:
			d[ab.lower()] = 0.0
		if a not in d:
			d[a.lower()] = 0.0


	# calculate support of set of attr
	with open('./census.csv', 'r') as f:
		for line in f.readlines():
			record_attrs = line.strip().lower().split(',')
			for r in d.keys():
				set_of_attrs = r.split(',')
				if is_support(set_of_attrs, record_attrs):
					d[r] += 1.0

	rs = []
	for r in rules:
		a,b = r.replace('{', '').replace('}', '').split('=>')
		ab = union_xy(a,b)
		a = ','.join(sorted(a.split(',')))
		rs.append((d[ab.lower()]/d[a.lower()], r))

	rs = sorted(rs, reverse=True)
	sorted_rules = []
	for r in rs:
		sorted_rules.append(r[1])
	return sorted_rules









rules = [
	'{native-country=United-States,capital-gain=None}=>{capital-loss=None}',
	'{capital-gain=None,capital-loss=None}=>{native-country=United-States}',
	'{native-country=United-States,capital-loss=None}=>{capital-gain=None}'
]

print(foo(rules))