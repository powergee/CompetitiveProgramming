n = int(input())
total = 0
diff = 2
for i in range(1,n+1):
    if i > 2 and i % 2 == 0:
        diff += 1
    total += diff

print(total)