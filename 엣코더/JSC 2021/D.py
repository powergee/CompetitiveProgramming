def power(val, exp, mod):
    if exp == 0:
        return 1 % mod
    elif exp % 2 == 0:
        return (power(val, exp//2, mod) ** 2) % mod
    else:
        return ((power(val, exp//2, mod) ** 2) % mod * val) % mod

n, p = list(map(int, input().split(" ")))
print(((p-1) * power(p-2, n-1, 1000000007)) % 1000000007)