sum, diff = list(map(int, input().split()))

a = (sum+diff) // 2
b = sum-a

if (sum+diff) % 2 == 0 and b >= 0:
    mid = (sum+diff) // 2
    print(mid, sum-mid)
else:
    print(-1)