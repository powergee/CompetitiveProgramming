[n, m] = list(map(int, input().split(' ')))
if m == 1:
	for a in range(1, n+1):
		print(a)
elif m == 2:
	for a in range(1, n+1):
		for b in range(a+1, n+1):
			print(a, b)
elif m == 3:
	for a in range(1, n+1):
		for b in range(a+1, n+1):
			for c in range(b+1, n+1):
				print(a, b, c)
elif m == 4:
	for a in range(1, n+1):
		for b in range(a+1, n+1):
			for c in range(b+1, n+1):
				for d in range(c+1, n+1):
					print(a, b, c, d)
elif m == 5:
	for a in range(1, n+1):
		for b in range(a+1, n+1):
			for c in range(b+1, n+1):
				for d in range(c+1, n+1):
					for e in range(d+1, n+1):
						print(a, b, c, d, e)
elif m == 6:
	for a in range(1, n+1):
		for b in range(a+1, n+1):
			for c in range(b+1, n+1):
				for d in range(c+1, n+1):
					for e in range(d+1, n+1):
						for f in range(e+1, n+1):
							print(a, b, c, d, e, f)
elif m == 7:
	for a in range(1, n+1):
		for b in range(a+1, n+1):
			for c in range(b+1, n+1):
				for d in range(c+1, n+1):
					for e in range(d+1, n+1):
						for f in range(e+1, n+1):
							for g in range(f+1, n+1):
								print(a, b, c, d, e, f, g)
elif m == 8:
	for a in range(1, n+1):
		for b in range(a+1, n+1):
			for c in range(b+1, n+1):
				for d in range(c+1, n+1):
					for e in range(d+1, n+1):
						for f in range(e+1, n+1):
							for g in range(f+1, n+1):
								for h in range(g+1, n+1):
									print(a, b, c, d, e, f, g, h)
