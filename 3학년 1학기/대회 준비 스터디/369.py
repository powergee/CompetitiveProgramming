n = int(input())

count = 0
for i in range(1, n+1):
    s = str(i)
    for ch in s:
        if ch == '3' or ch == '6' or ch == '9':
            count += 1

print(count)