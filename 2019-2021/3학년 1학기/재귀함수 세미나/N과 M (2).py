def print_comb(n, m, start, selected):
    print(start, selected)
    if len(selected) == m:
        # print(*selected)
        pass
    elif start <= n:
        selected.append(start)
        print_comb(n, m, start+1, selected)
        selected.pop()
        print_comb(n, m, start+1, selected)

[n, m] = list(map(int, input().split(' ')))
print_comb(n, m, 1, [])