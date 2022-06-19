import sys
input = sys.stdin.readline

T = int(input())
for _ in range(T):
    n = int(input())
    s = int(input())

    printed = False
    
    left = 10**(n-1)
    right = int("9"*n)
    for p in [n, n+1]:
        for d in range(1, 10):
            target = int(str(d) * p)
            dist = target-s
            if left <= dist <= right:
                print(dist)
                printed = True
            if printed:
                break
        if printed:
            break
