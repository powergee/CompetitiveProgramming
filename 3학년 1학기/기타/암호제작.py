P, K = map(int, input().split())

isPrime = [True] * (K+1)
isPrime[0] = isPrime[1] = False

div = 2
while div*div <= K:
    if isPrime[div]:
        for i in range(div*div, K+1, div):
            isPrime[i] = False
    div += 1

good = True
for i in range(2, K):
    if not isPrime[i]:
        continue
    elif P % i == 0:
        print("BAD", i)
        good = False
        break

if good:
    print("GOOD")