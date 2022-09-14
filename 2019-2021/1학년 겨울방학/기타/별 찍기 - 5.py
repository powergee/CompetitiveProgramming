n = int(input())

for i in range(0, n):
    print(" " * (n - i - 1) + "*" * i + "*" * (i + 1))