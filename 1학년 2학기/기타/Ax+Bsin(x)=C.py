from decimal import *

getcontext().prec = 50

def cos(x):
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 0, 0, 1, 1, 1, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

def sin(x):
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 1, 0, x, 1, x, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

token = input().split(' ')
A = int(token[0])
B = int(token[1])
C = int(token[2])

xFound = Decimal('0.0')
for i in range(0, 100):
    xFound = xFound - (A * xFound + B * sin(xFound) - C) / (A + B * cos(xFound))

print(round(xFound, 6))