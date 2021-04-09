def power(val, exp, mod):
    if exp == 0:
        return 1 % mod
    elif exp % 2 == 0:
        return (power(val, exp//2, mod) ** 2) % mod
    else:
        return ((power(val, exp//2, mod) ** 2) % mod * val) % mod

[a, b, c] = list(map(int, input().split(" ")))
print(power(a, b, c))