arr = list(map(int, input().split()))
diff = 1e9
for i in range(4):
    for j in range(i+1, 4):
        diff = min(diff, abs(sum(arr) - 2*arr[i] - 2*arr[j]))
print(diff)