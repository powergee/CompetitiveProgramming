s = int(input())
d = int(input())

if s % 2 == 0:
    print(s//2 + d//2)
    print(s//2 - d//2)
else:
    print(s//2+1 + d//2)
    print(s//2 - d//2)