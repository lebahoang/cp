def foo(filename, n):
	import csv
	with open(filename, 'r') as f:
		rs_lines = []
		lines = f.readlines()[1:]
		i = 0
		for line in lines:
			arr = line.strip().split(',')
			day = int(arr[0])
			open_price = float(arr[1])
			high = float(arr[2])
			low = float(arr[3])
			close = float(arr[4])
			volume = float(arr[5])

			typical_price = (high+low+close)/3
			money_flow = typical_price * volume
			positive_flow = negative_flow = 0.0
			if i > 0:
				if typical_price > rs_lines[i-1]['typical_price']:
					positive_flow = money_flow
				elif typical_price < rs_lines[i-1]['typical_price']:
					negative_flow = money_flow
			positive_flow_sum = negative_flow_sum = 0.0
			mfi = 0.0
			if i-n+1 >= 1:
				for k in range(i-n+1, i):
					positive_flow_sum += rs_lines[k]['positive_flow']
					negative_flow_sum += rs_lines[k]['negative_flow']
				positive_flow_sum += positive_flow
				negative_flow_sum += negative_flow
				money_ratio = positive_flow_sum / negative_flow_sum
				mfi = (money_ratio/(1+money_ratio)) * 100.0
			rs_lines.append({
				'day': day,
				'open': open_price,
				'high': high,
				'low': low,
				'close': close,
				'volume': volume,
				'typical_price': typical_price,
				'positive_flow': positive_flow,
				'negative_flow': negative_flow,
				'positive_flow_sum': positive_flow_sum,
				'negative_flow_sum': negative_flow_sum,
				'mfi': mfi
			})
			i += 1



		fields = ['Day', 'Open', 'High', 'Low', 'Close',
			'Volume', 'Typical Price', 'Positive Money Flow',
			'Negative Money Flow', 'Positive Money Flow Sum', 'Negative Money Flow Sum',
			'Money Flow Index'
		]
		with open('money_flow_index_{:d}.csv'.format(n), 'w') as csv_out:
			writer = csv.DictWriter(csv_out, fieldnames=fields)
			writer.writeheader()
			for line in rs_lines:
				writer.writerow({
					'Day': line['day'],
					'Open': line['open'],
					'High': line['high'],
					'Low': line['low'],
					'Close': line['close'],
					'Volume': line['volume'],
					'Typical Price': '{:.6f}'.format(line['typical_price']) if line['typical_price'] > 0 else '',
					'Positive Money Flow': '{:.6f}'.format(line['positive_flow']) if line['positive_flow'] > 0 else '',
					'Negative Money Flow': '{:.6f}'.format(line['negative_flow']) if line['negative_flow'] > 0 else '',
					'Positive Money Flow Sum': '{:.6f}'.format(line['positive_flow_sum']) if line['positive_flow_sum'] > 0 else '',
					'Negative Money Flow Sum': '{:.6f}'.format(line['negative_flow_sum']) if line['negative_flow_sum'] > 0 else '',
					'Money Flow Index': '{:.6f}'.format(line['mfi']) if line['mfi'] > 0 else ''
				})


foo('./sample.csv', 10)

