r, c, n = map(int, input().split())
divceil = lambda x, d: x//d + (1 if x%d > 0 else 0)
print(divceil(r, n) * divceil(c, n))