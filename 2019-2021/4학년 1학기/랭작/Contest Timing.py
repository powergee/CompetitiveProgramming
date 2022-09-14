arr = list(map(int, input().split()))
total = arr[0]*1440 + arr[1]*60 + arr[2] - (11*1440 + 11*60 + 11)
if total >= 0:
    print(total)
else:
    print(-1)