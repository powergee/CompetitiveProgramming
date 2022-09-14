s, a = map(int, input().split())
s *= 1000
a *= 1000

if 7*a <= s:
    print(7*a)
elif 7*(a//2) <= s:
    print(7*(a//2))
elif 7*(a//4) <= s:
    print(7*(a//4))
else:
    print(0)