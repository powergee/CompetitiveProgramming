def printHanoi(n, left, mid, right):
    if n == 1:
        print(f"{left} {right}")
    else:
        printHanoi(n-1, left, right, mid)
        print(f"{left} {right}")
        printHanoi(n-1, mid, left, right)

k = int(input())
print((1<<k)-1)
if k <= 20:
    printHanoi(k, 1, 2, 3)