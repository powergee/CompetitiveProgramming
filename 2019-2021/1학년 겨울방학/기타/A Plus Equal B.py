answer = []

a, b = map(int, input().split(' '))

while abs(a-b) != 0:

    while a % 2 == 0:
        a //= 2
        answer.append("B+=B")

    while b % 2 == 0:
        b //= 2
        answer.append("A+=A")

    if a > b:
        a += b
        a //= 2
        answer.append("A+=B")
        answer.append("B+=B")
    
    elif a < b:
        b += a
        b //= 2
        answer.append("B+=A")
        answer.append("A+=A")

print(len(answer))
for s in answer:
    print(s)